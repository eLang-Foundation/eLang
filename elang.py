#!/usr/bin/python3

# importing argv
from sys import argv

# importing re
import re

# function for raising errors
def raiseError(errorType, error, line="", line_number=""):
    if line:
        print("File \"" + filename, end="\"")
        print(", line " + str(line_number))
        print("    " + line)
        print()
    print(errorType + ": " + error)
    exit(1)

filename = ""

# trying to get the filename
try:
    filename = argv[1]
except:
    print("Usage: elang filename.e")
    exit(1)

if filename == "--version":
    print("eLang 0.0.1")
    exit()

contents = ""

# getting the contents of the file
try:
    with open(filename, "r") as file:
        contents = file.read()
except:
    raiseError("eLang", "unable to open \"" + filename + "\"")

# splitting the code into lines
lines = contents.split("\n")

# a dictionary of eLang syntax
syntax = {"function": "function", "start": "{", "end": "}", "arguments_start": "(", "arguments_end": ")"}

# creating a dictionary that will contain all functions
functions = {}

# this function checks if quotes or brackets or a parentheses were closed
def check_closed(char, char_name="quote"):
    # counting the number of chars in the file
    count = contents.count(char)
    if char == "{":
        count += contents.count("}")
    elif char == "(":
        count += contents.count(")")
    elif char == "[":
        count += contents.count("]")
    # if the number is not even
    if count % 2 != 0:
        ln = ""
        line_number = None
        # get the line
        for line in list(reversed(lines)):
            if char in line:
                line_number = lines.index(line) + 1
                ln = line
                break
        # raise an error
        raiseError("SyntaxError", "Unclosed " + char_name, ln, line_number)

# all characters that should be a pair
chars = {"\"": "quote", "'": "quote", "{": "curly bracket", "(": "parentheses", "[": "square brackets"}

# checking each character for a presence of a pair
for char in chars:
    check_closed(char, chars[char])

def interpret(line):
    # splitting the line into keywords
    words = line.split()
    # if it is a function
    if words:
        if words[0] == syntax["function"]:
            # getting the body of the function
            index = len(functions) if functions else 0
            body = re.findall(r"{}([\w\W]*?){}".format(syntax["start"], syntax["end"]), contents)[index]
            # getting the name of the function
            function_name = re.findall(r"{}\s+(\w+)\s*{}".format(syntax["function"], syntax["arguments_start"].replace("(", "\(")), contents)[index]
            # creating a class that will store the function code
            class func:
                def __init__(self, body):
                    self.body = body
            # adding func class to a dictionary
            new_body = ""
            # removing whitespaces and saving the result in new_body
            for line in body.split("\n"):
                new_body += line.strip()
            # creating a class
            f = func(new_body)
            # saving the function
            functions[function_name] = f
        # if a function was called
        if re.match(r"\w+\s*\([\w\W]*\)", line):
            # trying to get the name of the function
            function_name = re.findall(r"(\w+)\s*\([\w\W]*\)", line)
            # if the name of the function was provided
            if function_name:
                function_name = function_name[0]
                # if function was already defined
                if function_name in functions:
                    eval(functions[function_name].body)
                else:
                    raiseError("NameError", "name \"" + function_name + "\" is not defined", line, lines.index(line) + 1)

# cycling through lines
for line in lines:
    interpret(line)

