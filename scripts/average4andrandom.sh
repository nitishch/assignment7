#!/bin/bash
#bc <<< "scale=5;"
j=1
file4=../data/g28_lab05data_02.csv
filerand=../data/g28_lab05data_random.csv
touch ../data/average4andrandom.csv
while [ $j -le 100 ]
do
	steptime4=0
	steptimerandom=0
#	colltime=0
#	veltime=0
#	postime=0
#	looptime=0
	rerun=1
	while [ $rerun -le 150 ]
	do
		line=$(((${j}-1)*150+${rerun}))
#		echo $line
		stepadder4=$(echo -n $(sed -n "${line}s/^[^,]*,[^,]*,\([^,]*\),.*$/\1/p" ${file4}) )
#		stepadderrandom=$(echo -n $(sed -n "${line}s/^[^,]*,[^,]*,\([^,]*\),.*$/\1/p" ${filerand}) )
#		stepadder=$(echo -n $(sed -n "$(( ($j-1)*150+${rerun} ))s/^[^,]*,[^,]*,\([^,]*\),.*$/\1/p" ${file}) )
#		colladder=$(echo -n $(sed -n "${line}s/^[^,]*,[^,]*,[^,]*,\([^,]*\),.*$/\1/p" ${file}) )
#		veladder=$(echo -n $(sed -n "${line}s/^[^,]*,[^,]*,[^,]*,[^,]*,\([^,]*\),.*$/\1/p" ${file}) )
#		posadder=$(echo -n $(sed -n "${line}s/^[^,]*,[^,]*,[^,]*,[^,]*,[^,]*,\([^,]*\),.*$/\1/p" ${file}) )
#		loopadder=$(echo -n $(sed -n "${line}s/^[^,]*,[^,]*,[^,]*,[^,]*,[^,]*,[^,]*,\([^,]*\).*$/\1/p" ${file}) )
#	if [ $(echo "scale=5; $colladder < 300" | bc) -eq 1 ]
#	then		
#		colltime=$(echo "scale=5; ${colltime}+${colladder}" | bc)
#	fi	
#	if [ $(echo "scale=5; $veladder < 300" | bc) -eq 1 ]
#	then		
#		veltime=$(echo "scale=5; ${veltime}+${veladder}" | bc)
#	fi	
#	if [ $(echo "scale=5; $posadder < 300" | bc) -eq 1 ]
#	then		
#		postime=$(echo "scale=5; ${postime}+${posadder}" | bc)
#	fi	
#	if [ $(echo "scale=5; $loopadder < 300" | bc) -eq 1 ]
#	then		
#		looptime=$(echo "scale=5; ${looptime}+${loopadder}" | bc)
#	fi	
	if [ $(echo "scale=5; $stepadder4 < 300" | bc) -eq 1 ]
	then
		steptime4=$(echo "scale=5; ${steptime4}+${stepadder4}" | bc)
#		steptimerandom=$(echo "scale=5; ${steptimerandom}+${stepadderrandom}" | bc)
	fi
#		echo "scale=5; ;aiwo"
		rerun=$((${rerun}+1))
	done
	rerun=1
	while [ $rerun -le 15 ]
	do
		line=$(((${j}-1)*15+${rerun}))
#		echo $line
#		stepadder4=$(echo -n $(sed -n "${line}s/^[^,]*,[^,]*,\([^,]*\),.*$/\1/p" ${file4}) )
		stepadderrandom=$(echo -n $(sed -n "${line}s/^[^,]*,[^,]*,\([^,]*\),.*$/\1/p" ${filerand}) )
#		stepadder=$(echo -n $(sed -n "$(( ($j-1)*150+${rerun} ))s/^[^,]*,[^,]*,\([^,]*\),.*$/\1/p" ${file}) )
#		colladder=$(echo -n $(sed -n "${line}s/^[^,]*,[^,]*,[^,]*,\([^,]*\),.*$/\1/p" ${file}) )
#		veladder=$(echo -n $(sed -n "${line}s/^[^,]*,[^,]*,[^,]*,[^,]*,\([^,]*\),.*$/\1/p" ${file}) )
#		posadder=$(echo -n $(sed -n "${line}s/^[^,]*,[^,]*,[^,]*,[^,]*,[^,]*,\([^,]*\),.*$/\1/p" ${file}) )
#		loopadder=$(echo -n $(sed -n "${line}s/^[^,]*,[^,]*,[^,]*,[^,]*,[^,]*,[^,]*,\([^,]*\).*$/\1/p" ${file}) )
#	if [ $(echo "scale=5; $colladder < 300" | bc) -eq 1 ]
#	then		
#		colltime=$(echo "scale=5; ${colltime}+${colladder}" | bc)
#	fi	
#	if [ $(echo "scale=5; $veladder < 300" | bc) -eq 1 ]
#	then		
#		veltime=$(echo "scale=5; ${veltime}+${veladder}" | bc)
#	fi	
#	if [ $(echo "scale=5; $posadder < 300" | bc) -eq 1 ]
#	then		
#		postime=$(echo "scale=5; ${postime}+${posadder}" | bc)
#	fi	
#	if [ $(echo "scale=5; $loopadder < 300" | bc) -eq 1 ]
#	then		
#		looptime=$(echo "scale=5; ${looptime}+${loopadder}" | bc)
#	fi	
	if [ $(echo "scale=5; $stepadderrandom < 300" | bc) -eq 1 ]
	then
#		steptime4=$(echo "scale=5; ${steptime4}+${stepadder4}" | bc)
		steptimerandom=$(echo "scale=5; ${steptimerandom}+${stepadderrandom}" | bc)
	fi
#		echo "scale=5; ;aiwo"
		rerun=$((${rerun}+1))
	done
	
#	(( steptime = $(echo "scale=5; $steptime > 300" | bc)?$(echo "scale=5; $steptime/150" | bc):$steptime ))
#	if [ $(echo "scale=5; $steptime < 300" | bc) ]
#	then
	steptime4=$(echo "scale=5; $steptime4/150" | bc)
	steptimerandom=$(echo "scale=5; $steptimerandom/150" | bc)
#	fi
#	echo $steptime		
#	colltime=$(echo "scale=5; $colltime/150" | bc)
#	veltime=$(echo "scale=5; $veltime/150" | bc)
#	postime=$(echo "scale=5; $postime/150" | bc)
#	looptime=$(echo "scale=5; $looptime/150" | bc)
	echo "$j,$steptime4,$steptimerandom" >> ../data/average4andrandom.csv #$colltime,$veltime,$postime,$looptime" >> ../data/average.csv
	j=$(($j+1))
done
