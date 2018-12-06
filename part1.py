#Fares, Steven, Animesh
import sys
import re

def readFile(filePath):
    f = open(filePath, "r")
    lines = f.readlines()
    return lines

def removeSpaces(lines):
    new_line = lines.strip()
    re.sub(' +',' ',new_line)
    print("new line ",i ,"!" ,new_line)


filePath = "/Users/faresalfowzan/Desktop/CSUF/323/Part1/test.txt"
text = readFile(filePath)
i = 0
for line in text:
    i = i + 1
    print("Line " ,i , ": ",line)
    removeSpaces(line)


string = re.sub(' +',' ','The     quick brown    fox')
print(string)
