#ifndef CHESSBOARD_HPP

# define CHESSBOARD_HPP

# include "../figures/figures.hpp"
# include <fstream>
# include <iostream>
# include <string>

class	Figure;
class	Move;

class	Chessboard
{
	private:
		Figure	*board[8][8];

	public:
		/*-----ChessBoard ctor/dtor-----*/
		Chessboard();
		~Chessboard();

		/*-----ChessBoard operators-----*/
		Figure**		operator[](int idx);
		Figure*	const*	operator[](int idx) const;

		/*-----ChessBoard methods-----*/
		void			display() const;
		void			make_move(Move& move);
		void			unmake_move(Move& move);
		void			create_log(const std::string& filename) const;
};

#endif //CHESSBOARD_HPP