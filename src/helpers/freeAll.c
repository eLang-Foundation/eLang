// this function frees most of the variables
void freeAll(void)
{
	// freeing all functions
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

	// freeing all variables
	for (ui i = 0; i < numberOfVariables; i++)
	{
		Variable variable = VARIABLES[i];
		
		free(variable.name);
		free(variable.value);
	}
	free(VARIABLES);
}
