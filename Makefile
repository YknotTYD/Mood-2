
all:
	gcc -Wall -Wextra *.c -l csfml-graphics -l csfml-window -lm -o damien 

run:
	gcc -Wall -Wextra *.c -l csfml-graphics -l csfml-window -lm -o damien
	./damien
	rm damien

valgrind:
	gcc -Wall -Wextra *.c -l csfml-graphics -l csfml-window -lm -o damien
	valgrind -s --show-leak-kinds=none --track-origins=yes --leak-check=full --error-limit=no ./damien
	rm damien
