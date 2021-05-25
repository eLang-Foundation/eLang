#include "insideQuotes.h"
#include "Unity/src/unity.h"

void setUp(void) {}
void tearDown(void) {}

void insideQuotes_test(void)
{
	TEST_ASSERT(insideQuotes(1, "\"Test") == true);
	TEST_ASSERT(insideQuotes(2, "hello world") == false);
	TEST_ASSERT(insideQuotes(3, "he'123") == true);
}

int main(void)
{
	printf("\n\n");
	UNITY_BEGIN();
	RUN_TEST(insideQuotes_test);
	return UNITY_END();
}
