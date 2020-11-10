# EXECUTABLE
NAME = libgui-allegro.so

define uniq =
	$(shell echo $(1) | tr " " "\n" | cat -n | sort -uk2 | sort -nk1| cut -f2- | tr "\n" " ")
endef

# SOURCES
SRCS_FILES		= GuiAllegro.cpp
SRCS_MAIN_DIR	= src/
SRCS			= $(addprefix $(SRCS_MAIN_DIR), $(SRCS_FILES))

# OBJETS
OBJS_FILES		= $(SRCS_FILES:.cpp=.o)
OBJS_MAIN_DIR 	= objs/
OBJS 			= $(addprefix $(OBJS_MAIN_DIR), $(OBJS_FILES))

# HEADERS
HEADERS			=  src/GuiAllegro.hpp ../src/exceptions/Exceptions.hpp ../src/class/Score/Score.hpp ../src/class/Score/ScoreDataKey.hpp ../src/class/Elements/Walls.hpp ../src/class/Elements/Snake.hpp ../src/class/Elements/Food.hpp ../src/class/Elements/Foods.hpp ../src/class/Elements/Element.hpp ../src/class/Elements/Wall.hpp ../src/class/Gui/GUI.hpp ../src/class/Area/Area.hpp ../src/class/Cron/Cron.hpp ../src/class/Game/Game.hpp ../src/enum/Input.hpp ../src/enum/Direction.hpp ../src/enum/ElementType.hpp ../src/struct/Position.hpp ../src/struct/GameData.hpp ../src/struct/Cell.hpp
HEADERS_DIRS	= $(call uniq, src/ $(dir $(HEADERS)))

# INCLUDES FOLDER
INCLUDES = $(addprefix -I, $(HEADERS_DIRS))

# LIBRARIES
ALLEGRO_DIR=libs/allegro

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

.PHONY: clean clean-allegro clean-libs fclean re ffclean

# REGLES
all: $(NAME)

$(OBJS_MAIN_DIR):
	@mkdir -p $@

$(NAME): $(ALLEGRO_DIR) $(OBJS_MAIN_DIR) $(OBJS)
	@$(CC) -shared -o $(NAME) $(OBJS) \
	-Wl,--whole-archive -shared	\
	-L$(ALLEGRO_DIR)/lib/ -lallegro-static \
	-L$(ALLEGRO_DIR)/lib/ -lallegro_color-static \
	-L$(ALLEGRO_DIR)/lib/ -lallegro_font-static \
	-L$(ALLEGRO_DIR)/lib/ -lallegro_image-static \
	-L$(ALLEGRO_DIR)/lib/ -lallegro_main-static \
	-L$(ALLEGRO_DIR)/lib/ -lallegro_primitives-static \
	-L$(ALLEGRO_DIR)/lib/ -lallegro_ttf-static \
	-Wl,--no-whole-archive \
	-lfreetype -lgtk-3 -lXpm -lXss -lGL


	@printf "\033[2K\r$(NAME) has been created $(GREEN)[OK]$(WHITE)\n"

$(OBJS_MAIN_DIR)%.o: $(SRCS_MAIN_DIR)%.cpp $(HEADERS)
	@printf "\033[2K\r$(BLUE)>>Compiling \033[37m$<$(BLUE)$(DEFAULT)"
	@$(CC) $(CFLAGS) -I $(ALLEGRO_DIR)/include $(INCLUDES) -fPIC -o $@ -c $<

$(ALLEGRO_DIR):
	@echo "$(BLUE)Installing allegro...$(DEFAULT)"
	@./scripts/install-allegro.bash

clean:
	@echo "\033[31mCleaning .o$(DEFAULT)"
	@rm -rf $(OBJS_MAIN_DIR)

fclean:	clean
	@echo "\033[31mCleaning $(NAME)$(DEFAULT)"
	@rm -f $(NAME)

clean-allegro:
	@echo "$(RED)Removing allegro...$(DEFAULT)"
	@rm -rf $(ALLEGRO_DIR)

clean-libs:
	@echo "$(RED)Removing all libs...$(DEFAULT)"
	@rm -rf libs

ffclean: clean-libs fclean

re: fclean all
