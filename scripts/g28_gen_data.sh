#!/bin/bash
i=1
while [ $i -le 100 ]
do
	j=1
	while [ $j -lt 151 ]
	do
#		touch ../data/g28out-${i}-${j}.txt
#		~/Desktop/cs296-28-lab05/mybins/cs296_28_exe $i > ~/Desktop/cs296-28-lab05/data/g28out-${i}-${j}.txt
#echo $PWD
		../mybins/cs296_28_exe $i > ../data/g28out-${i}-${j}.txt
		j=$(($j+1))
	done
	i=$(($i+1))
done
