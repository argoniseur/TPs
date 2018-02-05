#! /bin/sh

trap 'echo -e "\nbronze"' INT
trap 'exit 1' QUIT
while true
do

	date +%T
	sleep 1
done
