#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz_utils/matriz_utils.h"

#define ALEATORIO ((double)random() / (double)RAND_MAX)

int main(int argc , char *argv[]){
    double alpha;
    int iterations;
    int nU, nF, nI;
    int num_ratings;

    FILE *entrada;
    if(argc < 2 || ((entrada = fopen(argv[1], "r")) == NULL)){
        printf("Erro ao abrir o ficheiro de entrada: %s\n", argv[1]);
        return 0;
    }

    //read parameters from file
    fscanf(entrada, "%d", &iterations);
    fscanf(entrada, "%lf", &alpha);
    fscanf(entrada, "%d", &nF);
    fscanf(entrada, "%d", &nU);
    fscanf(entrada, "%d", &nI);
    fscanf(entrada, "%d", &num_ratings);

    double L[nU][nF];
    double R[nF][nI];
    double B[nU][nI];
    double A[nU][nI];
    
    //set all elements of array A to 0 
    memset(A, 0, sizeof(A[0]) * nU);
    
    //initialize ratings matrix A
    for(int a = 0; a < num_ratings; a++){
        int i,j;
        fscanf(entrada, "%d", &i);
        fscanf(entrada, "%d", &j);
        fscanf(entrada, "%lf", &A[i][j]);
    }

    // Initialize matrices with random values
    srandom(0);
    for(int i = 0; i < nU; i++)
        for(int j = 0; j < nF; j++)
            L[i][j] = ALEATORIO / (double) nF;

    for(int i = 0; i < nF; i++)
        for(int j = 0; j < nI; j++)
            R[i][j] = ALEATORIO / (double) nF;

    mtrz_multiply(nU, nF, L, nF, nI, R, B);

    
    double L_t[nU][nF];
    double R_t[nF][nI];
    // Calculate recomendations matrix
    for(int iter = 0; iter < iterations; iter++){
        //update matrix R
        for(int k = 0; k < nF; k++){
            //update matrix R
            for(int j = 0; j < nI; j++){
                double sum = 0.0;

                for(int i = 0; i < nU; i++)
                    if(A[i][j] > 0)
                        sum += 2 * (A[i][j] - B[i][j]) * (-L[i][k]);
                
                R_t[k][j] = R[k][j] - alpha * sum;
            }

            //update matrix L
            for(int i = 0; i < nU; i++){
                double sum = 0.0;

                for(int j = 0; j < nI; j++)
                    if(A[i][j] > 0)
                        sum += 2 * (A[i][j] - B[i][j]) * (-R[k][j]);
                
                L_t[i][k] = L[i][k]  - alpha * sum;
            }
        }

        //update old matrices with new values
        //update matrix L
        for(int i = 0; i < nF; i++)
            for(int j = 0; j < nI; j++)
                R[i][j] = R_t[i][j];
        
        //update matrix R
        for(int i = 0; i < nU; i++)
            for(int j = 0; j < nF; j++)
                L[i][j] = L_t[i][j];

        mtrz_multiply(nU, nF, L, nF, nI, R, B);
    }


    //recomend
    for(int i = 0; i < nU; i ++){
        double speculated_rating = 0.0;
        int recomendation_item = 0;
        for(int j = 0; j < nI; j++){
            if(A[i][j] == 0 && speculated_rating < B[i][j]){
                speculated_rating = B[i][j];
                recomendation_item = j;
            }
        }
        printf("%d\n", recomendation_item);
    }

    return 0;
}