#include <glib.h>

#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>

#include "scribe.h"
#include "logger.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace scribe::thrift;

struct scribelogger_st {
	char             *scribe_host;
	short            scribe_port;
	GAsyncQueue      *queue; 
	GThread          *logging_thread;
	gboolean         thread_shutdown;
};

message_t scribelogger_message_new(const char *message, const char *category) {
	message_t msg = g_slice_new(struct message_st);
	msg->message = g_strdup(message);
	msg->category = g_strdup(category);
	return msg;
}

message_t scribelogger_message_new_nodup(char *message, char *category) {
	message_t msg = g_slice_new(struct message_st);
	msg->message = message;
	msg->category = category;
	return msg;
}

static void scribelogger_message_free(message_t msg)
{
	g_free(msg->message);
	g_free(msg->category);
	g_slice_free1(sizeof(struct message_st), msg);
}

static gpointer scribe_logging_func(gpointer data)
{
	scribelogger_t context = (scribelogger_t) data;
	g_async_queue_ref(context->queue);

	boost::shared_ptr<TSocket> socket(new TSocket(context->scribe_host, context->scribe_port));
	uint32_t timeout = 1000;
	socket->setConnTimeout(timeout);
    socket->setRecvTimeout(timeout);
    socket->setSendTimeout(timeout);
	boost::shared_ptr<TTransport> transport(new TFramedTransport(socket));
	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport, 0, 0, false, false));

	scribeClient client(protocol);
	while(!context->thread_shutdown) {
		try {
			transport->open();
		} catch(TTransportException &exception) {
			fprintf(stderr, "Unable to connect, sleeping for 5 seconds\n");
			sleep(5);
		}
	}

	std::vector<LogEntry> messages;
	while (!context->thread_shutdown) {
		message_t msg = (message_t) g_async_queue_pop(context->queue);
		//If msg->message is NULL, then we just got a wakeup message (so we can shutdown)
		if (msg->message) {
			LogEntry entry;
			entry.category = msg->category;
			entry.message = msg->message;
			scribelogger_message_free(msg);

			messages.push_back(entry);
			ResultCode r = client.Log(messages);
			if (r == OK) {
				messages.clear();
			}
		}
	}

	g_async_queue_unref(context->queue);
	try {
		transport->close();
	} catch(TTransportException &exception) {
	}

	return NULL;
}

scribelogger_t scribelogger_init(const char *host, short port)
{
	scribelogger_t context;

	if (!g_thread_supported()) {
		g_thread_init(NULL);
	}

	context = g_new0(struct scribelogger_st, 1);
	context->scribe_host = g_strdup(host);
	context->scribe_port = port;

	context->queue = g_async_queue_new();
	context->logging_thread = g_thread_create(scribe_logging_func, context, true, NULL);
	return context;
}

void scribelogger_uninit(scribelogger_t context) {
	context->thread_shutdown = TRUE;
	message_t msg = scribelogger_message_new_nodup(NULL, NULL);
	g_async_queue_push(context->queue, msg);
	g_thread_join(context->logging_thread);
	scribelogger_message_free(msg);
	g_async_queue_unref(context->queue);
	g_free(context->scribe_host);
}


void scribelogger_send(scribelogger_t context, message_t msg) {
	g_async_queue_push(context->queue, msg);
}
