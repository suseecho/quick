old=$IFS
IFS=$'\n'
for dir in `ls .`
do
	if [ -d $dir ]
	then
	cd $dir
	enconv -x utf-8 *
	cd ..
	fi
done

