NAME = btc

SRC =	main.cpp BitcoinExchange.cpp

HEADER = BitcoinExchange.hpp

CPP = c++

CPPFLAGS = -Wall -Wextra -Werror -std=c++98

OBJ = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(HEADER)
	@echo "🥣 .o was MADE."
	$(CPP) $(CPPFLAGS) $(SRC) -o $(NAME)

all: $(NAME)

clean:
	@rm -f $(OBJ)
	@echo "🗑 .o is REMOVED."

fclean:
	@rm -f $(OBJ) $(NAME)
	@echo "🧽 All CLEAN."

re: fclean all
