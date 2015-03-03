model.tos: model.o enemy.o missile.o player.o
	cc68x -g -c -v model.o enemy.o missile.o player.o -o model

model.o: model.c model.h
	cc68x -g -c -v model.c

enemy.o: enemy.c enemy.h
	cc68x -g -c -v enemy.c

missile.o: missile.c missile.h
	cc68x -g -c -v missile.c
	
player.o: player.c
	cc68x -g -c -v player.c

