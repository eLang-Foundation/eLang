// this function executed the given code
void execute(char *line, char *after, int lineNumber)
{
	if (line[0] == ';') return;

	char lineCopy[strlen(line) + 1];
	strcpy(lineCopy, line);
	char *firstWord = strtok(lineCopy, " ");

	char *functionKeyword = "fun";

	if (firstWord)
	{
		if (!ignore)
		{
			// if a function was defined
			if (!strcmp(firstWord, functionKeyword))
			{
				if (numberOfFunctions == 0)
				{
					FUNCTIONS = malloc(1 * sizeof(Function));
				}
				
				// getting the name of the function
				char *functionName = get(line, "fun\\s+([\\w_\\d]+)\\s*[\\(\\{]+");

				// getting the code inside of the function
				char *code = getContents(after, '{', '}');

				// getting the arguments of the function
				char *arguments = getContents(line, '(', ')');

				strArray array = getArguments(trim(arguments));

				// creating a function
				Function f;
				f.name = strdup(trim(functionName));
				f.arguments = array.array;
				f.code = strdup(trim(code));
				f.argumentsNumber = strcmp(arguments, "") ? array.length : 0;

				// appending the function to the array of functions
				FUNCTIONS = appendFunction(FUNCTIONS, f);

				// checking if the next line of code is inside of a function
				ignore = false;
				for (int i = 0, l = (int) strlen(code); i < l; i++)
				{
					if (code[i] == '\n')
					{
						ignore = true;
						break;
					}
				}

				free(functionName);
				free(code);
				free(arguments);
			}

			// if a function was called
			else if (match(line, "[\\w\\d_]+\\s*\\([\\w\\W]*\\)[\\w\\W]*"))
			{
				functionCall(line, after);
			}

			// if a variable was created or updated
			else if (match(line, "[\\w_\\d]+\\s*=\\s*[\\w\\W]+"))
			{
				if (numberOfVariables == 0)
				{
					VARIABLES = malloc(1 * sizeof(Variable));
				}

				char *varName = get(line, "([\\w_\\d]+?)\\s*=");
				char *varValue = get(line, "[\\w_\\d]+\\s*=\\s*([\\w\\W]+)");

				char *tmp = evaluate(varValue);
				char *value = getValue(tmp);

				bool exists = false;

				for (int i = 0; i < numberOfVariables; i++)
				{
					if (!strcmp(VARIABLES[i].name, varName))
					{
						free(VARIABLES[i].value);
						VARIABLES[i].value = strdup(value);
						exists = true;
						break;
					}
				}

				if (!exists)
				{
					// creating a variable
					Variable var;
					var.name = strdup(varName);
					var.value = strdup(value);
					var.type = type(varValue);

					// appending the variable to the array of variables
					VARIABLES = appendVariable(VARIABLES, var);
				}

				free(varName);
				free(varValue);
				free(tmp);
			}

			// if the following code is an if statement
			else if (!strcmp(firstWord, "if"))
			{
				ifStatement(line, after, false);
			}

			// if the following code is an else statement
			else if (!strcmp(firstWord, "else"))
			{
				ifStatement(line, after, true);
			}

			// if the following code is an elif statement
			else if (!strcmp(firstWord, "elif"))
			{
				ifStatement(line, after, false);
			}

			// invalid syntax
			else if (strcmp(line, "}"))
			{
				raiseError(ERROR_MSG, INS, line, lineNumber, FILENAME);
			}
		}
	}
}
