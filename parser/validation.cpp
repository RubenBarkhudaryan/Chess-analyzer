#include "./parser.hpp"

void	print_error(const char *color, const char *msg)
{
	std::cerr << color << msg << RESET << std::endl;
}

bool	is_valid_file(const std::string& config_file)
{
	std::ifstream	file(config_file, std::ios::in | std::ios::binary);
	std::size_t		len = config_file.size();

	if (!file.is_open())
	{
		print_error(RED, FILE_OPEN_ERR);
		return (false);
	}

	if (len <= 6)
	{
		file.close();
		print_error(RED, WRONG_FILE);
		return (false);
	}

	if (config_file.substr(len - 6) != ".chess")
	{
		file.close();
		print_error(RED, WRONG_EXTENSION);
		return (false);
	}

	file.close();
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

bool	check_counts(const t_count& cnt)
{
	if (cnt.total > 16)
	{
		print_error(RED, WRONG_TOTAL_COUNT);
		return (false);
	}
	if (cnt.king != 1)
	{
		print_error(RED, WRONG_KING_COUNT);
		return (false);
	}
	if (cnt.pawn > 8)
	{
		print_error(RED, WRONG_PAWN_COUNT);
		return (false);
	}

	int	extra_queens = std::max(0, cnt.queen - 1);
	int	extra_bishops = std::max(0, cnt.bishop - 2);
	int	extra_knights = std::max(0, cnt.knight - 2);
	int	extra_rooks = std::max(0, cnt.rook - 2);

	int	extra = extra_queens + extra_bishops + extra_knights + extra_rooks;

	int	missing_pawns = 8 - cnt.pawn;

	if (extra > missing_pawns)
	{
		print_error(RED, WRONG_EXTRA_COUNT);
		return (false);
	}
	return (true);
}

bool	check_figures_count(const std::vector<t_figure>& figures)
{
	t_count	white;
	t_count	black;

	for (std::size_t i = 0; i < figures.size(); ++i)
	{
		if (figures[i].figure->get_color() == Color::WHITE)
		{
			if (figures[i].figure->get_figure() == WHITE_KING)
				++(white.king);
			else if (figures[i].figure->get_figure() == WHITE_QUEEN)
				++(white.queen);
			else if (figures[i].figure->get_figure() == WHITE_BISHOP)
				++(white.bishop);
			else if (figures[i].figure->get_figure() == WHITE_KNIGHT)
				++(white.knight);
			else if (figures[i].figure->get_figure() == WHITE_ROOK)
				++(white.rook);
			else if (figures[i].figure->get_figure() == WHITE_PAWN)
				++(white.pawn);
			++(white.total);
		}
		else if (figures[i].figure->get_color() == Color::BLACK)
		{
			if (figures[i].figure->get_figure() == BLACK_KING)
				++(black.king);
			else if (figures[i].figure->get_figure() == BLACK_QUEEN)
				++(black.queen);
			else if (figures[i].figure->get_figure() == BLACK_BISHOP)
				++(black.bishop);
			else if (figures[i].figure->get_figure() == BLACK_KNIGHT)
				++(black.knight);
			else if (figures[i].figure->get_figure() == BLACK_ROOK)
				++(black.rook);
			else if (figures[i].figure->get_figure() == BLACK_PAWN)
				++(black.pawn);
			++(black.total);
		}
	}
	return (check_counts(white) && check_counts(black));
}
