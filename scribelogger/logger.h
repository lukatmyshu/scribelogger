#ifndef SCRIBELOGGER_LOGGER_H
#define SCRIBELOGGER_LOGGER_H

typedef struct scribelogger_st *scribelogger_t;

struct message_st {
	char *message;
	char *category;
};

typedef struct message_st *message_t;

scribelogger_t scribelogger_init(const char *host, short port);

void scribelogger_uninit(scribelogger_t);

message_t scribelogger_message_new(const char *msg, const char *category);

message_t scribelogger_message_new_nodup(char *msg, char *category);

void scribelogger_send(scribelogger_t, message_t msg);

#endif
