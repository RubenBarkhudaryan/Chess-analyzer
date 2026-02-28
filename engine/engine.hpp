#ifndef ENGINE_HPP

# define ENGINE_HPP

# define KINGS_IN_CHECK	"Error: Illegal position: both kings in check"

# include <vector>
# include "../chessboard/chessboard.hpp"

struct		Move;
enum class	Color;

class	Engine
{
	private:
		Chessboard	board;

	public:
		/*-----Engine ctor/dtor-----*/
		explicit Engine(const Chessboard& board);
		~Engine() = default;

		/*-----Engine methods-----*/
		std::vector<Move>	generate_legal_moves(Color color);
		bool				is_checkmate(Color color);
		bool				is_stalemate(Color color);
		bool				is_king_in_check(Color color) const;
		bool				is_square_attacked(int x, int y, Color by_clr) const;
		bool				mate_in_n(Color attacker, Color side_to_move, int depth);
};

#endif //ENGINE_HPP
