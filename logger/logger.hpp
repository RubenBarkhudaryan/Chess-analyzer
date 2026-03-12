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
		/*-----Logger private methods-----*/
		std::string	generate_log_name(void);
		void		log_board(const Chessboard& board, std::ofstream& file);

		/*-----Logger ctor/dtor-----*/
		Logger() = default;
		~Logger() = default;

	public:
		/*-----Logger deleted ctors/operators-----*/
		Logger(const Logger& other) = delete;
		Logger(Logger&& other) = delete;

		Logger& operator=(const Logger& other) = delete;
		Logger& operator=(Logger&& other) = delete;

		/*-----Logger methods-----*/
		static Logger&	create_logger();
		void			create_log(Chessboard& board, const std::vector<Move>& moves = std::vector<Move>());
};

#endif //LOGGER_HPP
