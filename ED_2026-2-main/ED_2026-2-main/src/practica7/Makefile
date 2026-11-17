cflags = -Wall -Werror -std=c99 -O2
includes = -I ../iostring -I ../datastructures/nodo -I ../datastructures/lista -I ../datastructures/arbol -I ../datastructures/heap -I .
libs = ../../lib -liostring -lHeap
source = $(wildcard *.c) 
output = ../../bin/practica7

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
run:
	$(output)
rebuild:
	make -C ..\iostring
	make -C ..\datastructures\nodo
	make -C ..\datastructures\lista
	make -C ..\datastructures\arbol
	make -C ..\datastructures\heap
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"