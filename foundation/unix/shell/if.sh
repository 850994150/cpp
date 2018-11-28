#!/bin/bash
read var
if [ $var -gt 10 ]
then
    echo "$var > 10"
elif [ $var -lt 10 ]
then
    echo "$var < 10"
else
    echo "$var = 10"
fi
echo "script complete"
