#! /bin/sh

SQL=sqlite3
ETCDIR==`KVCONFIG --sysconfdir`/kvalobs
SQLDIR=`KVCONFIG --datadir`/kvsynopd/
LOGDIR=`KVCONFIG --logdir`/kvsynop/
DBFILE=`KVCONFIG --localstatedir`/lib/kvsynopd/kvsynopd.sqlite

has_alias()
{
	aliasname=$1
	if [ -f /usr/local/sbin/alias_list ]; then
		/usr/local/sbin/alias_list | /bin/grep -q $aliasname
		return $?
	fi
	return 1
}

(test -f "$ETCDIR/KVALOBS_TEST") || has_alias kvalobs || die


DAY=`date '+%d'`
LOG=$LOGDIR/kvsynopdb-$DAY.log

echo -n "Start: " > $LOG
date >> $LOG
echo "--------------------------------------------------" >> $LOG 
$SQL $DBFILE  < $SQLDIR/cleansynopdb.sql >> $LOG  2>&1
echo "--------------------------------------------------" >> $LOG 
echo -n "Stop: " >> $LOG
date >> $LOG
