#include "./chessboard/chessboard.hpp"
#include "./parser/parser.hpp"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		Chessboard	board = parse_config(argv[1]);
		if (!board.empty())
			board.display();
	}

	return (0);
}