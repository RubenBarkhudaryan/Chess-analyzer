#include <string>
#include <chrono>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "./logger.hpp"

std::string	Logger::generate_log_name(void)
{
	const auto			now = std::chrono::system_clock::now();
	const std::time_t	t = std::chrono::system_clock::to_time_t(now);
	std::tm				time = *std::localtime(&t);

	int					year = 1900 + time.tm_year;
	int					month = time.tm_mon + 1;
	int					day = time.tm_mday;
	int					hour = time.tm_hour;
	int					minutes = time.tm_min;
	int					seconds = time.tm_sec;

	std::string			time_str = "logfile_" + std::to_string(year);

	time_str += month < 10 ? "0" + std::to_string(month) : std::to_string(month);
	time_str += day < 10 ? "0" + std::to_string(day) : std::to_string(day);
	time_str += "_";
	time_str += hour < 10 ? "0" + std::to_string(hour) : std::to_string(hour);
	time_str += minutes < 10 ? "0" + std::to_string(minutes) : std::to_string(minutes);
	time_str += seconds < 10 ? "0" + std::to_string(seconds) : std::to_string(seconds);

	time_str += ".log";
	return (time_str);
}

void	Logger::log_board(const Chessboard& board, std::ofstream& file)
{
	file << "╔═══╤═══╤═══╤═══╤═══╤═══╤═══╤═══╗╮\n";
	for (int i = 0; i < 8; ++i)
	{
		file << "║";
		for (int j = 0; j < 8; ++j)
		{
			if (j < 7)
			{
				if (!board.get(j, i))
				{
					if ((i + j + 1) % 2 == 0)
						file << "   │";
					else
						file << "░░░│";
				}
				else
					file << " " << board.get(j, i)->symbol() << " │";
			}
			else
			{
				if (!board.get(j, i))
				{
					if ((i + j + 1) % 2 == 0)
						file << "   ";
					else
						file << "░░░";
				}
				else
					file << " " << board.get(j, i)->symbol() << " ";
			}
		}
		file << "║" << 8 - i << std::endl;
		if (i == 7)
			break ;
		file << "╟───┼───┼───┼───┼───┼───┼───┼───╢┊" << std::endl;
	}
	file << "╚═══╧═══╧═══╧═══╧═══╧═══╧═══╧═══╝┊\n";
	file << "╰┈A┈┈┈B┈┈┈C┈┈┈D┈┈┈E┈┈┈F┈┈┈G┈┈┈H┈┈╯\n";
}

void	Logger::create_log(Chessboard& board, const std::vector<Move>& moves)
{
	std::string	path = "./logs/";
	std::string	letters = "ABCDEFGH";

	try
	{
		if (std::filesystem::create_directories(path))
			std::cout << "Filesystem: logs directory created successfully " << path << std::endl;
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		std::cerr << "Filesystem: error creating logs directory: " << e.what() << std::endl;
		return ;
	}

	std::ofstream	file(path + this->generate_log_name());

	for (const Move& m : moves)
	{
		file << "Move: " << board.get(m.from_x, m.from_y)->symbol() << " "
				<< letters[m.from_x] << 8 - m.from_y
				<< " -> "
				<< letters[m.to_x] << 8 - m.to_y
				<< std::endl;

		board.make_move((Move&)m);
		this->log_board(board, file);
		file << std::endl;
	}
	file.close();
}

Logger&	Logger::create_logger()
{
	static Logger	logger;
	return (logger);
}
