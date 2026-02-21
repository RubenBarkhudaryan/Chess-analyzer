#include <fstream>
#include <memory>
#include "./parser.hpp"
#include "../chessboard/chessboard.hpp"

std::unique_ptr<Figure> create_figure(const std::vector<std::string>& split)
{
	Color	clr = Color::WHITE;

	if (split[2] == "black")
		clr = Color::BLACK;
	if (split[0] == "QU")
		return (std::make_unique<Queen>(clr, PieceType::QUEEN));
	if (split[0] == "KG")
		return (std::make_unique<King>(clr, PieceType::KING));
	if (split[0] == "BP")
		return (std::make_unique<Bishop>(clr, PieceType::BISHOP));
	if (split[0] == "KN")
		return (std::make_unique<Knight>(clr, PieceType::KNIGHT));
	if (split[0] == "RK")
		return (std::make_unique<Rook>(clr, PieceType::ROOK));
	return (std::make_unique<Pawn>(clr,  PieceType::PAWN));
}

t_figure	parse_figure(std::string& line)
{
	t_figure					result;
	std::vector<std::string>	splited;

	splited = split(line, " \t\n\v\f\r");

	if (!is_valid_figure(splited, line))
		return (t_figure());

	result.x = std::tolower(splited[1][0]) - 'a';
	result.y = splited[1][1] - '0';
	result.figure = create_figure(splited);

	return (result);
}

Chessboard	parse_config(const std::string& config_file)
{
	std::ifstream			file;
	std::string				line;
	t_figure				figure;
	std::vector<t_figure>	res;

	if (!is_valid_file(config_file))
		return (Chessboard(nullptr));

	file.open(config_file, std::ios::in);

	if (!file.is_open())
	{
		print_error(RED, FILE_OPEN_ERR);
		return (Chessboard(nullptr));
	}

	while (std::getline(file, line))
	{
		trim_string(line);
		if (line.empty())
			continue ;
		figure = parse_figure(line);
		if (figure.figure == nullptr)
			return (Chessboard(nullptr));
		res.push_back(std::move(figure));
	}

	if (!check_figures_count(res) || !check_kings_positions(res)
		|| !pawns_rank_check(res) || !check_duplicate_positions(res))
		return (Chessboard(nullptr));
	return (Chessboard(std::move(res)));
}
