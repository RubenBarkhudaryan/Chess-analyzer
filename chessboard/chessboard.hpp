#ifndef CHESSBOARD_HPP

# define CHESSBOARD_HPP

# include <cstddef>
# include "../figures/figures.hpp"

class	Chessboard
{
	private:
		Figure	*board[8][8];

	public:
		/*-----ChessBoard ctor/dtor-----*/
		Chessboard();
		~Chessboard() = default;
};

#endif //CHESSBOARD_HPP