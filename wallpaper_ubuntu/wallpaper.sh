old=$IFS
IFS=$'\n'
./aa.sh > xenial.xml
./bb.sh > temp.txt
cp xenial.xml contest/.
cp temp.txt ../gnome-background-properties/xenial-wallpapers.xml

