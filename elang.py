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
    print("eLang 0.0.5")
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

# this is a class for functions
class func:
    def __init__(self, arguments, body):
        self.arguments = arguments
        self.body = body

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

def find_all(a_str, sub):
    start = 0
    while True:
        start = a_str.find(sub, start)
        if start == -1: return
        yield start
        start += len(sub)

# all characters that should have a pair
chars = {"\"": "quote", "'": "quote", "{": "curly bracket", "(": "parentheses", "[": "square brackets"}

# a dictionary of elang built-in functions
elang_functions = {"print": "print"}

ignore = False

def interpret(line):
    global function
    # splitting the line into keywords
    words = line.split()
    # if it is a function
    if words:
        if not ignore:
            if words[0] == syntax["function"]:
                index = len(functions) if functions else 0
                # getting the name of the function
                function_name = re.findall(r"{}\s+([\w_\d]+)\s*".format(syntax["function"]), contents)[index]
                # getting the body of the function
                try: body = re.findall(r"{}\s+{}[\w\W]*[\w\d\s,]*[\w\W]*\s*{}([\w\W]*?){}".format(syntax["function"], function_name, syntax["start"], syntax["end"]), contents)[0]
                except: raiseError("SyntaxError", "code block not provided", line, lines.index(line)+1)
                new_body = ""
                # removing whitespaces and saving the result in new_body
                for line in body.split("\n"):
                    new_body += line.strip()
                # getting the arguments
                try: arguments = re.findall(r"{}\s+{}\s*\{}([\w\W]*?)\{}".format(syntax["function"], function_name, syntax["arguments_start"], syntax["arguments_end"]), contents)[0]
                except: arguments = ""
                # creating a class
                f = func(arguments.split(","), new_body)
                # saving the function
                functions[function_name] = f
                function = True
                if "\n" not in body:
                    function = False
            # if a function was called
            elif re.match(r"\w+\s*\([\w\W]*\)", line):
                # trying to get the name of the function
                function_name = re.findall(r"(\w+)\s*\([\w\W]*\)", line)
                # getting the arguments
                arguments = re.findall(r"{}\{}([\w\W]*?)\{}".format(function_name, syntax["arguments_start"], syntax["arguments_end"]), line)[0]
                
                # list of arguments will be stored in this variable
                args = []

                if arguments:
                    # variables needed to check if the quotes are closed
                    closed_single_quote = True
                    closed_double_quote = True

                    # this variable will store the argument
                    argument = ""
                    # cycling through each character in arguments
                    for i in range(len(arguments)):
                        # adding character to argument
                        if closed_double_quote and closed_single_quote:
                            if arguments[i] != ",":
                                argument += arguments[i]
                        else: argument += arguments[i]
                        slash = arguments[i-1] == "\\"
                    
                        # checking if single quotes are closed
                        if not slash and arguments[i] == "'" and closed_double_quote:
                            closed_single_quote = not closed_single_quote
                        # checking if double quotes are closed
                        if not slash and arguments[i] == "\"" and closed_single_quote:
                            closed_double_quote = not closed_double_quote
                        # adding argument to arguments list
                        if closed_double_quote and closed_single_quote: 
                            if arguments[i] == "," or i == len(arguments)-1:
                                args.append(argument.strip())
                                argument = ""
                            if arguments[i] == "+":
                                for char in contents:
                                    pass
                # if the name of the function was provided
                if function_name:
                    function_name = function_name[0]
                    # if function was already defined
                    if function_name in functions:
                        # getting the function
                        function = functions[function_name]
                        # getting the body of the function
                        body = function.body
                        # replacing the argument variables with given arguments
                        for arg in function.arguments:
                            if arg:
                                argument = args[function.arguments.index(arg)]
                                for index in list(find_all(body, arg)):
                                    body_until_index = body[:index]
                                    if body_until_index.count("\"") % 2 == 0 and body_until_index.count("'") % 2 == 0:
                                        body = body.replace(arg, argument)
                        # trying to execute the block of code
                        for line in body.split("\n"):
                            interpret(line)
                    # if this functions is a elang built-in function
                    elif function_name in elang_functions:
                        if elang_functions[function_name] == "print":
                            if arguments:
                                string = ""
                                for argument in args:
                                    if argument[0] == "\"" or argument[0] == "'" and argument[0] == "\"" or argument[0] == "'":
                                        string += argument[1:-1] + " "
                                print(string.strip(), end="")
                            print()
                    # if this function is not an elang function and it was not defined by the user
                    else:
                        raiseError("NameError", "name \"" + function_name + "\" is not defined", line, lines.index(line))
            else:
                # trying to execute the line of code
                try:
                    pass
                    # eval(line)
                except: pass

# main function
def main():
    # making this variables accessible
    global ignore
    # defining variables needed to check if the line of code is inside of a function
    closed_double_quote = True
    closed_single_quote = True
    closed_curly_bracket = True
    wait = 0
    # checking each character for a presence of a pair
    for char in chars:
        check_closed(char, chars[char])
    # cycling through lines
    for line in lines:
        # checking, if the following code is still inside of a function
        if ignore:
            for char in line:
                if char == "\"" and closed_single_quote and contents[contents.index(char)-1] != "\\":
                    closed_double_quote = not closed_double_quote
                elif char == "'" and closed_double_quote and contents[contents.index(char)-1] != "\\":
                    closed_single_quote = not closed_single_quote
                elif char == syntax["start"] and closed_single_quote and closed_double_quote:
                    closed_curly_bracket = False
                    if function: wait += 1
                elif char == syntax["end"] and closed_single_quote and closed_double_quote:
                    if wait: wait -= 1
                    else:
                        ignore = False
                        closed_curly_bracket = True
        interpret(line)

# calling the main function
if __name__ == "__main__":
    main()

