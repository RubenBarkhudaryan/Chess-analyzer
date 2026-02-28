#ifndef LOGGER_HPP

# define LOGGER_HPP

# include <vector>
# include "../figures/figures.hpp"
# include "../chessboard/chessboard.hpp"

struct	Move;
class	Chessboard;

class	Logger
{
	private:
		std::string	generate_log_name(void);
		void		log_board(const Chessboard& board, std::ofstream& file);

	public:
		/*-----Logger methods-----*/
		void		create_log(Chessboard& board, std::vector<Move>& moves);
};

#endif //LOGGER_HPP
