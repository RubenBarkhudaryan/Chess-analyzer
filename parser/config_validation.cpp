#include <iostream>
#include <fstream>
#include "./parser.hpp"

void	print_error(const char *color, const char *msg)
{
	std::cerr << color << msg << RESET << std::endl;
}

bool	is_valid_file(const std::string& config_file)
{
	std::ifstream	file(config_file, std::ios::in);
	std::size_t		len = config_file.size();

	if (!file.is_open())
	{
		print_error(RED, FILE_OPEN_ERR);
		return (false);
	}

	if (len <= 6)
	{
		print_error(RED, WRONG_FILE);
		return (false);
	}

	if (config_file.substr(len - 6) != ".chess")
	{
		print_error(RED, WRONG_EXTENSION);
		return (false);
	}
	return (true);
}

bool	is_valid_config(const std::string& config)
{
	return (config == "QU" || config == "KG"
			|| config == "BP" || config == "KN"
			|| config == "RK" || config == "PW");
}

bool	is_valid_pos(const std::string& pos)
{
	if (pos.size() != 2)
		return (false);
	if (!(pos[0] >= 'a' && pos[0] <= 'h') && !(pos[0] >= 'A' && pos[0] <= 'H'))
		return (false);
	if (!(pos[1] >= '1' && pos[1] <= '8'))
		return (false);
	return (true);
}

bool	is_valid_figure(const std::vector<std::string>& fig, const std::string& line)
{
	if (fig.size() != 3 || !is_valid_config(fig[0]))
	{
		print_error(RED, WRONG_CONFIG);
		print_error(YELLOW, HINT);
		std::cerr << CYAN << "\nGiven config: " << line << std::endl;
		return (false);
	}

	if (!is_valid_pos(fig[1]))
	{
		print_error(RED, WRONG_CONFIG);
		print_error(YELLOW, HINT);
		std::cerr << CYAN << "\nGiven config: " << line << RESET << std::endl;
		return (false);
	}

	if (fig[2] != "white" && fig[2] != "black")
	{
		print_error(RED, WRONG_CONFIG);
		print_error(YELLOW, HINT);
		std::cerr << CYAN << "\nGiven config: " << line << RESET << std::endl;
		return (false);
	}

	return (true);
}
