# EXECUTABLE
NAME = nibbler

define uniq =
	$(shell echo $(1) | tr " " "\n" | cat -n | sort -uk2 | sort -nk1| cut -f2- | tr "\n" " ")
endef

# SOURCES
SRCS_FILES			= exceptions/Exceptions.cpp nibbler.cpp class/Score/ScoreDataKey.cpp class/Score/Score.cpp class/GuiManager/GuiManager.cpp class/Parser/Parser.cpp class/Elements/Food.cpp class/Elements/Element.cpp class/Elements/Walls.cpp class/Elements/Wall.cpp class/Elements/Snake.cpp class/Elements/Foods.cpp class/Area/Area.cpp class/Cron/Cron.cpp class/Game/Game.cpp struct/Cell.cpp struct/Position.cpp
SRCS_MAIN_DIR		= src/
SRCS				= $(addprefix $(SRCS_MAIN_DIR), $(SRCS_FILES))

# OBJETS
OBJS_FILES		= $(SRCS_FILES:.cpp=.o)
OBJS_MAIN_DIR 	= objs/
OBJS 			= $(addprefix $(OBJS_MAIN_DIR), $(OBJS_FILES))
OBJS_DIRS 		= $(call uniq, $(dir $(OBJS)))

# HEADERS
HEADERS_FILES_WILDCARD	= exceptions/Exceptions.hpp class/Score/Score.hpp class/Score/ScoreDataKey.hpp class/GuiManager/GuiManager.hpp class/Parser/Parser.hpp class/Elements/Walls.hpp class/Elements/Snake.hpp class/Elements/Food.hpp class/Elements/Foods.hpp class/Elements/Element.hpp class/Elements/Wall.hpp class/Gui/GUI.hpp class/Area/Area.hpp class/Cron/Cron.hpp class/Game/Game.hpp enum/Input.hpp enum/Direction.hpp enum/ElementType.hpp struct/Position.hpp struct/GameData.hpp struct/Options.hpp struct/Cell.hpp
HEADERS_FILES 			= $(HEADERS_FILES_WILDCARD:src/%=%)
HEADERS					= $(addprefix $(SRCS_MAIN_DIR), $(HEADERS_FILES))
HEADERS_DIRS			= $(call uniq, $(dir $(HEADERS)))

# INCLUDES FOLDER
INCLUDES = $(addprefix -I, $(call uniq,$(SRCS_MAIN_DIR) $(HEADERS_DIRS)))

# GUIS
GUI_ALLEGRO = gui-allegro/libgui-allegro.so
GUI_SFML = gui-sfml/libgui-sfml.so
GUI_SDL = gui-sdl/libgui-sdl.so

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

.PHONY: clean fclean ffclean re clean-guis $(GUI_ALLEGRO) $(GUI_SFML) $(GUI_SDL)

# REGLES
all: $(NAME) $(GUI_ALLEGRO) $(GUI_SFML) $(GUI_SDL)

$(OBJS_DIRS):
	@mkdir -p $@

$(NAME): $(OBJS_DIRS) $(OBJS)
	@printf "\033[2K\r$(BLUE)>>Linking...$(DEFAULT)"
	@$(CC) -o $@ $(OBJS) -lboost_program_options -lstdc++fs -ldl -rdynamic
	@printf "\033[2K\r$(NAME) has been created $(GREEN)[OK]$(DEFAULT)\n"

$(OBJS_MAIN_DIR)%.o: $(SRCS_MAIN_DIR)%.cpp $(HEADERS)
	@printf "\033[2K\r$(BLUE)>>Compiling \033[37m$<$(BLUE) $(DEFAULT)"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(GUI_ALLEGRO):
	@make -sC gui-allegro

$(GUI_SFML):
	@make -sC gui-sfml

$(GUI_SDL):
	@make -sC gui-sdl

clean:
	@echo "$(RED)Cleaning .o$(DEFAULT)"
	@rm -rf $(OBJS_MAIN_DIR)

fclean:	clean
	@echo "$(RED)Cleaning $(NAME)$(DEFAULT)"
	@rm -f $(NAME)

clean-guis:
	@make -sC gui-allegro fclean
	@make -sC gui-sfml fclean
	@make -sC gui-sdl fclean

ffclean: clean-guis fclean

re: fclean all