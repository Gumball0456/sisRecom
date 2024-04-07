#include "matriz_utils.h"
#include <stdio.h>
#include <stdlib.h>

void mtrz_multiply(int row1, int col1, double m1[][col1], int row2, int col2, double m2[][col2], double m3[ ][col2]){
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            m3[i][j] = 0.0;
        }
    }

    for (int i = 0; i < row1; i++){
        for (int j = 0; j < col2; j++){
            for(int k = 0; k < col1; k++)
                m3[i][j] += m1[i][k] * m2[k][j];
        }
    }
}

void mtrz_copy(int n_rws, int n_cls, double dest[][n_cls], double orig[][n_cls]){
    for(int i = 0; i < n_rws; i++){
        for(int j = 0; j < n_cls; j++)
            dest[i][j] = orig[i][j];
    }
};

void mtrz_print(int row, int column, double m[][column]){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            printf("%lf ", m[i][j]);
        }
        putchar('\n');
    }
};