#include "count.h"
#include "Unity/src/unity.h"

void setUp(void) {}
void tearDown(void) {}

void count_test(void)
{
	TEST_ASSERT_EQUAL_INT(1, count('a', "hello world this is a test, just A test"));
	TEST_ASSERT_EQUAL_INT(2, count('a', "just a word with a letter A"));
	TEST_ASSERT_EQUAL_INT(3, count('a', "12a'a'Aapple'A'a"));
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(count_test);
	return UNITY_END();
}
