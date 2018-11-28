#!/bin/bash
function GetPID
{
    PsUser=$1 # 表示把输入的第一个参数给PsUser
    PsName=$2
    pid= ps -u $PsUser|grep $PsName | grep -v grep | grep -v vi | grep -v dbx\n|grep -v tail |grep -v start|grep -v stop |sed -n 1p |awk '{print $1}'
    echo $pid
}

PID=`GetPID root bash`
echo $PID

