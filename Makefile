# EXECUTABLE
NAME = nibbler

define uniq =
  $(eval seen :=)
  $(foreach _,$1,$(if $(filter $_,${seen}),,$(eval seen += $_)))
  ${seen}
endef

# SOURCES
SRCS_FILES_WILDCARD	= $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
SRCS_FILES			= $(SRCS_FILES_WILDCARD:src/%=%)
SRCS_MAIN_DIR		= src/
SRCS				= $(addprefix $(SRCS_MAIN_DIR), $(SRCS_FILES))

# OBJETS
OBJS_FILES		= $(SRCS_FILES:.cpp=.o)
OBJS_MAIN_DIR 	= objs/
OBJS 			= $(addprefix $(OBJS_MAIN_DIR), $(OBJS_FILES))
OBJS_DIRS 		= $(call uniq, $(dir $(OBJS)))

# HEADERS
HEADERS_FILES_WILDCARD	= $(wildcard src/*.hpp) $(wildcard src/*/*.hpp)
HEADERS_FILES 			= $(HEADERS_FILES_WILDCARD:src/%=%)
HEADERS					= $(addprefix $(SRCS_MAIN_DIR), $(HEADERS_FILES))
HEADERS_DIRS			= $(call uniq, $(dir $(HEADERS)))

# INCLUDES FOLDER
INCLUDES = $(addprefix -I, $(SRCS_MAIN_DIR) $(HEADERS_DIRS))

BOOST_DIR = libs/boost

# COMPILATEUR
CC		= clang++
CFLAGS	= -Wall -Wextra -g3

# REGLES
all: libs $(OBJS_DIRS) $(NAME)

$(OBJS_DIRS):
	@mkdir -p $@

$(NAME): $(SRCS) $(OBJS)
	@printf "\033[2K\r\033[36m>>Linking...\033[0m"
	@$(CC) -o $@ $(OBJS) -Llibs/boost/binaries -lboost_program_options

	@echo "\t\033[32m[OK]\033[0m"
	@echo "\033[31m...$(shell echo $(NAME) | tr a-z A-Z)\033[0m"

$(OBJS_MAIN_DIR)%.o: $(SRCS_MAIN_DIR)%.cpp $(HEADERS)
	@printf "\033[2K\r\033[36m>>Compiling \033[37m$<\033[36m \033[0m"
	@$(CC) $(CFLAGS) -I libs/boost/headers $(INCLUDES) -o $@ -c $<

.PHONY: clean fclean re libs clean-boost clean-libs ffclean

libs: $(BOOST_DIR)

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

clean-libs: clean-boost

ffclean: clean-libs fclean

re: fclean all
