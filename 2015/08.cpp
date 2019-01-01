#include <doctest/doctest.h>
#include <sstream>
#include <fstream>
#include <algorithm>

namespace {

size_t CountEscape(std::istream &&is)
{
    size_t count{};
    std::string line;
    while (is && getline(is, line))
    {
        for (size_t i = 0; i < line.size(); ++i)
        {
            if (line[i] == '\\')
            {
                ++count;
                ++i;
                if (line[i] == 'x')
                {
                    count += 2;
                    i += 2;
                }
            }
        }
        count += 2;
    }
    return count;
}

size_t CountEscape2(std::istream &&is)
{
    size_t count{};
    std::string line;
    while (is && getline(is, line))
    {
        auto c = std::count_if(line.begin(), line.end(),
                               [](char ch) {
                                    return ch == '\\' || ch == '"';
                               });
        c += 2;
        count += c;
    }
    return count;
}

} //namespace;

TEST_CASE(TEST_NAME)
{
    SUBCASE("test") {
        const char *const TEST = R"(""
"abc"
"aaa\"aaa"
"\x27")";
        REQUIRE(12 == CountEscape(std::istringstream{TEST}));
        REQUIRE(19 == CountEscape2(std::istringstream{TEST}));
    }

    SUBCASE("task") {
        MESSAGE(CountEscape(std::ifstream{INPUT}));
        MESSAGE(CountEscape2(std::ifstream{INPUT}));
    }
}
