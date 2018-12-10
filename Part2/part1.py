#Fares, Steven, Animesh
import sys
import re

star = False


#a function to read the file and return a list of lines.
def readFile(filePath):
    f = open(filePath, "r")
    lines = f.readlines()
    return lines
# a function to remove all spaces.

def removeSpaces(lines, newTextPath):
    global star
    head, sep, tail = lines.partition('//')
    new_line = head.strip()
    new_line = re.sub(' +',' ',new_line)
    f = open(newTextPath, "a")
    new_line = new_line.split()
    new_list = []
    for token in new_line:
        print(star, " token:", token)
        if(token == "/*"):
            star = True
        if(token == "*/"):
            star = False
        if(star == False):
            if(token != "*/" and token != "/*"):
                if("show" in token):
                    print("HERE: ", token)
                    token = token.replace("show(", "show (")
                    print("AFTER: ", token)
                new_list.append(token)
    new_line = " ".join(new_list)
    if(new_line != ""):
        f.write(new_line + "\n")


filePath = "test.txt"
newTextPath = "finalp2.txt"
text = readFile(filePath)
i = 0
for line in text: #printing the lines before removing the spaces to test it.
    i = i + 1
    removeSpaces(line, newTextPath)
