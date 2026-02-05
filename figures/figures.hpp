#ifndef FIGURES_HPP

# define FIGURES_HPP

typedef enum e_color
{
	BLACK,
	WHITE
}	t_color;

typedef enum e_figure
{
	KING,
	QUEEN,
	BISHOP,
	KNIGHT,
	ROOK,
	PAWN
}	t_figure;

class	Figure
{
	private:
		t_figure	figure;
		t_color		color;

	public:
		/*-----Figures ctor/dtor-----*/
		Figure(t_figure fgr, t_color clr);
		~Figure() = default;
};

#endif //FIGURES_HPP