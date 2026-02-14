#include "./chessboard.hpp"

Chessboard::Chessboard()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
			this->board[i][j] = nullptr;
	}
}

void	Chessboard::make_move(Move& move)
{
	Figure	*piece;

	piece = this->board[move.from_y][move.from_x];

	move.captured = this->board[move.to_y][move.to_x];

	this->board[move.to_y][move.to_x] = piece;
	this->board[move.from_y][move.from_x] = nullptr;
}

void	Chessboard::unmake_move(Move& move)
{
	Figure	*piece;

	piece = this->board[move.to_y][move.to_x];
	this->board[move.from_y][move.from_x] = piece;
	this->board[move.to_y][move.to_x] = move.captured;
}

Figure	**Chessboard::operator[](int idx)
{
	return (this->board[idx]);
}

Figure	*const	*Chessboard::operator[](int idx) const
{
	return (this->board[idx]);
}

void	Chessboard::log(int fd) const
{

}
