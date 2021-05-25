#include "getContents.h"
#include "Unity/src/unity.h"
#include <malloc.h>

void setUp(void) {}
void tearDown(void) {}

void getContents_test(void)
{
	char *result1 = getContents("hello { world }", '{', '}');
	TEST_ASSERT_EQUAL_CHAR_ARRAY(" world ", result1, strlen(result1));
	free(result1);
	char *result2 = getContents("Let's see \"test\"", '"', '"');
	TEST_ASSERT_EQUAL_CHAR_ARRAY("test", result2, strlen(result2));
	free(result2);
	char *result3 = getContents("Test '\nhi\t\t'hello again", '\'', '\'');
	TEST_ASSERT_EQUAL_CHAR_ARRAY("\nhi\t\t", result3, strlen(result3));
	free(result3);
}

int main(void)
{
	printf("\n\n");
	UNITY_BEGIN();
	RUN_TEST(getContents_test);
	return UNITY_END();
}
