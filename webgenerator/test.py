import os
print('''<html>
<body>''')
handle=os.walk(".")
i = 0
for root,dir,file in handle:
    for mydir in dir:
        print('''<p><a href="./''',end="")
        print(mydir,end="")
        print('''/test.html''',end="")
        print('''">''',end="")
        print(mydir,end="")
        print("</a></p>")

print('''</body>
</html>''')