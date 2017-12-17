all : 
	gcc -o game main_game.c move.c screen.c score.c -lcurses -lpthread
