/* File: junction_tsp.c */
#include <stdlib.h>
#include "junction_tsp.h"

void junction_tsp(int **newchrom,int P,int cities,double PC)
{ int i, j, random1, random2, A[cities], B[cities], temp, k, l;
double r;
  for(i = 0 ; i < P-1 ; i=i+2){
  	r = rand() / (((double)RAND_MAX) + 1);
  	if(r < PC){
  		random1 = rand() % (cities-1) + 1;
  		do{
  			random2 = rand() % (cities-1) + 1;
		  }while(random2 == random1);
  		if(random1 > random2){
  			temp = random1;
  			random1 = random2;
  			random2 = temp;
		  }
  		for(j = random2 ; j < cities ; j++){
  			A[j-random2] = newchrom[i+1][j];
  			B[j-random2] = newchrom[i][j];
		  }
		  for(j = 0 ; j < random2 ; j++){
		  	A[cities-random2+j] = newchrom[i+1][j];
			B[cities-random2+j] = newchrom[i][j];
		  }
		  for(j = 0 ; j < cities ; j++){
		  	for(k = random1 ; k < random2 ; k++){
		  		if(A[j] == newchrom[i][k]) A[j] = -1;
		  		if(B[j] == newchrom[i+1][k]) B[j] = -1;
			  }
		  }
		  k = 0;
		  l = 0;
		  for(j = random2 ; j < cities ; j++){
		  	while(A[k+j-random2] == -1){
		  		k++;
			  }
			  newchrom[i][j] = A[k+j-random2];
			  while(B[l+j-random2] == -1){
			  	l++;
			  }
			  newchrom[i+1][j] = B[l+j-random2];
		  }
		  for(j = 0 ; j < random1 ; j++){
		  	while(A[cities-random2+k+j] == -1){
		  		k++;
			  }
			  newchrom[i][j] = A[cities-random2+k+j];
			  while(B[cities-random2+l+j] == -1){
			  	l++;
			  }
			  newchrom[i+1][j] = B[cities-random2+l+j];
		  }
	  }
  }
	return;
}
