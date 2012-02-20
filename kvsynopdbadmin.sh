#! /bin/sh

SQL=sqlite3
ETCDIR==`KVCONFIG --sysconfdir`/kvalobs
SQLDIR=`KVCONFIG --datadir`/kvsynopd/
LOGDIR=`KVCONFIG --logdir`/kvsynop/
DBFILE=`KVCONFIG --localstatedir`/lib/kvsynopd/kvsynopd.sqlite
LIBDIR=$(kvconfig --pkglibdir)

if [ ! -f "$LIBDIR/tool_funcs.sh" ]; then
	echo "Cant load: $LIBDIR/tool_funcs.sh"
	exit 1
fi

. $LIBDIR/tool_funcs.sh

#Exit if the machines do NOT hold the ipalias or is an test machine.
ipalias_status > /dev/null || exit 0 

DAY=`date '+%d'`
LOG=$LOGDIR/kvsynopdb-$DAY.log

echo -n "Start: " > $LOG
date >> $LOG
echo "--------------------------------------------------" >> $LOG 
$SQL $DBFILE  < $SQLDIR/cleansynopdb.sql >> $LOG  2>&1
echo "--------------------------------------------------" >> $LOG 
echo -n "Stop: " >> $LOG
date >> $LOG
