NAME = pipex

SRC_DIR = Source

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/paths.c $(SRC_DIR)/utils.c $(SRC_DIR)/heredoc.c $(SRC_DIR)/errors.c \
$(SRC_DIR)/freeing.c

OBJ = $(SRC: *.c=*.o)

LIB_DIR = libft

CC = gcc

MAKE = make

FLAGS =  -Werror -Wextra -Wall

AR = ar cr

all: $(NAME)

LIBRARY:
	make -C libft

$(NAME): LIBRARY $(OBJ) 
	$(CC) $(FLAGS) $(OBJ) $(LIB_DIR)/libft.a -o pipex

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C libft


fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a
	rm -f pipex

re: fclean all

.PHONY: all fclean clean re

