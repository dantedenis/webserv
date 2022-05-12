NAME	= webserv
CC		= g++
FLAGS	= -Werror -Wall -Wextra -std=c++98
INCLUDE	= -I ./inc
VPATH	:= ./Server

SRC_LST		= $(notdir $(wildcard ./Server/*.cpp))
HEADERS		= $(wildcard ./Server/*.hpp)

OBJ_PATH	=./bin/
OBJ			= $(addprefix $(OBJ_PATH), $(patsubst %.cpp, %.o, $(SRC_LST)))

.PHONY: all clean fclean re target
.SILENT: all clean fclean re $(OBJ_PATH)

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	echo "Create ./bin"
	mkdir -p $(OBJ_PATH)

$(NAME): $(OBJ_PATH) $(OBJ)
	$(CC) $(OBJ) -o $@


$(OBJ_PATH)%.o : %.cpp $(HEADERS)
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean :
	echo "Delete ./bin"
	rm -rf $(OBJ_PATH)

fclean : clean
	echo "Delete $(NAME)"
	rm -f $(NAME)

re : fclean all