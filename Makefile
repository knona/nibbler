# EXECUTABLE
NAME = nibbler

define uniq =
	$(shell echo $(1) | tr " " "\n" | cat -n | sort -uk2 | sort -nk1| cut -f2- | tr "\n" " ")
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
INCLUDES = $(addprefix -I, $(call uniq,$(SRCS_MAIN_DIR) $(HEADERS_DIRS)))

# LIBRARIES
BOOST_DIR = libs/boost

# COMPILATEUR
CC		= clang++
CFLAGS	= -Wall -Wextra -g3 --std=c++17

# REGLES
all: $(NAME)

$(OBJS_DIRS):
	@mkdir -p $@

$(NAME): $(BOOST_DIR) $(OBJS_DIRS) $(OBJS)
	@printf "\033[2K\r\033[36m>>Linking...\033[0m"
	@$(CC) -o $@ $(OBJS) -L$(BOOST_DIR)/bin -lboost_program_options -lallegro_font -lallegro_ttf -lallegro_primitives -lallegro -lSDL2 -lSDL2_ttf -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lsfml-graphics -lsfml-window -lsfml-system

	@echo "\t\033[32m[OK]\033[0m"
	@echo "\033[31m...$(shell echo $(NAME) | tr a-z A-Z)\033[0m"

$(OBJS_MAIN_DIR)%.o: $(SRCS_MAIN_DIR)%.cpp $(HEADERS)
	@printf "\033[2K\r\033[36m>>Compiling \033[37m$<\033[36m \033[0m"
	@$(CC) $(CFLAGS) -I $(BOOST_DIR)/include $(INCLUDES) -o $@ -c $<

.PHONY: clean fclean re clean-boost clean-stb_image clean-libs ffclean

$(BOOST_DIR):
	@echo "\033[36mInstalling boost...\033[0m"
	@./scripts/install-boost.bash

clean:
	@echo "\033[31mCleaning .o\033[0m"
	@rm -rf $(OBJS_MAIN_DIR)

fclean:	clean
	@echo "\033[31mCleaning $(NAME)\033[0m"
	@rm -f $(NAME)

clean-boost:
	@echo "\033[31mRemoving boost...\033[0m"
	@rm -rf $(BOOST_DIR)

ffclean: clean-boost fclean

re: fclean all
