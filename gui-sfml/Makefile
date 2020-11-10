# EXECUTABLE
NAME = libgui-sfml.so

define uniq =
	$(shell echo $(1) | tr " " "\n" | cat -n | sort -uk2 | sort -nk1| cut -f2- | tr "\n" " ")
endef

# SOURCES
SRCS_FILES		= GuiSfml.cpp
SRCS_MAIN_DIR	= src/
SRCS			= $(addprefix $(SRCS_MAIN_DIR), $(SRCS_FILES))

# OBJETS
OBJS_FILES		= $(SRCS_FILES:.cpp=.o)
OBJS_MAIN_DIR 	= objs/
OBJS 			= $(addprefix $(OBJS_MAIN_DIR), $(OBJS_FILES))

# HEADERS
HEADERS			= src/GuiSfml.hpp ../src/exceptions/Exceptions.hpp ../src/class/Score/Score.hpp ../src/class/Score/ScoreDataKey.hpp ../src/class/Elements/Walls.hpp ../src/class/Elements/Snake.hpp ../src/class/Elements/Food.hpp ../src/class/Elements/Foods.hpp ../src/class/Elements/Element.hpp ../src/class/Elements/Wall.hpp ../src/class/Gui/GUI.hpp ../src/class/Area/Area.hpp ../src/class/Cron/Cron.hpp ../src/class/Game/Game.hpp ../src/enum/Input.hpp ../src/enum/Direction.hpp ../src/enum/ElementType.hpp ../src/struct/Position.hpp ../src/struct/GameData.hpp ../src/struct/Cell.hpp
HEADERS_DIRS	= $(call uniq, src/ $(dir $(HEADERS)))

# INCLUDES FOLDER
INCLUDES = $(addprefix -I, $(HEADERS_DIRS))

# LIBRARIES
SFML_DIR=libs/sfml

# COMPILATEUR
CC		= clang++
CFLAGS	= -Wall -Wextra -Werror -g3 --std=c++17

# TEXT
RED = \033[31m
WHITE = \033[0;29m
YELLOW = \033[33m
PINK = \033[35m
GREEN = \033[32m
BLUE = \033[36m
DEFAULT = \033[0m

.PHONY: clean clean-sfml clean-libs fclean re ffclean

# REGLES
all: $(NAME)

$(OBJS_MAIN_DIR):
	@mkdir -p $@

$(NAME): $(SFML_DIR) $(OBJS_MAIN_DIR) $(OBJS)
	@$(CC) -shared \
		-o $(NAME) $(OBJS) \
		-Wl,--whole-archive -shared	\
			-L$(SFML_DIR)/lib/ -lsfml-graphics-s \
			-L$(SFML_DIR)/lib/ -lsfml-system-s \
			-L$(SFML_DIR)/lib/ -lsfml-window-s \
		-Wl,--no-whole-archive \
		-ludev
	@printf "\033[2K\r$(NAME) has been created $(GREEN)[OK]$(WHITE)\n"

$(OBJS_MAIN_DIR)%.o: $(SRCS_MAIN_DIR)%.cpp $(HEADERS)
	@printf "\033[2K\r$(BLUE)>>Compiling \033[37m$<$(BLUE)\033[0m"
	@$(CC) $(CFLAGS) $(INCLUDES) -I$(SFML_DIR)/include -fPIC -o $@ -c $<

$(SFML_DIR):
	@echo "$(BLUE)Installing sfml...$(DEFAULT)"
	@./scripts/install-sfml.bash

clean:
	@echo "\033[31mCleaning .o\033[0m"
	@rm -rf $(OBJS_MAIN_DIR)

fclean:	clean
	@echo "\033[31mCleaning $(NAME)\033[0m"
	@rm -f $(NAME)

clean-sfml:
	@echo "$(RED)Removing sfml...$(DEFAULT)"
	@rm -rf $(SFML_DIR)

clean-libs:
	@echo "$(RED)Removing all libs...$(DEFAULT)"
	@rm -rf libs

re: fclean all

ffclean: clean-libs fclean
