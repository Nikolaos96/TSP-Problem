/* File: robust_tsp.c */
#include "robust_tsp.h"

int robust_tsp(int **cost,int *chrom,int cities)
{int i, k2, k, temp;
double sum = 0.0;
	for(i = 0 ; i < cities ; i++){ /* Calculation cost */
		if(i != cities-1){
			k = chrom[i];
			k2 = chrom[i+1];
			if(k > k2){
				temp = k;
				k = k2;
				k2 = temp;
			}
			sum += cost[k-1][k2-k-1];
		}else{
			k = chrom[i];
			k2 = chrom[0];
			if(k > k2){
				temp = k;
				k = k2;
				k2 = temp;
			}
			sum += cost[k-1][k2-k-1];
		}
	}
return  sum;
}
