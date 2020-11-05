# EXECUTABLE
NAME = libgui-sdl.so

define uniq =
	$(shell echo $(1) | tr " " "\n" | cat -n | sort -uk2 | sort -nk1| cut -f2- | tr "\n" " ")
endef

# SOURCES
SRCS	= GuiSdl.cpp Program.cpp Shader.cpp

# OBJETS
OBJS	= $(SRCS:.cpp=.o)

# HEADERS
HEADERS			=  ../src/exceptions/Exceptions.hpp ../src/class/Score/Score.hpp ../src/class/Score/ScoreDataKey.hpp ../src/class/Elements/Walls.hpp ../src/class/Elements/Snake.hpp ../src/class/Elements/Food.hpp ../src/class/Elements/Foods.hpp ../src/class/Elements/Element.hpp ../src/class/Elements/Wall.hpp ../src/class/Gui/GUI.hpp ../src/class/Area/Area.hpp ../src/class/Cron/Cron.hpp ../src/class/Game/Game.hpp ../src/enum/Input.hpp ../src/enum/Direction.hpp ../src/enum/ElementType.hpp ../src/struct/Position.hpp ../src/struct/GameData.hpp ../src/struct/Cell.hpp
HEADERS_DIRS	= $(call uniq, $(dir $(HEADERS)))

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

# REGLES
all: $(NAME)

$(NAME): $(GLAD_DIR) $(STB_IMAGE_DIR) $(GLAD_DIR)/src/glad.o $(STB_IMAGE_DIR)/src/stb_image.o $(OBJS)
	@$(CC) -shared -fPIC -o $(NAME) $(OBJS) 
	@printf "\n$(NAME) has been created"
	@printf " $(GREEN)[OK]$(WHITE)\n"

%.o: %.cpp $(HEADERS)
	@printf "\033[2K\r$(BLUE)>>Compiling \033[37m$<$(BLUE)\033[0m"
	@$(CC) $(CFLAGS) -fPIC -I $(STB_IMAGE_DIR)/include -I $(GLAD_DIR)/include $(INCLUDES) -o $@ -c $<

$(GLAD_DIR)/src/glad.o: $(GLAD_DIR)/src/glad.c
	@printf "\033[2K\r\033[36m>>Compiling \033[37m$<\033[36m \033[0m"
	@clang -fPIC -I $(GLAD_DIR)/include -o $@ -c $<

$(STB_IMAGE_DIR)/src/stb_image.o: $(STB_IMAGE_DIR)/src/stb_image.c
	@printf "\033[2K\r\033[36m>>Compiling \033[37m$<\033[36m \033[0m"
	@clang -fPIC -I $(STB_IMAGE_DIR)/include -o $@ -c $<

.PHONY: clean clean-glad clean-stb_image fclean re ffclean

$(GLAD_DIR):
	@echo "\033[36mInstalling glad...\033[0m"
	@./scripts/install-glad.bash

$(STB_IMAGE_DIR):
	@echo "\033[36mInstalling stb_image...\033[0m"
	@./scripts/install-stb_image.bash

clean:
	@echo "\033[31mCleaning .o\033[0m"
	@rm -f $(OBJS)

fclean:	clean
	@echo "\033[31mCleaning $(NAME)\033[0m"
	@rm -f $(NAME)

clean-glad:
	@echo "\033[31mRemoving glad...\033[0m"
	@rm -rf $(GLAD_DIR)

clean-stb_image:
	@echo "\033[31mRemoving stb_image...\033[0m"
	@rm -rf $(STB_IMAGE_DIR)

ffclean: clean-glad clean-stb_image fclean

re: fclean all
