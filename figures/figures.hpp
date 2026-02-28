#ifndef FIGURES_HPP

# define FIGURES_HPP

# include <vector>
# include <memory>

class	Figure;
class	Chessboard;

enum class Color
{
	BLACK,
	WHITE
};

enum class PieceType
{
	KING,
	QUEEN,
	ROOK,
	BISHOP,
	KNIGHT,
	PAWN
};

struct	t_figure
{
	int						x;
	int						y;
	std::unique_ptr<Figure>	figure;

	t_figure();

	t_figure(t_figure&&) = default;
	t_figure& operator=(t_figure&&) = default;

	t_figure(const t_figure&) = default;
	t_figure& operator=(const t_figure&) = default;
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
		PieceType	type;

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
		explicit Figure(Color clr, PieceType piece);
		virtual ~Figure() = default;

		/*-----Figures methods-----*/
		Color						get_color() const;
		PieceType					get_type() const;

		virtual std::vector<Move>	generate_moves(
			const Chessboard& board,
			int x,
			int y
		) const = 0;
		virtual Figure				*clone() const = 0;

		const char* symbol() const;
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
		virtual King				*clone() const override;
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
		virtual Queen				*clone() const override;
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
		virtual Rook				*clone() const override;
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
		virtual Bishop				*clone() const override;
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
		virtual Knight				*clone() const override;
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
		virtual Pawn				*clone() const override;
};

#endif //FIGURES_HPP