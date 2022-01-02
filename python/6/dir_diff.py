from os import listdir
from os.path import isfile, join
onlyfiles = [f for f in listdir(".") if isfile(join(".", f))]


f = open("result.txt", "w+")
lines = f.readlines()

for file in onlyfiles:
    if file not in lines:
        if "mp3" in file:
            f.writelines(file.split(".")[0] + "\n")
        else:
            continue

f.close()
