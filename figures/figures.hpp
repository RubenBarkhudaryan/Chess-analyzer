#ifndef FIGURES_HPP

# define FIGURES_HPP

# define WHITE_KING "♚"
# define WHITE_QUEEN "♛"
# define WHITE_BISHOP "♝"
# define WHITE_KNIGHT "♞"
# define WHITE_ROOK "♜"
# define WHITE_PAWN "♟"

# define BLACK_KING "♔"
# define BLACK_QUEEN "♕"
# define BLACK_BISHOP "♗"
# define BLACK_KNIGHT "♘"
# define BLACK_ROOK "♖"
# define BLACK_PAWN "♙"

# include <vector>
# include <string>
# include <memory>
# include "../chessboard/chessboard.hpp"

class	Figure;
class	Chessboard;

enum class Color
{
	BLACK,
	WHITE
};

struct	t_figure
{
	int						x;
	int						y;
	std::unique_ptr<Figure>	figure;

	t_figure();

	t_figure(t_figure&&) = default;
	t_figure& operator=(t_figure&&) = default;
};

struct	Move
{
	int		from_x;
	int		from_y;

	int		to_x;
	int		to_y;

	Figure	*captured;
};

class	Figure
{
	protected:
		Color		color;
		std::string	figure;

		bool	add_move(
			std::vector<Move>& vec,
			int x,
			int y,
			int n_x,
			int n_y,
			Figure *piece
		) const;

	public:
		/*-----Figures ctor/dtor-----*/
		explicit Figure(Color clr, const std::string& fig);
		virtual ~Figure() = default;

		/*-----Figures methods-----*/
		Color						get_color() const;
		std::string					get_figure() const;

		virtual std::vector<Move>	generate_moves(
			const Chessboard& board,
			int x,
			int y
		) const = 0;
		virtual Figure				*clone() const = 0;
};

class	King : public Figure
{
	public:
		King(Color color, const std::string& figure);
		~King() override = default;

		virtual std::vector<Move>	generate_moves(
			const Chessboard& board,
			int x,
			int y
		) const override;
		virtual King				*clone() const override;
};

class	Queen : public Figure
{
	public:
		Queen(Color color, const std::string& figure);
		~Queen() override = default;

		virtual std::vector<Move>	generate_moves(
			const Chessboard& board,
			int x,
			int y
		) const override;
		virtual Queen				*clone() const override;
};

class	Rook : public Figure
{
	public:
		Rook(Color color, const std::string& figure);
		~Rook() override = default;

		virtual std::vector<Move>	generate_moves(
			const Chessboard& board,
			int x,
			int y
		) const override;
		virtual Rook				*clone() const override;
};

class	Bishop : public Figure
{
	public:
		Bishop(Color color, const std::string& figure);
		~Bishop() override = default;

		virtual std::vector<Move>	generate_moves(
			const Chessboard& board,
			int x,
			int y
		) const override;
		virtual Bishop				*clone() const override;
};

class	Knight : public Figure
{
	public:
		Knight(Color color, const std::string& figure);
		~Knight() override = default;

		virtual std::vector<Move>	generate_moves(
			const Chessboard& board,
			int x,
			int y
		) const override;
		virtual Knight				*clone() const override;
};

class	Pawn : public Figure
{
	public:
		Pawn(Color color, const std::string& figure);
		~Pawn() override = default;

		virtual std::vector<Move>	generate_moves(
			const Chessboard& board,
			int x,
			int y
		) const override;
		virtual Pawn				*clone() const override;
};

#endif //FIGURES_HPP