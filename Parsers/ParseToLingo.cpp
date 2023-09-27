#include <Lingo.hpp> // https://github.com/Hapaxia/Lingo
#include <vector>
#include <string>
#include <fstream>
#include <ostream>
#include <sstream>

template <class T>
bool parseToLingo(const std::string& filename, Lingo<T>& lingo)
{
	std::ifstream file(filename);
	if (!file.is_open())
		return false;

	auto trimmedString = [](const std::string& string)
	{
		const std::string ws{ " \t" };
		const std::size_t begin{ string.find_first_not_of(ws) };
		return (begin == std::string::npos) ? std::string() : string.substr(begin, string.find_last_not_of(ws) + 1u - begin);
	};

	std::vector<std::vector<std::string>> result;
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

	if (result.empty() || result[0u].empty())
		return false;



	const std::size_t numberOfLanguages{ result[0u].size() };
	for (std::size_t l{ 0u }; l < numberOfLanguages; ++l)
		lingo.addLanguage();
	for (std::size_t l{ 0u }; l < numberOfLanguages; ++l)
	{
		for (std::size_t s{ 0u }; s < result.size(); ++s)
			lingo.setString(static_cast<T>(s), result[s][l], l);
	}
	lingo.setLanguage(0u);



	return true;
}

int main()
{
	// prepare Lingo
	Lingo<std::size_t> lingo;



	// parse & check
	std::string filepath{ "../Tables/" };
	std::string filename{ "VeryCommon.md" };
	if (!parseToLingo(filepath + filename, lingo))
	{
		if (lingo.getNumberOfLanguages() == 0u)
		{
			std::cerr << "No languages found!\n";
			return EXIT_FAILURE;
		}
		else
		{
			std::cerr << "No strings found!\n";
			return EXIT_FAILURE;
		}
	}



	// use
	const std::size_t numberOfLanguages{ lingo.getNumberOfLanguages() };
	const std::size_t numberOfStrings{ lingo.getKeys().size() };

	std::cout << "Languages:\n";
	for (std::size_t i{ 0u }; i < numberOfLanguages; ++i)
		std::cout << "\t" << lingo.get(0u, i) << "\n";

	lingo.setLanguage(1u);
	std::cout << "Strings in " << lingo.get(0u) << ":\n";
	for (std::size_t i{ 1u }; i < numberOfStrings; ++i)
		std::cout << "\t[" << i << "]\t" << lingo.get(i) << "\n";
}
