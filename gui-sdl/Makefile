# EXECUTABLE
NAME = libgui-sdl.so

define uniq =
	$(shell echo $(1) | tr " " "\n" | cat -n | sort -uk2 | sort -nk1| cut -f2- | tr "\n" " ")
endef

# SOURCES
SRCS_FILES		= GuiSdl.cpp Program.cpp Shader.cpp
SRCS_MAIN_DIR	= src/
SRCS			= $(addprefix $(SRCS_MAIN_DIR), $(SRCS_FILES))

# OBJETS
OBJS_FILES		= $(SRCS_FILES:.cpp=.o)
OBJS_MAIN_DIR 	= objs/
OBJS 			= $(addprefix $(OBJS_MAIN_DIR), $(OBJS_FILES))

# HEADERS
HEADERS			=  src/Shader.hpp src/Program.hpp src/Texture.hpp src/GuiSdl.hpp ../src/exceptions/Exceptions.hpp ../src/class/Score/Score.hpp ../src/class/Score/ScoreDataKey.hpp ../src/class/Elements/Walls.hpp ../src/class/Elements/Snake.hpp ../src/class/Elements/Food.hpp ../src/class/Elements/Foods.hpp ../src/class/Elements/Element.hpp ../src/class/Elements/Wall.hpp ../src/class/Gui/GUI.hpp ../src/class/Area/Area.hpp ../src/class/Cron/Cron.hpp ../src/class/Game/Game.hpp ../src/enum/Input.hpp ../src/enum/Direction.hpp ../src/enum/ElementType.hpp ../src/struct/Position.hpp ../src/struct/GameData.hpp ../src/struct/Cell.hpp
HEADERS_DIRS	= $(call uniq, src/ $(dir $(HEADERS)))

# INCLUDES FOLDER
INCLUDES = $(addprefix -I, $(HEADERS_DIRS))

# LIBRARIES
GLAD_DIR = libs/glad
STB_IMAGE_DIR = libs/stb_image

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

.PHONY: clean clean-glad clean-stb_image clean-libs ffclean fclean re

# REGLES
all: $(NAME)

$(OBJS_MAIN_DIR):
	@mkdir -p $@

$(NAME): $(GLAD_DIR) $(GLAD_DIR)/src/glad.o $(STB_IMAGE_DIR) $(STB_IMAGE_DIR)/src/stb_image.o $(OBJS_MAIN_DIR) $(OBJS)
	@$(CC) -shared -o $(NAME) $(OBJS) $(GLAD_DIR)/src/glad.o $(STB_IMAGE_DIR)/src/stb_image.o -lSDL2 -lSDL2_ttf
	@printf "\033[2K\r$(NAME) has been created $(GREEN)[OK]$(WHITE)\n"

$(OBJS_MAIN_DIR)%.o: $(SRCS_MAIN_DIR)%.cpp $(HEADERS)
	@printf "\033[2K\r$(BLUE)>>Compiling \033[37m$<$(BLUE)$(DEFAULT)"
	@$(CC) $(CFLAGS) -fPIC -I $(STB_IMAGE_DIR)/include -I $(GLAD_DIR)/include $(INCLUDES) -o $@ -c $<

$(GLAD_DIR):
	@echo "$(BLUE)Installing glad...$(DEFAULT)"
	@./scripts/install-glad.bash

$(GLAD_DIR)/src/glad.o: $(GLAD_DIR)/src/glad.c
	@echo "\033[2K\r$(BLUE)>>Compiling \033[37m$<$(BLUE) $(DEFAULT)"
	@clang -I $(GLAD_DIR)/include -fPIC -o $@ -c $<

$(STB_IMAGE_DIR):
	@echo "$(BLUE)Installing stb_image...$(DEFAULT)"
	@./scripts/install-stb_image.bash

$(STB_IMAGE_DIR)/src/stb_image.o: $(STB_IMAGE_DIR)/src/stb_image.c
	@echo "\033[2K\r$(BLUE)>>Compiling \033[37m$<$(BLUE) $(DEFAULT)"
	@clang -I $(STB_IMAGE_DIR)/include -fPIC -o $@ -c $<

clean:
	@echo "\033[31mCleaning .o$(DEFAULT)"
	@rm -rf $(OBJS_MAIN_DIR)

fclean:	clean
	@echo "\033[31mCleaning $(NAME)$(DEFAULT)"
	@rm -f $(NAME)

clean-glad:
	@echo "$(RED)Removing glad...$(DEFAULT)"
	@rm -rf $(GLAD_DIR)

clean-stb_image:
	@echo "$(RED)Removing stb_image...$(DEFAULT)"
	@rm -rf $(STB_IMAGE_DIR)

clean-libs:
	@echo "$(RED)Removing all libs...$(DEFAULT)"
	@rm -rf libs

ffclean: clean-libs fclean

re: fclean all
