#include <iostream>
#include <sstream>
#include <cassert>
#include <unordered_set>
#include <algorithm>

template <typename FilterT>
unsigned Count(const std::string &input)
{
	unsigned count{0};
	std::istringstream iss(input);
	std::string line;
	while (std::getline(iss, line))
	{
		FilterT filter;
		std::istringstream is(line);
		std::string word;
		bool isBad{false};
		while (is >> word && !word.empty() && !isBad)
		{
			isBad = filter.Add(word);
		}

		if (!isBad)
			++count;
	}
	return count;
}

struct ExactFilter
{
	bool Add(const std::string &word)
	{
		return !_words.insert(word).second;
	}

private:
	std::unordered_set<std::string> _words;
};

struct AnagramFilter
{
	bool Add(std::string word)
	{
		std::sort(word.begin(), word.end());
		return !_words.insert(word).second;
	}

private:
	std::unordered_set<std::string> _words;
};

int main()
{
	assert(Count<ExactFilter>("aa bb cc dd ee") == 1);
	assert(Count<ExactFilter>("aa bb cc dd aa") == 0);
	assert(Count<ExactFilter>("aa bb cc dd aaa") == 1);

	std::string input((std::istreambuf_iterator<char>(std::cin)),
					  std::istreambuf_iterator<char>());
	std::cout << Count<ExactFilter>(input) << std::endl;
	std::cout << Count<AnagramFilter>(input) << std::endl;
}