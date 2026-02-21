#ifndef CHESSBOARD_HPP

# define CHESSBOARD_HPP

# include <string>
# include <fstream>
# include <iostream>
# include "../figures/figures.hpp"

class	Figure;
class	Move;
struct	t_figure;

class	Chessboard
{
	private:
		Figure			*board[8][8];

	public:
		/*-----ChessBoard ctor/dtor-----*/
		Chessboard();
		Chessboard(std::nullptr_t);
		Chessboard(std::vector<t_figure>&& figures) noexcept;
		~Chessboard();

		Chessboard(const Chessboard& other);
		Chessboard& operator=(const Chessboard& other);

		/*-----ChessBoard operators-----*/
		Figure**		operator[](int idx);
		Figure	*const	*operator[](int idx) const;

		/*-----ChessBoard methods-----*/
		bool			empty() const;
		void			display() const;
		void			make_move(Move& move);
		void			unmake_move(Move& move);
};

#endif //CHESSBOARD_HPP