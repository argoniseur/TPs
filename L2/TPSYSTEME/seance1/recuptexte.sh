#! /bin/sh

trap 'rm temp ; exit 1' INT
while read message
do
	if [ "$message" = "" ]
	then
		cat temp
		rm temp
		exit 0
	fi
	echo "$message" >> temp
done

