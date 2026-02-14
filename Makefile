NAME		=	analyzer

CXX			=	g++
CXXFLAGS	=	-std=c++11 -Wall -Wextra -Werror -g3

VALGRIND	=	valgrind --leak-check=full --show-leak-kinds=all

SRCS		=	./main.cpp
				./figures/figures.cpp
				./chessboard/chessboard.cpp

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

val: fclean all
	$(VALGRIND) ./$(NAME)

.PHONY: all clean fclean re val
