#!/bin/bash

var=1
until
    echo $var
do
    (($var++))
    echo $var
done
