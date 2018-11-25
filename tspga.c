/* File: tspga.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "robust_tsp.h"
#include "mutation_tsp.h"
#include "junction_tsp.h"
#include "check_path.h"

struct tspga{
	int *chromosome;
	double robustness;
	double relative_rob;
	double incrementally;
};

int main(int argc, char *argv[])
{int cities, cities2, check = 0, read = 0, random,i, j, k, stop, p, p2, Blength, path;
int P = 100, G = 10000, **cost, counter = 0, *checkP, **newchrom, best_length, *array_path;
double PM = 0.1, PC = 0.5, Srob, best_gen, inc, max, random1;
char *arg;
FILE *fp;
struct tspga *tsp;
srand(time(NULL));
while(--argc){
 	arg = *++argv;
 	if(!strcmp(arg, "-P")){ if(argc > 1) P = atoi(*++argv);                                /* Population */
	 }else if(!strcmp(arg, "-G")){ if(argc > 1) G = atoi(*++argv);                         /* Generation */
	 }else if(!strcmp(arg, "-C")){ check = 1; ++argc;                                  /* Check snapshot */
	 }else if(!strcmp(arg, "-I")){                                                     /* Reaf from file */
	 	if(argc > 1){
	 	  fp = fopen(*++argv,"r");                                                  /* Open the file */
	 	  if(fp == NULL){
	 	  	printf("File doesn't exist\n");
	 	  	return -1;
		   }
	 	  read = 1;
	 	}
	 }else if(!strcmp(arg, "-PC")){ if(argc > 1) PC = atoi(*++argv);             /* Possibility junction */
	 }else if(!strcmp(arg, "-PM")){ if(argc > 1) PM = atoi(*++argv);             /* Possibility mutation */
	}
	 if(argc > 1) argc--;
 }
if(read == 0) scanf("%d", &cities);
else fscanf(fp , "%d", &cities);                                            /* Read from file crowd of cities */

if(cities <= 2 ){                                           /* If the crowd is smaller from 2 end the program */
    printf("Error\n");
    return -1;
}
tsp = malloc(P * sizeof(struct tspga));                                       /* Dynamic commitment structure */
if(tsp == NULL){
	printf("Memory error\n");
	return -1;
}
cost = malloc((cities-1) * sizeof(int*));         /* Dynamic commitment array 2D for cost βbetween the cities */
if(cost == NULL){
	printf("Memory error\n");
	return -1;
}
for(i = 0 ; i < cities-1 ; i++){
	cost[i] = malloc((cities-1) * sizeof(int));
	if(cost[i] == NULL){
		printf("Memory error\n");
		return -1;
	}
}
cities2 = cities-1;
if(read == 0){                                              /* Read cost between the cities and save in array */
	for(i = 0 ; i < cities-1 ; i++){                                                 /* Triangular αarray */
		for(j = 0 ; j < cities2 ; j++) scanf("%d", &cost[i][j]);
		cities2--;
	}
}else{                                            /* Read cost between the cities from file and save in array */
	for(i = 0 ; i < cities-1 ; i++){
		for(j = 0 ; j < cities2 ; j++) fscanf(fp, "%d", &cost[i][j]);
		cities2--;
	}
	fclose(fp);                                                        /* Close the file to read the cost */
}
if(check == 1){                                                                         /* Check the snapshot */
	checkP = malloc(cities * sizeof(int));
	if(checkP == NULL){
		printf("Memory error\n");
		return -1;
	}
	for(i = 0 ; i < cities ; i++) scanf("%d", &checkP[i]);                     /* Read the path for check */
    	check_path(checkP,cities,cost);                                     /* Function calculating all costs */
	free(checkP);                                                                          /* Free memory */
	for(i = 0 ; i < cities-1 ; i++) free(cost[i]);
	free(cost);
	return 0;
}
for(i = 0 ; i < P ; i++){                                    /* Dynamic commitment array inside the structure */
    tsp[i].chromosome = malloc(cities * sizeof(int));
    if(tsp[i].chromosome == NULL){
	   printf("Memory error\n");
       return -1;
    }
}
for(i = 0 ; i < P ; i++){                             /* Archive initial chromosome with different volue each */
	for(j = 0 ; j < cities ; j++){
		if(j == 0){
			random = rand() % cities + 1;                    /* Random number in space [1,cities) */
			tsp[i].chromosome[j] = random;
		}else{
			do{                                     /* Each number is different from all previous */
				stop = 1;
				random = rand() % cities + 1;
				for(k = 0 ; k < j ; k++){
					if(tsp[i].chromosome[k] == random) stop = 0;
				}
				if(stop == 1) tsp[i].chromosome[j] = random;
			}while(stop == 0);
		}
	}
}
newchrom = malloc(P * sizeof(int*));                                  /* Dynamic commitment ancillary array 2D */
if(newchrom == NULL){
	printf("Memory error\n");
	return -1;
}
for(i = 0 ; i < P ; i++){
	newchrom[i] = malloc(cities*sizeof(int));
	if(newchrom[i] == NULL){
		printf("Memory error\n");
		return -1;
	}
}
best_gen = -9000.0;
while(counter <= G){
	Srob = 0;
	max = -9999.0;
	for(i = 0 ; i < P ; i++){
		Blength = robust_tsp(cost,tsp[i].chromosome,cities-1);/* Calculation length for each chromosome */
		tsp[i].robustness = 1 / (double)Blength;                      /* Robustness for each chromosome */
		Srob += tsp[i].robustness;                                                    /* Sum robustness */
		if(tsp[i].robustness > max){                     /* Finding the best robustness each generation */
			max = tsp[i].robustness;
			best_length = Blength;
			p = i;
		}
	}
	printf("Generation %6d: Bfit = %f  AvFit = %f  BLength = %d\n", counter, max, Srob/(double)P, best_length);
	if(max > best_gen){                                      /* Finding the best length all the generations */
		best_gen = max;
		path = best_length;
		p2 = p;
		array_path = malloc(cities * sizeof(int));  /* Dynamic commitment array for the best chromosome */
		if(array_path == NULL){
			printf("Memory error\n");
			return -1;
		}                                                          /* Copy the best chromosome in array */
		for(i = 0 ; i < cities ; i++) array_path[i] = tsp[p2].chromosome[i];
	}
	for(i = 0 ; i < P ; i++){                                                  /* Calculation incrementally */
		tsp[i].relative_rob = tsp[i].robustness / Srob;
		inc = 0;
		for(j = 0 ; j <= i ; j++) inc += tsp[j].relative_rob;
		tsp[i].incrementally = inc;
	}
	for(i = 0 ; i < P ; i++){                                      /* Process selection */
		random1 = rand() / (((double)RAND_MAX) + 1);/* Random number in space [0,1) */
		for(j = 0 ; j < P ; j++){
			if(random1 < tsp[j].incrementally){
				for(k = 0 ; k < cities ; k++){
					newchrom[i][k] = tsp[j].chromosome[k];
				}
				break;
			}
		}
	}
	junction_tsp(newchrom,P,cities,PC);        /* Process junction with function */
	mutation_tsp(newchrom,P,cities,PM);        /* Process mutation with function */
	for(i = 0 ; i < P ; i++){  /* Copy current population in the next population */
		for(j = 0 ; j < cities ; j++) tsp[i].chromosome[j] = newchrom[i][j];
	}
	counter++;
}
printf("Best chromosome is: ");                         /* Print the best chromosome */
for(i = 0 ; i < cities ; i++) printf("%d ", array_path[i]);
printf("\n");
printf("Path length = %d\n", path);  /* Print the path length of the best chromosome */
for(i = 0 ; i < P ; i++) free(tsp[i].chromosome);    /* Free array inside the struct */
free(tsp);                                                        /* Free the struct */
for(i = 0 ; i < P ; i++) free(newchrom[i]);               /* Free ancillary array 2D */
free(newchrom);
for(i = 0 ; i < cities-1 ; i++) free(cost[i]);             /* Free array 2D for cost */
free(cost);
free(array_path);                             /* Free array with the best chromosome */
return 0;
}
/* End of main */
