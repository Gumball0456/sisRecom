/*
*   matriz.h: define functions to deal with matrices
*   author: Gumball
*/

#ifndef MATRIZ_H
#define MATRIZ_H

/* Multiply two matrices m1 and m2 with sizes size1 and size2 and store the result in matriz result*/
void mtrz_multiply(int row1, int col1, double m1[row1][col1], int row2, int col2, double m2[row2][col2], double m3[row1][col2]);
void mtrz_copy(int num_rows, int num_cols, double dest[num_rows][num_cols], double orig[num_rows][num_cols]);
void mtrz_print(int row, int column, double[row][column]);

#endif