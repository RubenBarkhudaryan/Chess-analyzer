#include "./engine.hpp"
#include <iostream>

Engine::Engine(const Chessboard& board) : board(board)
{}

bool	Engine::is_square_attacked(int x, int y, Color by_clr) const
{
	/*-----Pawn attacks-----*/
	int	pawn_dir = (by_clr == Color::WHITE) ? -1 : 1;
	int	pawn_y = y - pawn_dir;

	for (int dx : {-1, 1})
	{
		int	pawn_x = x + dx;

		if (pawn_x >= 0 && pawn_x < 8
			&& pawn_y >= 0 && pawn_y < 8)
		{
			Figure	*piece = this->board.get(pawn_x, pawn_y);

			if (piece && piece->get_color() == by_clr
				&& piece->get_type() == PieceType::PAWN)
				return (true);
		}
	}

	/*-----Knight attacks-----*/
	const int	knight_offset[8][2] =
	{
		{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
		{1, 2}, {1, -2}, {-1, 2}, {-1, -2}
	};

	for (int i = 0; i < 8; ++i)
	{
		int	nx = x + knight_offset[i][0];
		int	ny = y + knight_offset[i][1];

		if (nx >= 0 && nx < 8
			&& ny >= 0 && ny < 8)
		{
			Figure	*piece = this->board.get(nx, ny);

			if (piece && piece->get_color() == by_clr
				&& piece->get_type() == PieceType::KNIGHT)
				return (true);
		}
	}

	/*-----King attacks-----*/
	for (int dx = -1; dx <= 1; ++dx)
	{
		for (int dy = -1; dy <= 1; ++dy)
		{
			if (dx == 0 && dy == 0)
				continue ;
			int	nx = x + dx;
			int	ny = y + dy;

			if (nx >= 0 && nx < 8
				&& ny >= 0 && ny < 8)
			{
				Figure	*piece = this->board.get(nx, ny);

				if (piece && piece->get_color() == by_clr
					&& piece->get_type() == PieceType::KING)
					return(true);
			}
		}
	}

	/*-----Rook / Queen (straight lines)-----*/
	const int	rook_offset[4][2] =
	{
		{1, 0}, {-1, 0}, {0, 1}, {0, -1}
	};

	for (int i = 0; i < 4; ++i)
	{
		int	dx = rook_offset[i][0];
		int	dy = rook_offset[i][1];

		int	nx = x + dx;
		int	ny = y + dy;

		while (nx >= 0 && nx < 8 && ny >= 0 && ny < 8)
		{
			Figure	*piece = this->board.get(nx, ny);

			if (piece)
			{
				if (piece->get_color() == by_clr &&
					(piece->get_type() == PieceType::ROOK ||
					piece->get_type() == PieceType::QUEEN)
				)
					return (true);
				break ;
			}
			nx += dx;
			ny += dy;
		}
	}

	/*-----Bishop / Queen (straight lines)-----*/
	const int	bishop_offset[4][2] =
	{
		{1, 1}, {1, -1}, {-1, 1}, {-1, -1}
	};

	for (int i = 0; i < 4; ++i)
	{
		int	dx = bishop_offset[i][0];
		int	dy = bishop_offset[i][1];

		int	nx = x + dx;
		int	ny = y + dy;

		while (nx >= 0 && nx < 8 && ny >= 0 && ny < 8)
		{
			Figure	*piece = this->board.get(nx, ny);

			if (piece)
			{
				if (piece->get_color() == by_clr &&
					(piece->get_type() == PieceType::BISHOP ||
					piece->get_type() == PieceType::QUEEN)
				)
					return (true);
				break ;
			}
			nx += dx;
			ny += dy;
		}
	}

	return (false);
}

bool	Engine::is_king_in_check(Color clr) const
{
	Figure	*piece;
	Color	enemy = (clr == Color::WHITE)
					? Color::BLACK
					: Color::WHITE;

	for (int x = 0; x < 8; ++x)
	{
		for (int y = 0; y < 8; ++y)
		{
			piece = this->board.get(x, y);
			if (piece && piece->get_type() == PieceType::KING && piece->get_color() == clr)
				return (is_square_attacked(x, y, enemy));
		}
	}
	return (false);
}

std::vector<Move>	Engine::generate_legal_moves(Color color)
{
	Figure				*piece;
	std::vector<Move>	legal_moves;
	std::vector<Move>	pseudo_moves;

	for (int x = 0; x < 8; ++x)
	{
		for (int y = 0; y < 8; ++y)
		{
			piece = this->board.get(x, y);

			if (!piece || piece->get_color() != color)
				continue ;

			pseudo_moves = piece->generate_moves(this->board, x, y);

			for (Move& move : pseudo_moves)
			{
				this->board.make_move(move);
				if (!this->is_king_in_check(color))
					legal_moves.push_back(move);
				this->board.unmake_move(move);
			}
		}
	}
	return (legal_moves);
}

bool	Engine::is_checkmate(Color color)
{
	std::vector<Move>	moves = this->generate_legal_moves(color);

	return moves.empty() && this->is_king_in_check(color);
}

bool	Engine::is_stalemate(Color color)
{
	std::vector<Move>	moves = this->generate_legal_moves(color);

	return moves.empty() && !this->is_king_in_check(color);
}

bool	Engine::mate_in_n(Color attacker, Color side_to_move, int depth)
{
	std::vector<Move>	moves = this->generate_legal_moves(side_to_move);
	Color				next = (side_to_move == Color::WHITE) ? Color::BLACK : Color::WHITE;

	if (moves.empty())
	{
		if (this->is_king_in_check(side_to_move))
			return (side_to_move != attacker);
		return (false);
	}

	if (depth == 0)
		return (false);

	if (side_to_move == attacker)
	{
		for (Move& move : moves)
		{
			this->board.make_move(move);
			if (this->mate_in_n(attacker, next, depth - 1))
			{
				this->board.unmake_move(move);
				return (true);
			}
			this->board.unmake_move(move);
		}
		return (false);
	}
	else
	{
		for (Move& move : moves)
		{
			this->board.make_move(move);
			if (!this->mate_in_n(attacker, next, depth - 1))
			{
				this->board.unmake_move(move);
				return (false);
			}
			this->board.unmake_move(move);
		}
		return (true);
	}
}
