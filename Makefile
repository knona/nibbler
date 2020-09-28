# EXECUTABLE
NAME = nibbler

# SOURCES
SRC = $(wildcard *.cpp)

# HEADERS
HEADERS = $(wildcard *.hpp)

# OBJETS
OBJ = $(SRC:.cpp=.o)

# COMPILATEUR
CC		=	clang++
CFLAGS	=	-Wall -Wextra -g3

# REGLES
all: $(NAME)

$(NAME): $(OBJ)
	@printf "\033[2K\r\033[36m>>Linking...\033[0m"
	@$(CC) -o $@ $(OBJ) -Lboost/binaries -lboost_program_options

	@echo "\t\033[32m[OK]\033[0m"
	@echo "\033[31m...$(shell echo $(NAME) | tr a-z A-Z)\033[0m"

%.o: %.cpp $(HEADERS)
	@printf "\033[2K\r\033[36m>>Compiling \033[37m$<\033[36m \033[0m"
	@$(CC) $(CFLAGS) -o $@ -c $< -I boost/headers

.PHONY: clean fclean re

clean:
	@echo "\033[31mCleaning .o\033[0m"
	@rm -f $(OBJ)

fclean:	clean
	@echo "\033[31mCleaning $(NAME)\033[0m"
	@rm -f $(NAME)

re:		fclean all