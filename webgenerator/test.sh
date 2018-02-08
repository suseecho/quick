old=$IFS
IFS=$'\n'
for dir in `ls .`
do
    if [ -d $dir ]
    then
        cp test2.py $dir/test2.py
        echo $dir
        cd $dir
        python3 test2.py > test.html
        cd ..
    fi
done