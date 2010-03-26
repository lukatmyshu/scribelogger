#!/bin/sh

APPNAME=scribelogger
VERSION=`awk '/^Version/ {print $2;}' $APPNAME.spec`
RPMBUILDDIR=`rpm --eval "%{_topdir}"`

export CFLAGS="-ggdb $CFLAGS"
rm -rf $RPMBUILDDIR/SOURCES/$APPNAME-$VERSION
cp -pRd . $RPMBUILDDIR/SOURCES/$APPNAME-$VERSION
cp controller.logrotate $RPMBUILDDIR/SOURCES/
BASEDIR=$RPMBUILDDIR/SOURCES/$APPNAME-$VERSION
cd $BASEDIR
./autogen.sh
make -C $RPMBUILDDIR/SOURCES/$APPNAME-$VERSION distclean
cd -
tar -C $RPMBUILDDIR/SOURCES -zcf $RPMBUILDDIR/SOURCES/$APPNAME-$VERSION.tar.gz $APPNAME-$VERSION
rm -rf $BASEDIR
rpmbuild -ba --clean --rmsource $APPNAME.spec
