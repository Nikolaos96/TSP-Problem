/* File: mutation_tsp.c */
#include <stdlib.h>
#include "mutation_tsp.h"

void mutation_tsp(int **newchrom,int P,int cities,double PM)
{ int random1, random2, i, temp;
  double r;
	for(i = 0 ; i < P ; i++){ /* Mutation */
		r = rand() / (((double)RAND_MAX) + 1); /* Random number in space [0,1) */
		if(r < PM){
			random1 = rand() % cities;
			do{                          /* Random1 different from random2 */
				random2 = rand() % cities;
			}while(random2 == random1);
			temp = newchrom[i][random1];                 /* Exchange volue */
			newchrom[i][random1] = newchrom[i][random2];
			newchrom[i][random2] = temp;
		}
	}
  return;
}
