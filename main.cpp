#include <iostream>
#include "./parser/parser.hpp"
#include "./engine/engine.hpp"
#include "./logger/logger.hpp"
#include "./chessboard/chessboard.hpp"

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		Chessboard	board = parse_config(argv[1]);

		if (board.empty())
		{
			print_error(RED, EMPTY_BOARD_ERR);
			return (1);
		}

		board.display();

		Engine				engine(board);
		int					depth = std::stoi(argv[2]);
		std::vector<Move>	line;

		if (engine.is_king_in_check(Color::WHITE) && engine.is_king_in_check(Color::BLACK))
		{
			print_error(RED, KINGS_IN_CHECK);
			return (1);
		}

		if (engine.mate_in_n(Color::WHITE, Color::WHITE, depth * 2, line))
		{
			Logger	log;
			std::cout << "White wins" << std::endl;
			std::cout << "You can see the logfile with every step in '/logs' directory." << std::endl;
			log.create_log(board, line);
		}

		else
			std::cout << "White doesn't mate in " << depth << std::endl;
	}
	else
	{
		if (argc < 3)
			print_error(RED, "Error: too few arguments to run the program.");
		else
			print_error(RED, "Error: too many arguments to run the program.");
		print_error(CYAN, "To run program you'll need: [executable] [config_file] [n_steps_for_mate_detection]");
		return (1);
	}
	return (0);
}
