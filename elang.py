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
    print("eLang 0.0.6")
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

# characters in eLang that should have a pair
chars = {"\"": "quote", "'": "quote", syntax["start"]: "curly bracket", syntax["end"]: "close curly bracket", syntax["arguments_start"]: "parentheses", syntax["arguments_end"]: "close parentheses", "[": "square brackets", "]": "close square brackets"}

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
    counter = contents.count(char)
    try:
        counter += contents.count(list(chars.keys())[list(chars.values()).index("close " + char_name)])
    except: pass
    # if the number is not even
    if counter % 2 != 0:
        # getting the line to display the error
        ln = ""
        line_number = None
        # get the line
        for line in list(reversed(lines)):
            if char in line:
                line_number = lines.index(line) + 1
                ln = line
                break
        raiseError("SyntaxError", "Unclosed " + char_name, ln, line_number)

# this function finds indexes at which the given string is places in the given string
# (I have no idea how this code works because I just copied it from StackOverflow https://stackoverflow.com/a/4665027)
def find_all(a_str, sub):
    start = 0
    while True:
        start = a_str.find(sub, start)
        if start == -1: return
        yield start
        start += len(sub)

# this function returnes true if the character at given index inside of given string is a string
def inside_quotes(index, line):
    # sorry for my terrible English
    # if there are no double or single quotes they are closed
    closed_single_quote = True
    closed_double_quote = True
    # cycling through each character in the given string until the given index
    for i in range(len(line[:index])):
        slash = line[i-1] == "\\"
        # if char is equal to " and it is not inside of a string and it doesn't have a slash before it
        if line[i] == "\"" and closed_single_quote and not slash:
            # the double quotes are opened if they were closed and they are closed if they were opened
            closed_double_quote = not closed_double_quote
        # if char is equal to ' and it is not inside of a string and it doesn't have a slash before it
        if line[i] == "'" and closed_double_quote and not slash:
            # the signgle quotes are opened if they were closed and they are closed if they were opened
            closed_double_quote = not closed_double_quote
    # if single quotes and double quotes are closed
    if closed_single_quote and closed_double_quote:
        return False
    # if not
    return True

# a dictionary of elang built-in functions
elang_functions = {"print": "print"}

ignore = False

def interpret(line):
    global ignore
    # splitting the line into keywords
    words = line.split()
    # if it is a function
    if words:
        if not ignore:
            if words[0] == syntax["function"]:
                # getting the name of the function
                function_name = re.findall(r"{}\s+([\w_\d]+)\s*".format(syntax["function"]), line)[0]
                # getting the body of the function
                try: body = re.findall(r"{}\s+{}[\(\)\s\w]*{}([\w\W]*?){}".format(syntax["function"], function_name, syntax["start"], syntax["end"]), contents)[0]
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
                ignore = True
                if "\n" not in body:
                    ignore = False
            # if a function was called
            elif re.match(r"\w+\s*\([\w\W]*\)", line):
                # trying to get the name of the function
                function_name = re.findall(r"([\w_\d]+)\s*\{}[\w\W]*\{}".format(syntax["arguments_start"], syntax["arguments_end"]), line)[0]
                # getting the arguments
                arguments = re.findall(r"{}\{}([\w\W]*?)\{}".format(function_name, syntax["arguments_start"], syntax["arguments_end"]), line)[0]
                
                # list of arguments will be stored in this variable
                args = []

                if arguments:
                    # this variable will store the argument
                    argument = ""
                    # cycling through each character in arguments
                    for i in range(len(arguments)):
                        if not(not inside_quotes(i, arguments) and arguments[i] == ","):
                            argument += arguments[i]
                        if (not inside_quotes(i, arguments) and arguments[i] == ",") or i == len(arguments)-1:
                            args.append(argument.strip())
                            argument = ""
                # if the name of the function was provided
                if function_name:
                    # if function was defined by the user
                    if function_name in functions:
                        # getting the function
                        function = functions[function_name]
                        # getting the body of the function
                        body = function.body
                        # replacing the argument variables with given arguments
                        for arg in function.arguments:
                            # if argument is not an empty string
                            if arg:
                                # getting the given argument
                                argument = args[function.arguments.index(arg)]
                                # the following code is replacing variables in code with the arguments
                                for index in list(find_all(body, arg)):
                                    # if variable is not inside of quotes
                                    if not inside_quotes(index, body):
                                        # replacing it with the argument
                                        body = body.replace(arg, argument)
                        # trying to execute the block of code
                        for line in body.split("\n"):
                            interpret(line)
                    # if this functions is a elang built-in function
                    elif function_name in elang_functions:
                        # if the function is print
                        if elang_functions[function_name] == "print":
                            # if arguments were given
                            if arguments:
                                # creating an empty string variable to which we'll be adding arguments
                                string = ""
                                # cycling through each argument in arguments
                                for argument in args:
                                    # if argument is a string
                                    if argument[0] == "\"" or argument[0] == "'" and argument[0] == "\"" or argument[0] == "'":
                                        # adding the argument to the string and removing the quotes
                                        string += argument[1:-1] + " "
                                # printing out the string
                                print(string.strip().replace(r"\n", "\n").replace(r"\t", "\t").replace(r"\r", "\r").replace(r"\"", "\""), end="")
                            # printing the new line
                            print()
                    # if this function is not an elang function and it was not defined by the user
                    else:
                        raiseError("NameError", "name \"" + function_name + "\" is not defined", line, lines.index(line))
            else:
                # trying to execute the line of code
                try:
                    eval(line)
                except: pass

# main function
def main():
    # making this variables accessible
    global ignore
    # checking each character for a presence of a pair
    for char in chars:
        if not chars[char].startswith("close"): check_closed(char, chars[char])
    # cycling through lines
    for line in lines:
        wait = 0
        # checking, if the following code is still inside of a function
        if ignore:
            for i in range(len(line)):
                # if the character represents the start of a code block and it is not a string
                if line[i] == syntax["start"] and not inside_quotes(i, line):
                    closed_curly_bracket = False
                    wait += 1
                if line[i] == syntax["end"] and not inside_quotes(i, line):
                    if wait: wait -= 1
                    else: ignore = False        
        interpret(line)

# calling the main function
if __name__ == "__main__":
    main()

