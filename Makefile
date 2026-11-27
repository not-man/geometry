geometry: main.o geometry.o fill.o grid.o io.o utils.o
	gcc main.o geometry.o fill.o grid.o io.o utils.o -o geometry

main.o: main.c geometry.h
	gcc main.c -c

geometry.o: geometry.c geometry.h
	gcc geometry.c -c

fill.o: fill.c geometry.h
	gcc fill.c -c

grid.o: grid.c geometry.h
	gcc grid.c -c

io.o: io.c geometry.h
	gcc io.c -c

utils.o: utils.c geometry.h
	gcc utils.c -c

run: geometry
	./geometry

clean:
	rm -f *.o geometry grid.pgm
