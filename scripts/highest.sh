#!/bin/bash
file=../data/g28_lab05data_02.csv
output=../data/highest.csv
i=1
target=73 #this must be changed to 73
while [ $i -le 150 ]
do
	a=$(sed -n "$(((${target}-1)*150+${i}))s/^[^,]*,[^,]*,\([^,]*\),.*$/\1/p" ${file})
    if [ $(echo "$a < 300" | bc) -eq 1 ]
	then	
		echo $(sed -n "$(((${target}-1)*150+${i}))s/^\(.*\)/\1/p" ${file}) >> $output
	fi
	i=$(($i+1))
done
