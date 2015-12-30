/*
 * Matrix.h
 *
 * Created: 28.12.2015 19.23.07
 *  Author: AndreasBell
 */ 


#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdint.h>

typedef struct{
	uint8_t row;
	uint8_t col;
	double** data;
} Matrix;


void mallocMatrix(Matrix* m, uint8_t row, uint8_t col); //Allocate memory
void resizeMatrix(Matrix* m, uint8_t row, uint8_t col); //Resize
void freeMatrix(Matrix* m); //Free memory
Matrix copy(Matrix* rhs); //Copy all data

/*Matrix operators*/
Matrix* adde(Matrix* lhs, Matrix* rhs); //operator +=
Matrix* sube(Matrix* lhs, Matrix* rhs); //operator -=
Matrix add(Matrix* lhs, Matrix* rhs); //operator +
Matrix sub(Matrix* lhs, Matrix* rhs); //operator -
Matrix mul(Matrix* lhs, Matrix* rhs); //operator *
Matrix* mule(Matrix* lhs, Matrix* rhs); //operator *=
Matrix* scale(Matrix* lhs, double rhs); //operator Matrix *= (double)

double det(Matrix* m); //Determinant
Matrix T(Matrix* m); //Transpose
Matrix I(Matrix* m); //Inverse


/*Help functions*/
double Determinant(double **a, uint8_t n);
void CoFactor(double **a, uint8_t n, double **b); //Find the cofactor matrix of a square matrix
void TSquare(double **a, uint8_t n); ////Transpose of a square matrix, in place
void TAny(double ***matrix, uint8_t row, uint8_t col); //Transpose of a none square matrix

#endif /* MATRIX_H_ */