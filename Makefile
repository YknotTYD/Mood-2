##
## EPITECH PROJECT, 2024
## Chip8TYD
## File description:
## A Chip8 TYD Emulator;
##

SRC  = src/*.c
LIBS = -l SDL2 -l m
NAME = Mood2
DEFAULTARGS  = ""

compile:
	@ gcc -g -Wall -Wextra $(SRC) $(LIBS) \
		-o $(NAME)

compile_Ofast:
	@ gcc -Ofast -Wall -Wextra $(SRC) $(LIBS) \
		-o $(NAME)

run: compile
	@ ./$(NAME) $(DEFAULTARGS)
	@ rm $(NAME)

log: compile
	@ ./$(NAME) $(DEFAULTARGS) > ~log
	@ rm $(NAME)

logless: compile
	@ ./$(NAME) $(DEFAULTARGS) > ~log
	@ rm $(NAME)
	@ cat ~log | less
	@rm ~log

valgrind: compile
	@valgrind -s --show-leak-kinds=none \
		--track-origins=yes \
		--leak-check=full \
		--error-limit=no \
	./$(NAME) $(DEFAULTROM)
	@ rm $(NAME)

clean:
	@ rm -fr *.o

fclean: clean
	@ rm -f $(NAME)

re: fclean compile

kronk:
	@ echo "Oh ouais."
