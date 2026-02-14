#ifndef FIGURES_HPP

# define FIGURES_HPP

# include <vector>
# include <string>
# include "../chessboard/chessboard.hpp"

class	Figure;
class	Chessboard;

enum class Color
{
	BLACK,
	WHITE
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
};

#endif //FIGURES_HPP