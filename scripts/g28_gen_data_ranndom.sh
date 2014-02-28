#!/bin/bash
touch ../data/g28_lab05data_random.csv
iter=1
while [ $iter -le 100 ]
do
	j=1
	sequence=$(seq 1 150 | shuf)
	for i in $sequence
	do
		if [ $j -eq 16 ]
		then break
    	fi
	echo $(sed -n "$(( (${iter}-1)*150+$i))p" ../data/g28_lab05data_02.csv) >> ../data/g28_lab05data_random.csv
	j=$((${j}+1))
	done
	iter=$((${iter}+1))
done

	

