#Fares, Steven, Animesh
import sys
import re
#a function to read the file and return a list of lines.
def readFile(filePath):
    f = open(filePath, "r")
    lines = f.readlines()
    return lines
# a function to remove all spaces.
def removeSpaces(lines):
    new_line = lines.strip()
    new_line = re.sub(' +',' ',new_line)
    print("new line ",i ,"!" ,new_line) #testing the output



filePath = "/Users/faresalfowzan/Desktop/CSUF/323/Part1/test.txt"
text = readFile(filePath)
i = 0
for line in text: #printing the lines before removing the spaces to test it.
    i = i + 1
    print("Line " ,i , ": ",line)
    removeSpaces(line)
