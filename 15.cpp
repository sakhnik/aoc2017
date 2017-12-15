#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <iostream>

unsigned Count(uint64_t a, uint64_t b)
{
	unsigned judge{0};

	for (unsigned i = 0; i < 40000000; ++i)
	{
		a = (a * 16807) % 2147483647;
		b = (b * 48271) % 2147483647;
		if ((a & 0xffff) == (b & 0xffff))
			++judge;
	}

	return judge;
}

TEST_CASE("main")
{
	REQUIRE(Count(65, 8921) == 588);

	std::cout << Count(289, 629) << std::endl;
}
