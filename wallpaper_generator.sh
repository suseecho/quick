#!/bin/bash
d=$(date)
echo -e "<background>"
echo -e "\t<starttime>"
echo -e "\t<year>$(date +%y)</year>"
echo -e "\t<month>$(date +%m)</month>"
echo -e "\t<day>$(date +%d)</day>"
echo -e "\t<hour>$(date +%H)</hour>"
echo -e "\t<minute>$(date +%M)</minute>"
echo -e "\t<second>$(date +%S)</second>"
echo -e "\t</starttime>"
let index=0
for files in `ls .`:
do
	postfix=`echo $files | cut -d "." -f 2`
	if [ $postfix = "jpg" ]
	then
		pic[$index]="$files"
		let index+=1
	fi
done
mod=$index
index=0
let i=1
while [[ $i -le $mod ]]
do
		echo -e "<static>"
		echo -e "\t\t\t<duration>180.0</duration>"
		echo -e "\t\t\t<file>$PWD/${pic[$index]}</file>"
		echo -e "</static>"
		echo -e "<transition>"
		echo -e "\t\t\t<duration>5.0</duration>"
		echo -e "\t\t\t<from>$PWD/${pic[$index]}</from>"
		let index+=1
		let i+=1
		echo -e "\t\t\t<to>$PWD/${pic[${index}%${mod}]}</to>"
		echo -e "</transition>"

done
echo -e "</background>"
