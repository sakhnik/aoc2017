#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <iterator>
#include <numeric>

using TuneT = std::vector<int>;

TuneT Parse(std::istream &&is)
{
    return {std::istream_iterator<int>{is}, std::istream_iterator<int>{}};
}

TuneT GetInput()
{
    return Parse(std::ifstream{INPUT});
}

TuneT GetSample(const char *s)
{
    return Parse(std::istringstream{s});
}

int Sum(const TuneT &tune)
{
    return std::accumulate(begin(tune), end(tune), 0);
}

int Twice(const TuneT &tune)
{
    std::unordered_set<int> sums{0};
    int acc{};
    while (true)
    {
        for (auto i : tune)
        {
            acc += i;
            if (!sums.insert(acc).second)
            {
                return acc;
            }
        }
    }
}

TEST_CASE("main")
{
    REQUIRE(Sum(GetSample("+1 -2 +3 +1")) == 3);
    REQUIRE(Sum(GetSample("+1 +1 +1")) == 3);
    REQUIRE(Sum(GetSample("+1 +1 -2")) == 0);
    REQUIRE(Sum(GetSample("-1 -2 -3")) == -6);

    auto input = GetInput();
    std::cout << Sum(input) << std::endl;

    REQUIRE(Twice(GetSample("+1 -1")) == 0);
    REQUIRE(Twice(GetSample("+3 +3 +4 -2 -4")) == 10);
    REQUIRE(Twice(GetSample("-6 +3 +8 +5 -6")) == 5);
    REQUIRE(Twice(GetSample("+7 +7 -2 -7 -4")) == 14);

    std::cout << Twice(input) << std::endl;
}
