#!/bin/bash
i=1
#filename=dummy.txt
touch ../data/g28_lab05data_02.csv
while [ $i -le 100 ]
do
	j=1
	while [ $j -lt 151 ]
	do
		../mybins/cs296_28_exe $i | sed -n 's/[a-zA-Z: ]*\([0-9][0-9.]*\).*$/\1/p' | sed -n "1s/^\(.*\)$/\1,${j}/p;2,6s/\(.*\)/\1/p" | sed -n '1h;1!H;$g;$s/\n/,/gp' >> ../data/g28_lab05data_02.csv
#		../mybins/cs296_28_exe $i | sed -n 's/[a-zA-Z: ]*\([0-9][0-9]*\).*$/\1/p' | sed -n "1s/^\(.*\)$/\1,${j}/p;2,6s/\(.*\)/\1/p" | sed -n '1h;1!H;$g;$s/\n/,/gp' >> ../data/g28_lab05data_02.csv
#		echo -n `sed -n '1s/.*: *\(.*\)$/\1/p' ${filename}` >> ../data/g28_lab05data_02.csv../mybins/cs296_28_exe 100 | sed -n 's/[a-zA-Z: ]*\([0-9][0-9.]*\).*$/\1/p' | sed -n "1s/^\(.*\)$/\1,${var}/p;2,6s/\(.*\)/\1/p" | sed -n '1h;1!H;$g;$s/\n/,/gp'
#		echo -n "," >> ../data/g28_lab05data_02.csv
#		echo -n ${j} >> ../data/g28_lab05data_02.csv
#		echo -n "," >> ../data/g28_lab05data_02.csv
#		echo -n `sed -n '2s/[a-zA-Z ]*\([0-9.]*\) ms$/\1/p' ${filename}` >> ../data/g28_lab05data_02.csv
#		echo -n "," >> ../data/g28_lab05data_02.csv
#		echo -n `sed -n '3s/[a-zA-Z ]*\([0-9.]*\) ms$/\1/p' ${filename}` >> ../data/g28_lab05data_02.csv
#		echo -n "," >> ../data/g28_lab05data_02.csv
#		echo -n `sed -n '4s/[a-zA-Z ]*\([0-9.]*\) ms$/\1/p' ${filename}` >> ../data/g28_lab05data_02.csv
#		echo -n "," >> ../data/g28_lab05data_02.csv
#		echo -n `sed -n '5s/[a-zA-Z ]*\([0-9.]*\) ms$/\1/p' ${filename}` >> ../data/g28_lab05data_02.csv
#		echo -n "," >> ../data/g28_lab05data_02.csv
#		echo `sed -n '7s/[a-zA-Z ]*\([0-9.]*\) ms$/\1/p' ${filename}` >> ../data/g28_lab05data_02.csv
		j=$(($j+1))
	done
		i=$(($i+1))
done
#rm -f ${filename}
