#ifndef PARSER_HPP

# define PARSER_HPP

# include <string>
# include <vector>
# include <memory>
# include "../figures/figures.hpp"

# define FILE_OPEN_ERR			"Error: unable to open the file"
# define DUPLICATE_COORD_ERR	"Error: duplicate coordinates in config file"
# define WRONG_EXTENSION		"Error: given file's extension isn't '.chess'"
# define WRONG_FILE				"Error: invalid filename"
# define WRONG_PAWN_COUNT		"Error: max count of pawns for each color (black/white) is 8"
# define WRONG_KING_COUNT		"Error: for each color (black/white) must be one king"
# define WRONG_EXTRA_COUNT		"Error: pawns count and extra figures count doesn't match (queen/bishop/knight/rook)"
# define WRONG_TOTAL_COUNT		"Error: total count more than 16"
# define WRONG_KING_PLACEMENT	"Error: kings are adjacent"
# define WRONG_PAWN_PLACEMENT	"Error: pawns can't be placed on first or last rows in initialization stage"
# define WRONG_CONFIG			"Error: wrong config"
# define HINT					"Hint: config must contain -> the type of figure (QU, KG, BP, KN, RK, PW), \
position (f7, B4, e3, A1 or other) and color of figure (white/black)"

# define RESET				"\033[0m"
# define RED				"\033[31m"
# define GREEN				"\033[32m"
# define YELLOW				"\033[33m"
# define BLUE				"\033[34m"
# define CYAN				"\033[36m"

struct	t_figure;
class	Figure;
class	Chessboard;

typedef struct	s_count
{
	int	king = 0;
	int	queen = 0;
	int	bishop = 0;
	int	knight = 0;
	int	rook = 0;
	int	pawn = 0;
	int	total = 0;
}	t_count;

/*-----config file parser-----*/
Chessboard					parse_config(const std::string& config_file);
t_figure					parse_figure(std::string& line);

/*------parser helpers-----*/
std::unique_ptr<Figure>		create_figure(const std::vector<std::string>& split);
void						trim_string(std::string& str);
std::vector<std::string>	split(const std::string& str, const std::string& delimeter_set);

/*-----figure(t_figure) validation-----*/
bool						check_duplicate_positions(const std::vector<t_figure>& figures);
bool						check_counts(const t_count& cnt);
bool						check_figures_count(const std::vector<t_figure>& figures);
bool						pawns_rank_check(const std::vector<t_figure>& figures);
bool						is_valid_config(const std::string& config);
bool						is_valid_pos(const std::string& pos);
bool						check_kings_positions(const std::vector<t_figure>& figures);
bool						is_valid_figure(
								const std::vector<std::string>& fig,
								const std::string& line
							);

/*-----file validation-----*/
bool						is_valid_file(const std::string& config_file);
void						print_error(const char *color, const char *msg);

#endif //PARSER_HPP