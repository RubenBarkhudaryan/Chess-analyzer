#ifndef FIGURES_HPP

# define FIGURES_HPP

# include <vector>
# include "../chessboard/chessboard.hpp"

class	Figure;
class	ChessBoard;

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
		Color	color;

	public:
		/*-----Figures ctor/dtor-----*/
		explicit Figure(Color clr);
		virtual ~Figure() = default;

		/*-----Figures methods-----*/
		Color						get_color() const;
		virtual std::vector<Move>	generate_moves(
			const Chessboard& board,
			int x,
			int y
		) const = 0;
};

class	King : public Figure
{
	public:
		King(Color color);
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
		Queen(Color color);
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
		Rook(Color color);
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
		Bishop(Color color);
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
		Knight(Color color);
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
		Pawn(Color color);
		~Pawn() override = default;

		virtual std::vector<Move>	generate_moves(
			const Chessboard& board,
			int x,
			int y
		) const override;
};

#endif //FIGURES_HPP