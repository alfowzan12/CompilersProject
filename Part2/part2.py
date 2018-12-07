import re
star = False
#a function to read the file and return a list of lines.
def readFile(filePath):
    f = open(filePath, "r")
    lines = f.readlines()
    return lines

def writingFile(lines ,new_filePath):
    global star
    show = False
    parenthesis = False
    f = open(new_filePath, "a")
    head, sep, tail = lines.partition(";")
    head = head.split()
    #print(head)
    stringToAppend = ""
    for token in head:
        if (token == "begin"):
            star = True
        if (token == "end"):
            star = False
        if (token == "show" and star == True):
            show = True
            print("True: " ,token)
            for showToken in head:

                if (showToken == "("):
                    parenthesis = True
                if (parenthesis == True and showToken != "(" and showToken != ")"):
                    new_list = ["print"]
                    new_list.append("(" + showToken + ")")
                    new_line = "".join(new_list)
                    f.write(new_line + "\n")
        if(star == True and token != "begin" and show != True):
            #print("".join(head))
            f.write("".join(head) + "\n")
            break






string = "show ( d18 )"
file_name = "new_text.txt"
text = readFile(file_name)
for line in text: #printing the lines before removing the spaces to test it.
    writingFile(line, "done.txt")
#s = "show (ab1) ;"
#m = re.search(r"\(([A-Za-z0-9_]+)\)", s)
#print(m.group(1))
