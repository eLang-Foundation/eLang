#include "../src/re.h"
#include "Unity/src/unity.h"

void setUp(void) {}
void tearDown(void) {}

void re_test(void)
{
	TEST_ASSERT(match("hello", "[\\w]*") == true);
	char *string = "hello";
	TEST_ASSERT(get("123hello456", "([\\w]+)") == string);
}

int main(void)
{
	printf("\n\n");
	UNITY_BEGIN();
	RUN_TEST(re_test);
	return UNITY_END();
}
