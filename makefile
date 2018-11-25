tspga: tspga.o check_path.o robust_tsp.o junction_tsp.o mutation_tsp.o
	gcc tspga.o check_path.o robust_tsp.o junction_tsp.o mutation_tsp.o -o tspga

tspga.o: tspga.c
	gcc -c tspga.c

check_path.o: check_path.c
	gcc -c check_path.c

robust_tsp.o: robust_tsp.c
	gcc -c robust_tsp.c

junction_tsp.o: junction_tsp.c
	gcc -c junction_tsp.c

mutation_tsp.o: mutation_tsp.c
	gcc -c mutation_tsp.c
