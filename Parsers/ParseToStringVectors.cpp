#include <vector>
#include <string>
#include <fstream>
#include <ostream>
#include <sstream>

std::vector<std::vector<std::string>> parseToStringVectors(const std::string& filename)
{
	std::vector<std::vector<std::string>> result;
	std::ifstream file(filename);
	if (!file.is_open())
		return result;

	auto trimmedString = [](const std::string& string)
	{
		const std::string ws{ " \t`" };
		const std::size_t begin{ string.find_first_not_of(ws) };
		return (begin == std::string::npos) ? std::string() : string.substr(begin, string.find_last_not_of(ws) + 1u - begin);
	};

	std::size_t firstLanguageTokenIndex{ 0u };
	while (file)
	{
		std::string s;
		std::getline(file, s);
		s = trimmedString(s);
		if (s != "")
		{
			std::vector<std::string> strings;
			bool discardThisLine{ false };
			std::size_t tokenIndex{ 0u };
			std::stringstream ss(s);
			while (ss && !discardThisLine && std::getline(ss, s, '|'))
			{
				if (tokenIndex++ < firstLanguageTokenIndex)
					continue;
				s = trimmedString(s);
				if (s == ":---:")
				{
					discardThisLine = true;
					break;
				}
				if ((firstLanguageTokenIndex > 0u) && (tokenIndex == (firstLanguageTokenIndex + 1u)) && (s == ""))
				{
					discardThisLine = true;
					break;
				}
				if ((s == "*") && (firstLanguageTokenIndex == 0u))
				{
					firstLanguageTokenIndex = tokenIndex;
					strings.clear();
					continue;
				}
				strings.push_back(s);
			}
			if (!discardThisLine && (tokenIndex > 0u))
				result.push_back(strings);
		}
	}



	return result;
}

int main()
{
	// parse
	std::string filepath{ "../Tables/" };
	std::string filename{ "VeryCommon.md" };
	std::vector<std::vector<std::string>> stringVectors{ parseToStringVectors(filepath + filename) };



	// check
	if (stringVectors.empty())
	{
		std::cerr << "No strings found!\n";
		return EXIT_FAILURE;
	}
	else if (stringVectors[0u].empty())
	{
		std::cerr << "No languages found!\n";
		return EXIT_FAILURE;
	}



	// use
	const std::size_t numberOfStrings{ stringVectors.size() };
	const std::size_t numberOfLanguages{ stringVectors[0u].size() };

	std::cout << "Languages:\n";
	for (std::size_t i{ 0u }; i < numberOfLanguages; ++i)
		std::cout << "\t" << stringVectors[0u][i] << "\n";

	const std::size_t languageChoice{ 1u };
	std::cout << "Strings in " << stringVectors[0u][languageChoice] << ":\n";
	for (std::size_t i{ 1u }; i < numberOfStrings; ++i)
		std::cout << "\t[" << i << "]\t" << stringVectors[i][languageChoice] << "\n";
}
