##
## EPITECH PROJECT, 2024
## sokoban
## File description:
## Makefile
##

SRC = 	main.c \
		game_files/difficulty.c \
		game_files/sokoban.c \
		game_files/menus.c \
		game_files/texture_generation.c \
		game_files/settings.c \

OBJ = $(SRC:.c=.o)

NAME = sokoban

CFLAGS = -g

all: $(OBJ)
	gcc -o $(NAME) $(OBJ) -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -fsanitize=address

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f *.o

re: fclean all
