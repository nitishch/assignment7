#!/bin/bash
touch ../data/g28_lab05data_01.csv
rerunno=1
#for j in $(ls ../data/*.txt)
while [ $rerunno -le 100 ]
do
	j=1
	while [ $j -le 150 ]
	do
		echo -n $(sed -n '1s/.*: *\([0-9.]*\)$/\1/p' ../data/g28out-${rerunno}-${j}.txt) >> ../data/g28_lab05data_01.csv
		echo -n "," >> ../data/g28_lab05data_01.csv
		echo -n ${j} >> ../data/g28_lab05data_01.csv
		echo -n "," >> ../data/g28_lab05data_01.csv
		echo -n $(sed -n '2s/[a-zA-Z ]*\([0-9.]*\) ms$/\1/p' ../data/g28out-${rerunno}-${j}.txt) >> ../data/g28_lab05data_01.csv
		echo -n "," >> ../data/g28_lab05data_01.csv
		echo -n $(sed -n '3s/[a-zA-Z ]*\([0-9.]*\) ms$/\1/p' ../data/g28out-${rerunno}-${j}.txt) >> ../data/g28_lab05data_01.csv
		echo -n "," >> ../data/g28_lab05data_01.csv
		echo -n $(sed -n '4s/[a-zA-Z ]*\([0-9.]*\) ms$/\1/p' ../data/g28out-${rerunno}-${j}.txt) >> ../data/g28_lab05data_01.csv
		echo -n "," >> ../data/g28_lab05data_01.csv
		echo -n $(sed -n '5s/[a-zA-Z ]*\([0-9.]*\) ms$/\1/p' ../data/g28out-${rerunno}-${j}.txt) >> ../data/g28_lab05data_01.csv
		echo -n "," >> ../data/g28_lab05data_01.csv
		echo $(sed -n '7s/[a-zA-Z ]*\([0-9.]*\) ms$/\1/p' ../data/g28out-${rerunno}-${j}.txt) >> ../data/g28_lab05data_01.csv
		j=$((${j}+1))
	done
	rerunno=$((${rerunno}+1))
done
