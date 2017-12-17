all : 
	gcc -o game main_game.c move.c score.c -lcurses -lpthread
