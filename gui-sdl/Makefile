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
SDL_DIR = libs/sdl
GLAD_DIR = libs/glad
STB_IMAGE_DIR = libs/stb_image
GLM_DIR = libs/glm

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

.PHONY: clean clean-sdl clean-glad clean-stb_image clean-glm clean-libs ffclean fclean re

# REGLES
all: $(NAME)

$(OBJS_MAIN_DIR):
	@mkdir -p $@

$(NAME): $(SDL_DIR) $(GLAD_DIR) $(GLAD_DIR)/src/glad.o $(STB_IMAGE_DIR) $(STB_IMAGE_DIR)/src/stb_image.o $(GLM_DIR) $(OBJS_MAIN_DIR) $(OBJS)
	@$(CC) -shared -o $(NAME) $(OBJS) \
	$(GLAD_DIR)/src/glad.o \
	$(STB_IMAGE_DIR)/src/stb_image.o \
	-Wl,--whole-archive -shared	\
	-L$(SDL_DIR)/lib -lSDL2 \
	-L$(SDL_DIR)/lib -lSDL2_ttf \
	-Wl,--no-whole-archive \

	@printf "\033[2K\r$(NAME) has been created $(GREEN)[OK]$(WHITE)\n"

$(OBJS_MAIN_DIR)%.o: $(SRCS_MAIN_DIR)%.cpp $(HEADERS)
	@printf "\033[2K\r$(BLUE)>>Compiling \033[37m$<$(BLUE)\033[0m"
	@$(CC) $(CFLAGS) -fPIC -I $(SDL_DIR)/include -I $(STB_IMAGE_DIR)/include -I $(GLAD_DIR)/include -I $(GLM_DIR)/include $(INCLUDES) -o $@ -c $<

$(SDL_DIR):
	@echo "$(BLUE)Installing sdl...$(DEFAULT)"
	@./scripts/install-sdl.bash
	@echo "$(BLUE)Installing sdl-ttf...$(DEFAULT)"
	@./scripts/install-sdl_ttf.bash

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

$(GLM_DIR):
	@echo "$(BLUE)Installing glm...$(DEFAULT)"
	@./scripts/install-glm.bash

clean:
	@echo "\033[31mCleaning .o\033[0m"
	@rm -rf $(OBJS_MAIN_DIR)

fclean:	clean
	@echo "\033[31mCleaning $(NAME)\033[0m"
	@rm -f $(NAME)

clean-sdl:
	@echo "$(RED)Removing sdl...$(DEFAULT)"
	@rm -rf $(SDL_DIR)

clean-glad:
	@echo "$(RED)Removing glad...$(DEFAULT)"
	@rm -rf $(GLAD_DIR)

clean-stb_image:
	@echo "$(RED)Removing stb_image...$(DEFAULT)"
	@rm -rf $(STB_IMAGE_DIR)

clean-glm:
	@echo "$(RED)Removing glm...$(DEFAULT)"
	@rm -rf $(GLM_DIR)

clean-libs:
	@echo "$(RED)Removing all libs...$(DEFAULT)"
	@rm -rf libs

ffclean: clean-libs fclean

re: fclean all
