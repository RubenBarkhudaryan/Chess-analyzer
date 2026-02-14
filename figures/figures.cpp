#include "./figures.hpp"

/*-----Figure methods-----*/
Figure::Figure(Color clr) : color(clr)
{}

Color	Figure::get_color() const
{
	return (this->color);
}

/*-----King methods-----*/
King::King(Color clr) : Figure(clr)
{}

std::vector<Move>	King::generate_moves(const Chessboard& board, int x, int y) const
{

}

/*-----Queen methods-----*/
Queen::Queen(Color clr) : Figure(clr)
{}

std::vector<Move>	Queen::generate_moves(const Chessboard& board, int x, int y) const
{
	
}

/*-----Bishop methods-----*/
Bishop::Bishop(Color clr) : Figure(clr)
{}

std::vector<Move>	Bishop::generate_moves(const Chessboard& board, int x, int y) const
{
	
}

/*-----Knight methods-----*/
Knight::Knight(Color clr) : Figure(clr)
{}

std::vector<Move>	Knight::generate_moves(const Chessboard& board, int x, int y) const
{
	
}

/*-----Rook methods-----*/
Rook::Rook(Color clr) : Figure(clr)
{}

std::vector<Move>	Rook::generate_moves(const Chessboard& board, int x, int y) const
{
	
}

/*-----Pawn methods-----*/
Pawn::Pawn(Color clr) : Figure(clr)
{}

std::vector<Move>	Pawn::generate_moves(const Chessboard& board, int x, int y) const
{
	
}
