#include "./parser.hpp"

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

bool	check_kings_positions(const std::vector<t_figure>& figures)
{
	int		disabled_fields[8][2] = 
	{
		{-1, 0}, {1, 0}, {0, -1}, {0, 1},
		{-1, -1}, {-1, 1}, {1, -1}, {1, 1}
	};

	int		white_x;
	int		white_y;
	int		black_x;
	int		black_y;

	bool	white_king_found;
	bool	black_king_found;

	white_king_found = false;
	black_king_found = false;
	for (std::size_t i = 0; i < figures.size(); ++i)
	{
		if (white_king_found && black_king_found)
			break ;
		if (figures[i].figure->get_figure() == WHITE_KING)
		{
			white_king_found = true;
			white_x = figures[i].x;
			white_y = figures[i].y;
		}
		else if (figures[i].figure->get_figure() == BLACK_KING)
		{
			black_king_found = true;
			black_x = figures[i].x;
			black_y = figures[i].y;
		}
	}

	if (black_y == white_y && black_x == white_x)
	{
		print_error(RED, WRONG_KING_PLACEMENT);
		return (false);
	}

	for (std::size_t i = 0; i < 8; ++i)
	{
		int	dy = disabled_fields[i][0];
		int	dx = disabled_fields[i][1];

		if (black_y == white_y + dy && black_x == white_x + dx)
		{
			print_error(RED, WRONG_KING_PLACEMENT);
			return (false);
		}
	}
	return (true);
}

bool	pawns_rank_check(const std::vector<t_figure>& figures)
{
	for (std::size_t i = 0; i < figures.size(); ++i)
	{
		auto	type = figures[i].figure->get_figure();
		if (type == WHITE_PAWN || type == BLACK_PAWN)
		{
			if (figures[i].y == 8 || figures[i].y == 1)
			{
				print_error(RED, WRONG_PAWN_PLACEMENT);
				return (false);
			}
		}
	}
	return (true);
}

bool	check_duplicate_positions(const std::vector<t_figure>& figures)
{
	std::set<std::pair<int, int>>	coords;

	for (std::size_t i = 0; i < figures.size(); ++i)
	{
		if (!coords.insert({figures[i].y, figures[i].x}).second)
		{
			print_error(RED, DUPLICATE_COORD_ERR);
			return (false);
		}
	}
	return (true);
}
