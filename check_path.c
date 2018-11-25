/* File: check_path.c */
#include <stdio.h>
#include "check_path.h"

void check_path(int *check,int cities,int **cost)
{int count = 0, i, j, sum = 0, k, k2, temp;
for(i = 0 ; i < cities ; i++){ /* Check if each citie exists once time */
	for(j = 0 ; j < cities ; j++){
		if(i+1 == check[j]){
			count++;
			break;
		}
	}
}
if(count == cities){                          /* Print the length path */
	for(i = 0 ; i < cities ; i++){             /* Calculation cost */
		if(i != cities-1){
			k = check[i];
			k2 = check[i+1];
			if(k > k2){
				temp = k;
				k = k2;
				k2 = temp;
			}
			sum += cost[k-1][k2-k-1];
		}else{
			k = check[i];
			k2 = check[0];
			if(k > k2){
				temp = k;
				k = k2;
				k2 = temp;
			}
			sum += cost[k-1][k2-k-1];
		}
	}
	printf("Path length: %d\n", sum);
}else{                                           /* Print error message */
	printf("The path is faild\n");
}
return;	
}
