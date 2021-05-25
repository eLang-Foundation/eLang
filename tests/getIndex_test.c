#include "getIndex.h"
#include "Unity/src/unity.h"

void setUp(void) {}
void tearDown(void) {}

void getIndex_test(void)
{
	TEST_ASSERT_EQUAL_INT(2, getIndex("hello, world", 'l'));
	TEST_ASSERT_EQUAL_INT(1, getIndex("apple", 'p'));
	TEST_ASSERT_EQUAL_INT(0, getIndex("test", 't'));
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(getIndex_test);
	return UNITY_END();
}
