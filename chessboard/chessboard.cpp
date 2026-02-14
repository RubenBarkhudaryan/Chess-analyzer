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

void	Chessboard::create_log(const std::string& filename) const
{
	std::ofstream	file(filename);

	if (!file.is_open())
	{
		std::cerr << "Error: unable to open " << filename << "\n";
		return ;
	}
	file << "   a  b   c  d   e  f   g  h\n";
	file << " +---------------------------+\n";
	for (int i = 0; i < 8; ++i)
	{
		file << i + 1 << "|";
		for (int j = 0; j < 8; ++j)
		{
			if (j < 7)
			{
				if ((i + j + 1) % 2 == 0)
					file << u8"\u2B1C ";
				else
					file << u8"\u2B1B ";
			}
			else
			{
				if ((i + j + 1) % 2 == 0)
					file << u8"\u2B1C";
				else
					file << u8"\u2B1B";
			}
		}
		file << "|" << i + 1 << std::endl;
		if (i == 7)
			break ;
	}
	file << " +---------------------------+\n";
	file << "   a  b   c  d   e  f   g  h\n";
}

void	Chessboard::display() const
{
	std::cout << "   a   b   c   d   e   f   g   h \n";
	std::cout << " +-------------------------------+\n";
	for (int i = 0; i < 8; ++i)
	{
		std::cout << i + 1 << "|";
		for (int j = 0; j < 8; ++j)
		{
			if (j < 7)
			{
				if ((i + j + 1) % 2 == 0)
					std::cout << u8"\u2B1C  ";
				else
					std::cout << u8"\u2B1B  ";
			}
			else
			{
				if ((i + j + 1) % 2 == 0)
					std::cout << u8"\u2B1C ";
				else
					std::cout << u8"\u2B1B ";
			}
		}
		std::cout << "|" << i + 1 << std::endl;
		if (i == 7)
			break ;
		std::cout << " |" << std::string(30, ' ')  << " |" << std::endl;
	}
	std::cout << " +-------------------------------+\n";
	std::cout << "   a   b   c   d   e   f   g   h \n";
}
