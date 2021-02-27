#!/usr/bin/python3

# importing argv
from sys import argv

# importing re
import re


# function for raising errors
def raiseError(errorType, error, line="", line_number=None):
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
    print("Usage: elang filename.elang")
    exit(1)

if filename == "--version":
    print("eLang 0.0.9 (Python)")
    exit(0)

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
chars = {"\"": "double quote", "'": "single quote", syntax["start"]: "curly bracket",
         syntax["end"]: "close curly bracket",
         syntax["arguments_start"]: "parentheses", syntax["arguments_end"]: "close parentheses", "[": "square brackets",
         "]": "close square brackets"}

# this is a dictionary of elang built-in functions
elang_functions = {"print": "print"}

# this is a dictionary that will contain all functions
functions = {}

# this is a dictionary of variables
variables = {}


# this is a class for functions
class Function:
    def __init__(self, arguments, body):
        self.arguments = arguments
        self.body = body


# this function checks if quotes or brackets or a parentheses were closed
def checkClosed(char, char_name="quote"):
    # counting the number of chars in the file
    counter = 0
    for i in range(len(contents)):
        if contents[i] == char:
            if not insideQuotes(i, contents):
                counter += 1
            else:
                if not insideQuotes(i + 1, contents):
                    counter += 1
    try:
        char_close = list(chars.keys())[list(chars.values()).index("close " + char_name)]
        for i in range(len(contents)):
            if contents[i] == char_close:
                if not insideQuotes(i, contents):
                    counter += 1
    except:
        pass
    # if the number is not even
    if counter % 2 != 0 and counter != 0:
        # getting the line to display the error
        ln = ""
        line_number = None
        # get the line
        for line in list(reversed(lines)):
            if char in line:
                line_number = lines.index(line) + 1
                ln = line
                break
        # raising the error
        raiseError("SyntaxError", "Unclosed " + char_name, ln, line_number)


# this function finds indexes at which the given string is places in the given string
# (I have no idea how this code works because I just copied it from StackOverflow https://stackoverflow.com/a/4665027)
def findAll(a_str, sub):
    start = 0
    while True:
        start = a_str.find(sub, start)
        if start == -1: return
        yield start
        start += len(sub)


# this function returns true if the character at given index inside of given string is a string
def insideQuotes(index, line):
    # sorry for my terrible English
    # if there are no double or single quotes they are closed
    closed_single_quote = True
    closed_double_quote = True
    # cycling through each character in the given string until the given index
    for i in range(len(line[:index])):
        slash = line[i - 1] == "\\"
        # if char is equal to " and it is not inside of a string and it doesn't have a slash before it
        if line[i] == "\"" and closed_single_quote and not slash:
            # the double quotes are opened if they were closed and they are closed if they were opened
            closed_double_quote = not closed_double_quote
        # if char is equal to ' and it is not inside of a string and it doesn't have a slash before it
        if line[i] == "'" and closed_double_quote and not slash:
            # the single quotes are opened if they were closed and they are closed if they were opened
            closed_single_quote = not closed_single_quote
    # if single quotes and double quotes are closed
    if closed_single_quote and closed_double_quote:
        return False
    # if not
    return True


# this function returns the contents of a code block or a list or a dictionary or a string
def getContents(index, code):
    # getting the code we'll be working with
    code = code[index + 1:]
    # getting the character
    character = code[index + 1]
    # initializing return_value variable
    return_value = ""
    # if character indicates that this is a string
    if character == "\"" or character == "'":
        escape = False
        # cycling through each character in code
        for char in code:
            # if character is back slash the next character is an escape character
            if character == "\\":
                escape = True
            # if the character is not a double quote or a single quote
            if char != character:
                # adding the character to return value
                return_value += char
            # if the character is a double quote or a single quote
            else:
                # if it is not an escape character
                if not escape:
                    # return the return value
                    return return_value
                # if the character is an escape character
                else:
                    # adding character to the return value
                    return_value += char
                    # the next character will not be an escape character
                    escape = False
    # if character is a character that starts a code block
    if character == syntax["start"]:
        wait = 0
        # cycling through each character in code
        for char in code:
            # if character does not represent the end of the code block
            if char != syntax["end"]:
                if char == syntax["start"]:
                    if not insideQuotes(code.index(char), code):
                        wait += 1
                # adding the character to the return value
                return_value += char
            # if character represents the end of the code block
            else:
                # if it is not inside of quotes
                if not insideQuotes(code.index(char), code):
                    if wait == 0:
                        # return the return value
                        return return_value
                    else:
                        wait -= 1
                # if the character is not inside of quotes
                else:
                    # adding the character to the return value
                    return_value += char
    # if character is a character that represents the start of arguments
    if character == syntax["arguments_start"]:
        # cycling through each character in code
        for char in code:
            # if character does not represent the end of the arguments
            if char != syntax["arguments_end"]:
                # adding the character to the return value
                return_value += char
            # if character represents the end of the arguments
            else:
                # if character is not inside of quotes
                if not insideQuotes(code.index(char), code):
                    # return the return value
                    return return_value
                # if the character is not inside of quotes
                else:
                    # adding the character to the return value
                    return_value += char
    # returning the return value if not already returned
    return return_value


ignore = False


def interpret(line, after=""):
    global ignore, variables, contents
    # splitting the line into keywords
    words = line.split()
    # if it is a function
    if words:
        if not ignore:
            if words[0] == syntax["function"]:
                # getting the name of the function
                function_name = re.findall(r"{}\s+([\w_\d]+)\s*".format(syntax["function"]), after)[0]
                # trying to get the body of the function
                for character in after[after.index(function_name) + len(function_name):]:
                    if character == "(":
                        continue
                    elif character in ["\n", "\t", " "]:
                        continue
                    else:
                        index = line.find(function_name) + len(function_name)
                        line = line[:index] + "()" + line[index:]
                        index = after.find(function_name) + len(function_name)
                        after = after[:index] + "()" + after[index:]
                        break
                # regex pattern for getting body of the function
                pattern = r"\s+" + re.escape(function_name) + r"\s*\([\w\W]*?\)\s*\{([\w\W]*?)\}"
                # getting the body of the function
                body = re.findall(pattern, after)[0]
                # this variable will store the body of the function without whitespaces
                new_body = ""
                # removing whitespaces and saving the result in new_body
                for line in body.split("\n"):
                    new_body += line.strip()
                # getting the arguments
                pattern = r"{}\s+{}\s*{}\s*([\w\W]*?)\s*{}".format(syntax["function"], re.escape(function_name),
                                                                   re.escape(syntax["arguments_start"]),
                                                                   re.escape(syntax["arguments_end"]))
                try:
                    arguments = re.findall(pattern, after)[0]
                except:
                    arguments = ""
                # creating a class
                f = Function(arguments.split(","), new_body)
                # saving the function
                functions[function_name] = f
                # you should ignore the next line of code because it will be inside of a function
                ignore = True
                if "\n" not in body:
                    ignore = False
            # if a function was called
            elif re.match(r"\w+\s*\([\w\W]*\)", line):
                # trying to get the name of the function
                function_name = re.findall(r"([\w_\d]+)\s*{}[\w\W]*{}".format(re.escape(syntax["arguments_start"]),
                                                                              re.escape(syntax["arguments_end"])),
                                           line)[0]
                if insideQuotes(line.index(function_name), line):
                    return
                # getting the arguments
                arguments = re.findall(
                    r"{}\s*{}\s*([\w\W]*?)?{}".format(re.escape(function_name), re.escape(syntax["arguments_start"]),
                                                      re.escape(syntax["arguments_end"])), after)[0]
                # list of arguments will be stored in this variable
                args = []

                if arguments:
                    # this variable will store the argument
                    argument = ""
                    # cycling through each character in arguments
                    for i in range(len(arguments)):
                        if not insideQuotes(i, arguments) and arguments[i] == ",":
                            args.append(argument.strip())
                            argument = ""
                        else:
                            argument += arguments[i]
                        if i == len(arguments) - 1:
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
                                for index in list(findAll(body, arg)):
                                    # if variable is not inside of quotes
                                    if not insideQuotes(index, body):
                                        # replacing it with the argument
                                        body = body.replace(arg, argument)
                        # executing the block of code
                        lns = body.split("\n")
                        for i in range(len(lns)):
                            line = lns[i]
                            after = ""
                            after_list = lns[i - 1:] if i > 0 else lns[0:]
                            for ln in after_list:
                                after += ln + "\n"
                            interpret(line, after)

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
                                    a_string = False
                                    for index in range(len(argument[1:-1])):
                                        a_string = insideQuotes(index, argument)
                                    # if argument is a string
                                    if a_string:
                                        # adding the argument to the string and removing the quotes
                                        string += argument[1:-1] + " "
                                    else:
                                        if argument in variables:
                                            a = variables[argument]
                                            s = False
                                            for index in range(len(a[1:-1])):
                                                s = insideQuotes(index + 1, a)
                                            if s:
                                                string += a[1:-1] + " "
                                            else:
                                                string += a + " "
                                        else:
                                            raiseError("NameError", "name \"" + argument + "\" is not defined", line,
                                                       contents.split("\n").index(line) + 1)
                                # printing out the string
                                print(string.replace(r"\n", "\n").replace(r"\t", "\t").replace(r"\r", "\r")
                                      .replace(r"\"", "\"").replace(r"\'", "'"),
                                      end="")
                            # printing the new line
                            print()
                    # if this function is not an elang function and it was not defined by the user
                    else:
                        raiseError("NameError", "name \"" + function_name + "\" is not defined", line,
                                   contents.split("\n").index(line) + 1)
            else:
                if "=" in line:
                    index = line.index("=")
                    variable_name = line[:index].strip()
                    value = line[index + 1:].strip()
                    variables[variable_name] = value


# main function
def main():
    # making this variables accessible
    global ignore, contents
    # removing all comments from the code
    contents = ""
    for i in range(len(lines)):
        line = lines[i]
        if ":" in line:
            indexes = list(findAll(line, ";"))
            if indexes:
                for index in indexes:
                    if not insideQuotes(index, line):
                        lines[i] = line[:index]
                        contents += line[:index] + "\n"
        else:
            contents += line + "\n"
    # checking each character for a presence of a pair
    for char in chars:
        if not chars[char].startswith("close"):
            checkClosed(char, chars[char])
    # cycling through lines
    for i in range(len(lines)):
        line = lines[i]
        wait = 0
        # checking, if the following code is still inside of a function
        if ignore:
            for j in range(len(line)):
                # if the character represents the start of a code block and it is not a string
                if line[j] == syntax["start"] and not insideQuotes(j, line):
                    wait += 1
                if line[j] == syntax["end"] and not insideQuotes(j, line):
                    if wait:
                        wait -= 1
                    else:
                        ignore = False
        after = ""
        after_list = lines[i - 1:] if i > 0 else lines[0:]
        for ln in after_list:
            after += ln + "\n"
        interpret(line, after)


# calling the main function
if __name__ == "__main__":
    main()
