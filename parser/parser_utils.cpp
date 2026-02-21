#include "./parser.hpp"

void	trim_string(std::string& str)
{
	std::size_t	start;
	std::size_t	end;

	if (str.size() == 0)
		return ;

	start = 0;
	end = str.size() - 1;

	while (start < str.size())
	{
		if (!std::isspace(str[start]))
			break ;
		++start;
	}
	if (start == str.size())
	{
		str.clear();
		return ;
	}
	while (end > start)
	{
		if (!std::isspace(str[end]))
			break ;
		--end;
	}
	str = str.substr(start, end - start + 1);
}

std::vector<std::string>	split(const std::string& str, const std::string& delimeter_set)
{
	std::vector<std::string>	result;
	std::size_t					start;
	std::size_t					pos;

	start = 0;
	while ((pos = str.find_first_of(delimeter_set, start)) != std::string::npos)
	{
		if (pos > start)
			result.push_back(str.substr(start, pos - start));
		start = pos + 1;
	}
	if (start < str.size())
		result.push_back(str.substr(start));
	return (result);
}
