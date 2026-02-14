#include "./chessboard.hpp"

Chessboard::Chessboard()
{
	/*-----Black Rooks-----*/
	this->board[0][0] = new Rook(Color::BLACK, "♖");
	this->board[0][7] = new Rook(Color::BLACK, "♖");

	/*-----Black Knights-----*/
	this->board[0][1] = new Knight(Color::BLACK, "♘");
	this->board[0][6] = new Knight(Color::BLACK, "♘");

	/*-----Black Bishops-----*/
	this->board[0][2] = new Bishop(Color::BLACK, "♗");
	this->board[0][5] = new Bishop(Color::BLACK, "♗");

	/*-----Black Queen/King-----*/
	this->board[0][3] = new Queen(Color::BLACK, "♕");
	this->board[0][4] = new King(Color::BLACK, "♔");

	/*-----White Rooks-----*/
	this->board[7][0] = new Rook(Color::WHITE, "♜");
	this->board[7][7] = new Rook(Color::WHITE, "♜");

	/*-----White Knights-----*/
	this->board[7][1] = new Knight(Color::WHITE, "♞");
	this->board[7][6] = new Knight(Color::WHITE, "♞");

	/*-----White Bishops-----*/
	this->board[7][2] = new Bishop(Color::WHITE, "♝");
	this->board[7][5] = new Bishop(Color::WHITE, "♝");

	/*-----White Queen/King-----*/
	this->board[7][3] = new Queen(Color::WHITE, "♛");
	this->board[7][4] = new King(Color::WHITE, "♚");

	/*-----Black/White Pawns-----*/
	for (int i = 0; i < 8; ++i)
	{
		this->board[1][i] = new Pawn(Color::BLACK, "♙");
		this->board[6][i] = new Pawn(Color::WHITE, "♟");
	}

	for (int i = 2; i < 6; ++i)
	{
		for (int j = 0; j < 8; ++j)
			this->board[i][j] = nullptr;
	}
}

Chessboard::~Chessboard()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (this->board[i][j] != nullptr)
				delete this->board[i][j];
		}
	}
}

void	Chessboard::make_move(Move& move)
{
	Figure	*piece;

	piece = this->board[move.from_y][move.from_x];

	move.captured = this->board[move.to_y][move.to_x];

	this->board[move.to_y][move.to_x] = piece;
	this->board[move.from_y][move.from_x] = nullptr;
	this->display();
}

void	Chessboard::unmake_move(Move& move)
{
	Figure	*piece;

	piece = this->board[move.to_y][move.to_x];
	this->board[move.from_y][move.from_x] = piece;
	this->board[move.to_y][move.to_x] = move.captured;
	this->display();
}

Figure	**Chessboard::operator[](int idx)
{
	return (this->board[idx]);
}

Figure	*const	*Chessboard::operator[](int idx) const
{
	return (this->board[idx]);
}

void	Chessboard::display() const
{
	std::cout << "╔═══╤═══╤═══╤═══╤═══╤═══╤═══╤═══╗╮\n";
	for (int i = 0; i < 8; ++i)
	{
		std::cout << "║";
		for (int j = 0; j < 8; ++j)
		{
			if (j < 7)
			{
				if (!board[i][j])
				{
					if ((i + j + 1) % 2 == 0)
						std::cout << "   │";
					else
						std::cout << "░░░│";
				}
				else
					std::cout << board[i][j]->get_figure() << "  │";
			}
			else
			{
				if (!board[i][j])
				{
					if ((i + j + 1) % 2 == 0)
						std::cout << "   ";
					else
						std::cout << "░░░";
				}
				else
					std::cout << board[i][j]->get_figure() << "  ";
			}
		}
		std::cout << "║" << 8 - i << std::endl;
		if (i == 7)
			break ;
		std::cout << "╟───┼───┼───┼───┼───┼───┼───┼───╢┊" << std::endl;
	}
	std::cout << "╚═══╧═══╧═══╧═══╧═══╧═══╧═══╧═══╝┊\n";
	std::cout << "╰┈A┈┈┈B┈┈┈C┈┈┈D┈┈┈E┈┈┈F┈┈┈G┈┈┈H┈┈╯\n";
}
