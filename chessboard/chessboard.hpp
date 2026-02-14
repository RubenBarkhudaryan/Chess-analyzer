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

		/*-----ChessBoard operators-----*/
		Figure**		operator[](int idx);
		Figure*	const*	operator[](int idx) const;

		/*-----ChessBoard methods-----*/
		void					make_move(Move& move);
		void					unmake_move(Move& move);
		void					log(int fd = 0) const;
};

#endif //CHESSBOARD_HPP