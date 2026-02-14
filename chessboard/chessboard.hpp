#ifndef CHESSBOARD_HPP

# define CHESSBOARD_HPP

# include "../figures/figures.hpp"

class	Figure;

class	Chessboard
{
	private:
		Figure	*board[8][8];

	public:
		/*-----ChessBoard ctor/dtor-----*/
		Chessboard();
		~Chessboard() = default;

		/*-----ChessBoard methods-----*/
		void	make_move(Move&);
		void	unmake_move(Move&);
};

#endif //CHESSBOARD_HPP