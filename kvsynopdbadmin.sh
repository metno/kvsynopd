#! /bin/sh

KVCONFIG=__KVCONFIG__

SQL=sqlite3
LOCAL_CONF_FILE=`$KVCONFIG --sysconfdir`/kvalobs/kvsynopd_dbclean.sql
ETCDIR=`$KVCONFIG --sysconfdir`/kvalobs
SQLDIR=`$KVCONFIG --datadir`/kvsynopd/
LOGDIR=`$KVCONFIG --logdir`/kvsynop/
DBFILE=`$KVCONFIG --localstatedir`/lib/kvsynopd/kvsynopd.sqlite
LIBDIR=`$KVCONFIG --pkglibdir`
SQLCLEAN=$SQLDIR/cleansynopdb.sql

#if [ ! -f "$LIBDIR/tool_funcs.sh" ]; then
#	echo "Cant load: $LIBDIR/tool_funcs.sh"
#	exit 1
#fi
#
#. $LIBDIR/tool_funcs.sh
#
#Exit if the machines do NOT hold the ipalias or is an test machine.
#ipalias_status > /dev/null || exit 0 

if [ -f $LOCAL_CONF_FILE ]; then
    SQLCLEAN=$LOCAL_CONF_FILE
fi

DAY=`date '+%d'`
LOG=$LOGDIR/kvsynopdb-$DAY.log

[ -f "$LOG" ] && rm -rf "$LOG" 

if [ ! -f "$DBFILE" ]; then
    echo "No dbfile: $DBFILE" >> $LOG  
    exit 0
fi

if [ ! -f "$SQLCLEAN" ]; then
    echo "No sqlclean file: $SQLCLEAN" >> $LOG
    exit 0
fi 

if ! which $SQL > /dev/null 2>&1; then
    echo "Cant find the program <$SQL>." >> $LOG
    exit 1
fi



echo -n "Start: " >> $LOG
date >> $LOG
echo "Clean script: $SQLCLEAN" >> $LOG
echo "Sqlite db: $DBFILE" >> $LOG
echo "--------------------------------------------------" >> $LOG 
$SQL $DBFILE  < $SQLCLEAN >> $LOG  2>&1
echo "--------------------------------------------------" >> $LOG 
echo -n "Stop: " >> $LOG
date >> $LOG
