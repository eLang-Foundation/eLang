#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	system("cd ../src && ./elang ../tests/if_statement_test.elang > ../tests/if_statement_test_results.txt");

	// reading the test results file
	FILE *ifStatementTestResultsFile = fopen("if_statement_test_results.txt", "r");
	fseek(ifStatementTestResultsFile, 0L, SEEK_END);
	size_t length = ftell(ifStatementTestResultsFile);
	fseek(ifStatementTestResultsFile, 0L, SEEK_SET);

	char *results = malloc(length + 1);
	fread(results, 1, length, ifStatementTestResultsFile);

	fclose(ifStatementTestResultsFile);

	if (!strcmp(results, "correct\n"
	                     "correct\n"
	                     "correct\n"
	                     "correct\n"
	                     "correct\n"
	                     "correct\n"
	                     "correct\n"
	                     "correct\n"
	                     "correct\n"
	                     "correct\n"
	                     "correct\n"))
	{
		printf("Passed all if statement tests ✔️\n");
	}
	else
	{
		free(results);
		printf("Failed some of if statement tests ❌\n");
		return 1;
	}

	free(results);


	return 0;
}
