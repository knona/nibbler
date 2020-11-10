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

.PHONY: clean fclean re clean-boost clean-libs clean-guis ffclean libraries $(GUI_ALLEGRO) $(GUI_SFML) $(GUI_SDL) reload

# REGLES
all: $(NAME) $(GUI_ALLEGRO) $(GUI_SFML) $(GUI_SDL)

$(OBJS_DIRS):
	@mkdir -p $@

$(NAME): $(BOOST_DIR) $(OBJS_DIRS) $(OBJS) reload
	@printf "\033[2K\r$(BLUE)>>Linking...$(DEFAULT)"
	@$(CC) -o $@ $(OBJS) -L$(BOOST_DIR)/bin -lboost_program_options gui-allegro/libgui-allegro.so -lXpm -lXss -lGL -lX11 -lpthread -lXrandr -lXi -ldl -rdynamic
	@printf "\033[2K\r$(NAME) has been created $(GREEN)[OK]$(DEFAULT)\n"

$(OBJS_MAIN_DIR)%.o: $(SRCS_MAIN_DIR)%.cpp $(HEADERS)
	@printf "\033[2K\r$(BLUE)>>Compiling \033[37m$<$(BLUE) $(DEFAULT)"
	@$(CC) $(CFLAGS) -I $(BOOST_DIR)/include $(INCLUDES) -o $@ -c $<

$(BOOST_DIR):
	@echo "$(BLUE)Installing boost...$(DEFAULT)"
	@./scripts/install-boost.bash

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

clean-boost:
	@echo "$(RED)Removing boost...$(DEFAULT)"
	@rm -rf $(BOOST_DIR)

clean-libs:
	@echo "$(RED)Removing all libs...$(DEFAULT)"
	@rm -rf libs

clean-guis:
	@make -sC gui-allegro fclean
	@make -sC gui-sfml fclean
	@make -sC gui-sdl fclean

ffclean: clean-libs clean-guis fclean

re: fclean all