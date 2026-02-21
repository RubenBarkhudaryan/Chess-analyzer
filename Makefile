NAME		=	analyzer

CXX			=	g++
CXXFLAGS	=	-std=c++17 -Wall -Wextra -Werror -g3

SRCS		=	./main.cpp \
				./figures/figures.cpp \
				./chessboard/chessboard.cpp \
				./parser/parser.cpp \
				./parser/parser_utils.cpp \
				./parser/config_validation.cpp \
				./parser/checkers.cpp

OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re val
