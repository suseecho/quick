#!/bin/bash
echo -e "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
echo -e "<!DOCTYPE wallpapers SYSTEM \"gnome-wp-list.dtd\">"
echo -e "<wallpapers>"
echo -e " <wallpaper deleted=\"false\">"
echo -e "  <name>ECHO WALLPAPERS</name>"
echo -e "  <filename>/usr/share/backgrounds/contest/xenial.xml</filename>"
echo -e "  <options>zoom</options>"
echo -e " </wallpaper>"
let index=0
for files in `ls .`:
do
	postfix=`echo $files | cut -d "." -f 2`
	if [ $postfix = "jpg" -o $postfix = "png"  ]
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
	echo -e "<wallpaper>"
	echo -e "  <name>${pic[$index]}</name>"
	echo -e "  <filename>$PWD/${pic[$index]}</filename>"
	echo -e "  <options>zoom</options>"
	echo -e "  <pcolor>#000000</pcolor>"
	echo -e "  <scolor>#000000</scolor>"
	echo -e "  <shade_type>solid</shade_type>"
	echo -e " </wallpaper>"
	let index+=1
	let i+=1

done
echo -e "</wallpapers>"
