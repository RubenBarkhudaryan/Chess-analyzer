#include "chessboard.hpp"

Chessboard::Chessboard()
{
	for (std::size_t y = 0; y < 8; ++y)
	{
		for (std::size_t x = 0; x < 8; ++x)
			this->board[y][x] = nullptr;
	}
}
