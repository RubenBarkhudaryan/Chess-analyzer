#ifndef CHESSBOARD_HPP

# define CHESSBOARD_HPP

# include <vector>
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

		/*-----ChessBoard operators-----*/
		Chessboard(const Chessboard& other);
		Chessboard& operator=(const Chessboard& other);

		/*-----ChessBoard methods-----*/
		bool			empty() const;
		void			display() const;
		void			make_move(Move& move);
		void			unmake_move(Move& move);
		Figure*			get(int x, int y) const;
		void			set(int x, int y, Figure* piece);
};

#endif //CHESSBOARD_HPP