#include <doctest/doctest.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

namespace {

unsigned Checksum(const std::string &input)
{
	unsigned cs{0};

	std::istringstream iss(input);
	std::string line;
	while (std::getline(iss, line))
	{
		std::istringstream iss(line);
		int mi = std::numeric_limits<int>::max();
		int ma = std::numeric_limits<int>::min();
		int i{0};
		while (iss >> i)
		{
			if (i > ma)
				ma = i;
			if (i < mi)
				mi = i;
		}
		cs += ma - mi;
	}

	return cs;
}

unsigned Checksum2(const std::string &input)
{
	unsigned cs{0};

	std::istringstream iss(input);
	std::string line;
	while (std::getline(iss, line))
	{
		std::istringstream iss(line);
		std::vector<unsigned> nums;
		int i{0};
		while (iss >> i)
		{
			nums.push_back(i);
		}

		for (auto a : nums)
		{
			bool found = false;
			for (auto b : nums)
			{
				if (a > b && (a % b == 0))
				{
					cs += a / b;
					found = true;
					break;
				}
			}
			if (found)
				break;
		}
	}

	return cs;
}

} //namespace;

TEST_CASE(TEST_NAME)
{
	REQUIRE(Checksum("5 1 9 5\n7 5 3\n2 4 6 8") == 18);
	REQUIRE(Checksum2("5 9 2 8\n9 4 7 3\n3 8 6 5") == 9);

	std::ifstream ifs(INPUT);
	std::string str((std::istreambuf_iterator<char>(ifs)),
					std::istreambuf_iterator<char>());
	MESSAGE(Checksum(str));
	MESSAGE(Checksum2(str));
}