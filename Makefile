# EXECUTABLE
NAME = nibbler

define uniq =
  $(eval seen :=)
  $(foreach _,$1,$(if $(filter $_,${seen}),,$(eval seen += $_)))
  ${seen}
endef

# SOURCES
SRCS_FILES_WILDCARD	= $(wildcard src/*.cpp) $(wildcard src/*/*.cpp) $(wildcard src/*/*/*.cpp)
SRCS_FILES			= $(SRCS_FILES_WILDCARD:src/%=%)
SRCS_MAIN_DIR		= src/
SRCS				= $(addprefix $(SRCS_MAIN_DIR), $(SRCS_FILES))

# OBJETS
OBJS_FILES		= $(SRCS_FILES:.cpp=.o)
OBJS_MAIN_DIR 	= objs/
OBJS 			= $(addprefix $(OBJS_MAIN_DIR), $(OBJS_FILES))
OBJS_DIRS 		= $(call uniq, $(dir $(OBJS)))

# HEADERS
HEADERS_FILES_WILDCARD	= $(wildcard src/*.hpp) $(wildcard src/*/*.hpp) $(wildcard src/*/*/*.hpp)
HEADERS_FILES 			= $(HEADERS_FILES_WILDCARD:src/%=%)
HEADERS					= $(addprefix $(SRCS_MAIN_DIR), $(HEADERS_FILES))
HEADERS_DIRS			= $(call uniq, $(dir $(HEADERS)))

# INCLUDES FOLDER
INCLUDES = $(addprefix -I, $(SRCS_MAIN_DIR) $(HEADERS_DIRS))

# LIBRARIES
BOOST_DIR = libs/boost
GLFW_DIR = libs/glfw
GLAD_DIR = libs/glad
STB_IMAGE_DIR = libs/stb_image
NCURSES_DIR = libs/ncurses

# COMPILATEUR
CC		= clang++
CFLAGS	= -Wall -Wextra -g3

# REGLES
all: $(NAME)

$(OBJS_DIRS):
	@mkdir -p $@

$(NAME): $(BOOST_DIR) $(GLFW_DIR) $(GLAD_DIR) $(STB_IMAGE_DIR) $(NCURSES_DIR) $(OBJS_DIRS) $(GLAD_DIR)/src/glad.o $(STB_IMAGE_DIR)/src/stb_image.o $(OBJS)
	@printf "\033[2K\r\033[36m>>Linking...\033[0m"
	@$(CC) -o $@ $(OBJS) $(GLAD_DIR)/src/glad.o $(STB_IMAGE_DIR)/src/stb_image.o -L$(BOOST_DIR)/bin -lboost_program_options -L$(GLFW_DIR)/bin -lglfw3 -L$(NCURSES_DIR)/bin -lncursesw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

	@echo "\t\033[32m[OK]\033[0m"
	@echo "\033[31m...$(shell echo $(NAME) | tr a-z A-Z)\033[0m"

$(OBJS_MAIN_DIR)%.o: $(SRCS_MAIN_DIR)%.cpp $(HEADERS)
	@printf "\033[2K\r\033[36m>>Compiling \033[37m$<\033[36m \033[0m"
	@$(CC) $(CFLAGS) -I $(BOOST_DIR)/include -I $(GLFW_DIR)/include -I $(GLAD_DIR)/include -I $(STB_IMAGE_DIR)/include -I $(NCURSES_DIR)/include $(INCLUDES) -o $@ -c $<

$(GLAD_DIR)/src/glad.o: $(GLAD_DIR)/src/glad.c
	@printf "\033[2K\r\033[36m>>Compiling \033[37m$<\033[36m \033[0m"
	@clang -I $(GLAD_DIR)/include -o $@ -c $<

$(STB_IMAGE_DIR)/src/stb_image.o: $(STB_IMAGE_DIR)/src/stb_image.c
	@printf "\033[2K\r\033[36m>>Compiling \033[37m$<\033[36m \033[0m"
	@clang -I $(STB_IMAGE_DIR)/include -o $@ -c $<

.PHONY: clean fclean re clean-boost clean-glfw clean-glad clean-ncurses clean-stb_image clean-libs ffclean

$(BOOST_DIR):
	@echo "\033[36mInstalling boost...\033[0m"
	@./scripts/install-boost.bash

$(GLFW_DIR):
	@echo "\033[36mInstalling glfw...\033[0m"
	@./scripts/install-glfw.bash

$(GLAD_DIR):
	@echo "\033[36mInstalling glad...\033[0m"
	@./scripts/install-glad.bash

$(STB_IMAGE_DIR):
	@echo "\033[36mInstalling stb_image...\033[0m"
	@./scripts/install-stb_image.bash

$(NCURSES_DIR):
	@echo "\033[36mInstalling ncurses...\033[0m"
	@./scripts/install-ncurses.bash

clean:
	@echo "\033[31mCleaning .o\033[0m"
	@rm -rf $(OBJS_MAIN_DIR)

fclean:	clean
	@echo "\033[31mCleaning $(NAME)\033[0m"
	@rm -f $(NAME)

clean-boost:
	@echo "\033[31mRemoving boost...\033[0m"
	@rm -rf $(BOOST_DIR)

clean-glfw:
	@echo "\033[31mRemoving glfw...\033[0m"
	@rm -rf $(GLFW_DIR)

clean-glad:
	@echo "\033[31mRemoving glad...\033[0m"
	@rm -rf $(GLAD_DIR)

clean-stb_image:
	@echo "\033[31mRemoving stb_image...\033[0m"
	@rm -rf $(STB_IMAGE_DIR)

clean-ncurses:
	@echo "\033[31mRemoving ncurses...\033[0m"
	@rm -rf $(NCURSES_DIR)

clean-libs:
	@echo "\033[31mRemoving all libs...\033[0m"
	@rm -rf libs

ffclean: clean-libs fclean

re: fclean all
