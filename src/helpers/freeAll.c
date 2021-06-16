// this function frees the functions
void freeFunctions(void)
{
	for (ui i = 0; i < numberOfFunctions; i++)
	{
		Function function = FUNCTIONS[i];
		
		for (int j = 0; j < function.argumentsNumber; j++)
			free(function.arguments[j]);

		free(function.arguments);
		free(function.code);
		free(function.name);
	}
	free(FUNCTIONS);
}

// this function frees the variables
void freeVariables(void)
{
	for (ui i = 0; i < numberOfVariables; i++)
	{
		Variable variable = VARIABLES[i];
		
		free(variable.name);
		free(variable.value);
		free(variable.scope);
	}
	free(VARIABLES);
}

// this function frees most of the variables
void freeAll(void)
{
	freeFunctions();
	freeVariables();

	free(SCOPE);
}
