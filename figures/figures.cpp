#include "./figures.hpp"

t_figure::t_figure() : x(0), y(0), figure(nullptr)
{}

/*-----Figure methods-----*/
Figure::Figure(Color clr, const std::string& fig) : color(clr), figure(fig)
{}

Color	Figure::get_color() const
{
	return (this->color);
}

std::string	Figure::get_figure() const
{
	return (this->figure);
}

bool	Figure::add_move(std::vector<Move>& vec, int x, int y, int n_x, int n_y, Figure *piece) const
{
	if (!piece || piece->get_color() != this->color)
	{
		vec.push_back(Move{x, y, n_x, n_y, piece});
		if (!piece)
			return (true);
		return (false);
	}
	return (false);
}

/*-----King methods-----*/
King::King(Color clr, const std::string& fig) : Figure(clr, fig)
{}

std::vector<Move>	King::generate_moves(const Chessboard& board, int x, int y) const
{
	const int	rays[8][2] =
	{
		{1, 0}, {-1, 0}, {0, 1}, {0, -1}, // rook-like
		{1, 1}, {1, -1}, {-1, 1}, {-1, -1} // bishop-like
	};

	int					n_x;
	int					n_y;
	int					dx;
	int					dy;
	Figure				*piece;
	std::vector<Move>	possible_moves;

	for (int i = 0; i < 8; ++i)
	{
		dx = rays[i][0];
		dy = rays[i][1];
		n_x = x + dx;
		n_y = y + dy;

		if (n_x < 0 || n_x >= 8 || n_y < 0 || n_y >= 8)
			continue ;

		piece = board[n_y][n_x];
		if (!piece || piece->get_color() != this->color)
			possible_moves.push_back(Move{x, y, n_x, n_y, piece});
	}
	return (possible_moves);
}

King	*King::clone() const
{
	return new King(*this);
}

/*-----Queen methods-----*/
Queen::Queen(Color clr, const std::string& fig) : Figure(clr, fig)
{}

std::vector<Move>	Queen::generate_moves(const Chessboard& board, int x, int y) const
{
	const int	rays[8][2] =
	{
		{1, 0}, {-1, 0}, {0, 1}, {0, -1}, // rook-like
		{1, 1}, {1, -1}, {-1, 1}, {-1, -1} // bishop-like
	};

	int					n_x;
	int					n_y;
	int					dx;
	int					dy;
	Figure				*piece;
	std::vector<Move>	possible_moves;

	for (int i = 0; i < 8; ++i)
	{
		dx = rays[i][0];
		dy = rays[i][1];
		n_x = x + dx;
		n_y = y + dy;

		while (n_x >= 0 && n_x < 8 && n_y >= 0 && n_y < 8)
		{
			piece = board[n_y][n_x];
			if (!add_move(possible_moves, x, y, n_x, n_y, piece))
				break ;
			n_x += dx;
			n_y += dy;
		}
	}
	return (possible_moves);
}

Queen	*Queen::clone() const
{
	return new Queen(*this);
}

/*-----Bishop methods-----*/
Bishop::Bishop(Color clr, const std::string& fig) : Figure(clr, fig)
{}

std::vector<Move>	Bishop::generate_moves(const Chessboard& board, int x, int y) const
{
	const int	rays[4][2] =
	{
		{1, 1}, //up-right
		{1, -1}, //up-left
		{-1, 1}, //down-right
		{-1, -1} //down-left
	};

	int					n_x;
	int					n_y;
	int					dx;
	int					dy;
	Figure				*piece;
	std::vector<Move>	possible_moves;

	for (int i = 0; i < 4; ++i)
	{
		dx = rays[i][0];
		dy = rays[i][1];
		n_x = x + dx;
		n_y = y + dy;

		while (n_x >= 0 && n_x < 8 && n_y >= 0 && n_y < 8)
		{
			piece = board[n_y][n_x];
			if (!add_move(possible_moves, x, y, n_x, n_y, piece))
				break ;
			n_x += dx;
			n_y += dy;
		}
	}
	return (possible_moves);
}

Bishop	*Bishop::clone() const
{
	return new Bishop(*this);
}

/*-----Knight methods-----*/
Knight::Knight(Color clr, const std::string& fig) : Figure(clr, fig)
{}

std::vector<Move>	Knight::generate_moves(const Chessboard& board, int x, int y) const
{
	const int	offsets[8][2] =
	{
		{ 2, 1 }, { 2,-1 }, { -2, 1 }, { -2,-1 }, // up-down
		{ 1, 2 }, { 1,-2 }, { -1, 2 }, { -1,-2 } // left-right
	};

	int					n_x;
	int					n_y;
	Figure				*piece;
	std::vector<Move>	possible_moves;

	for (int i = 0; i < 8; ++i)
	{
		n_x = x + offsets[i][0];
		n_y = y + offsets[i][1];

		if (n_x < 0 || n_x > 7 || n_y < 0 || n_y > 7)
			continue ;

		piece = board[n_y][n_x];
		if (!piece || piece->get_color() != this->color)
			possible_moves.push_back(Move{x, y, n_x, n_y, piece});
	}
	return (possible_moves);
}

Knight	*Knight::clone() const
{
	return new Knight(*this);
}

/*-----Rook methods-----*/
Rook::Rook(Color clr, const std::string& fig) : Figure(clr, fig)
{}

std::vector<Move>	Rook::generate_moves(const Chessboard& board, int x, int y) const
{
	const int	rays[4][2] =
	{
		{1, 0}, //move-forward
		{-1, 0}, //move-backward
		{0, 1}, //move-right
		{0, -1} //move-left
	};

	int					n_x;
	int					n_y;
	int					dx;
	int					dy;
	Figure				*piece;
	std::vector<Move>	possible_moves;

	for (int i = 0; i < 4; ++i)
	{
		dx = rays[i][0];
		dy = rays[i][1];
		n_x = x + dx;
		n_y = y + dy;

		while (n_x >= 0 && n_x < 8 && n_y >= 0 && n_y < 8)
		{
			piece = board[n_y][n_x];
			if (!add_move(possible_moves, x, y, n_x, n_y, piece))
				break ;
			n_x += dx;
			n_y += dy;
		}
	}
	return (possible_moves);
}

Rook	*Rook::clone() const
{
	return new Rook(*this);
}

/*-----Pawn methods-----*/
Pawn::Pawn(Color clr, const std::string& fig) : Figure(clr, fig)
{}

std::vector<Move>	Pawn::generate_moves(const Chessboard& board, int x, int y) const
{
	std::vector<Move>	possible_moves;
	int					dir = (this->color == Color::WHITE) ? -1 : 1;
	int					start_rank = (this->color == Color::WHITE) ? 6 : 1;

	int					one_step_move = y + dir;
	int					two_step_move = y + 2 * dir;

	if (board[one_step_move][x] == nullptr)
	{
		possible_moves.push_back(Move{x, y, x, one_step_move, nullptr});
		if (y == start_rank && board[two_step_move][x] == nullptr)
			possible_moves.push_back(Move{x, y, x, two_step_move, nullptr});
	}

	for (int dx : {-1, 1})
	{
		int	n_x = x + dx;
		int	n_y = y + dir;

		if (n_x < 0 || n_x > 8 || n_y < 0 || n_y > 8)
			continue ;

		Figure	*piece = board[n_y][n_x];
		if (piece && piece->get_color() != this->color)
			possible_moves.push_back(Move{x, y, n_x, n_y, piece});
	}
	return (possible_moves);
}

Pawn	*Pawn::clone() const
{
	return new Pawn(*this);
}
