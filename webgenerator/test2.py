import os

print('''<html>
<body>''')
handle=os.walk(".")
#temp=""
for root,dir,files in handle:
    for file in files:
        #temp=file
        if(file.split(".")[-1] == "mkv" or file.split(".")[-1] == "avi" or file.split(".")[-1] == "mp4" or file.split(".")[-1] == "MP4"):
            print("<p>视频</p>")
            print('''<video width="960" height="720" controls="controls" 
src="''',end="")
            print(file,end="")
            print('''"></video></object>''')
        if(file.split(".")[-1] == "jpg" or file.split(".")[-1] == "JPG" or file.split(".")[-1] == "PNG" or file.split(".")[-1] == "png"):
            print('''<img src="''',end="")
            print(file,end="")
            print('''"</img>''')
