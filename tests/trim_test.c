#include "trim.h"
#include "Unity/src/unity.h"
#include <malloc.h>

void setUp(void) {}
void tearDown(void) {}

void trim_test(void)
{
	char *string1 = strdup("    hello    ");
	TEST_ASSERT_EQUAL_STRING("hello", trim(string1));
	free(string1);
	char *string2 = strdup("\t\t hi \n");
	TEST_ASSERT_EQUAL_STRING("hi", trim(string2));
	free(string2);
	char *string3 = strdup("123");
	TEST_ASSERT_EQUAL_STRING("123", trim(string3));
	free(string3);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(trim_test);
	return UNITY_END();
}
