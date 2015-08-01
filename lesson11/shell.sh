#!/bin/bash

# Filename   : shell.sh
# Author     : X h y
# Version    : 1.0
# Date       : 07-30-2015

echo '#2.2'
a="hello Xhy"
b=5

echo "a is $a"
echo "b is $b"
echo -ne "\n"


echo '#2.3'
echo '$# is :' $#
echo '$* is :' $*
echo '$0 is :' $0
echo '$1 is :' $1
echo '$2 is :' $2
echo -ne "\n"


echo '#2.4'
var1=8
var2=4
var3=`expr $var1 / $var2`
var4=`expr $var1 - $var2`

echo $var3
echo $var4
echo -ne "\n"


echo '#2.5.1'
var=10
if [ $1 -gt $var ]
then
    echo 'the $1 is greater than 10'
else 
    echo 'the $1 is less than 10'
fi 
echo -ne "\n"


echo '#2.5.2'
list="Sun Mon Tue Wed Thur Fri Sat"
for day in $list
do
    echo $day
done
echo -ne "\n"


echo '#2.5.3'
var=$2
while [ $var -gt 0 ]
do
    echo $var
    var=`expr $var - 1`
done
echo -ne "\n"


echo '#2.6'
sed -n '3p' tmp.txt
sed -n '1,3p' tmp.txt

sed '3d' tmp.txt
sed '1,3d' tmp.txt

sed -n '/root/p' tmp.txt

sed '1c Hi' tmp.txt

#sed -i '$a bye' tmp.txt



echo '#2.7'
#last -n 5
last -n 5
echo -ne "\n"

#last -n 5  |awk '{print $1}'
last -n 5 | awk '{print $1}'
echo -ne "\n"

#last -n 5 | awk '{print $2}'
last -n 5 | awk '{print $2}'
echo -ne "\n"

#cat /etc/passwd | awk -F ':' '{print $1}'
cat /etc/passwd | awk -F ':' '{print $1}'
echo -ne "\n"

#awk -F ':' '$1=="root" {print $0}' /etc/passwd
awk -F ':' '$1=="root" {print $0}' /etc/passwd
echo -ne "\n"