/*
 * Matrix.c
 *
 * Created: 28.12.2015 19.22.40
 *  Author: AndreasBell
 */ 


#include "Matrix.h"

void mallocMatrix(Matrix& m, uint8_t row, uint8_t col){
	m.row = row;
	m.col = col;
	
	m.data = (double**) malloc(m.row * sizeof(double*));
	for (uint8_t r = 0; r < m.row; r++){
		m.data[r] = (double*) malloc(m.col * sizeof(double));
	}
}

void freeMatrix(Matrix& m){
	for (uint8_t r = 0; r < m.row; r++){
		free(m.data[r]);
	}
	free(m.data);
	m.data
}

void resizeMatrix(Matrix& m, uint8_t row, uint8_t col){
	if(m.col != col && m.row != row){
		freeMatrix(m);
		mallocMatrix(m, row, col);
	}
}

Matrix copy(Matrix& rhs){
	Matrix temp;
	mallocMatrix(temp, rhs.row, rhs.col);
	for(uint8_t r = 0; r < temp.row; r++){
		for (uint8_t c = 0; c < temp.col; c++){
			temp.data[r][c] = rhs.data[r][c];
		}
	}
	return temp;
}

Matrix& adde(Matrix& lhs, Matrix& rhs){
	if (lhs.row == rhs.row && lhs.col == rhs.col){
		for (int r = 0; r < lhs.row; r++){
			for (int c = 0; c < lhs.col; c++){
				lhs.data[r][c] += rhs.data[r][c];
			}
		}
	}
	return lhs;
}

Matrix& sube(Matrix& lhs, Matrix& rhs){
	if (lhs.row == rhs.row && lhs.col == rhs.col){
		for (int r = 0; r < lhs.row; r++){
			for (int c = 0; c < lhs.col; c++){
				lhs.data[r][c] -= rhs.data[r][c];
			}
		}
	}
	return lhs;
}

Matrix add(Matrix& lhs, Matrix& rhs){
	Matrix temp = copy(lhs);
	return adde(temp, rhs);
}

Matrix sub(Matrix& lhs, Matrix& rhs){
	Matrix temp = copy(lhs);
	return sube(temp, rhs);
}

Matrix mul(Matrix& lhs, Matrix& rhs){
	Matrix returnMatrix;
	if(lhs.col == rhs.row){
		mallocMatrix(returnMatrix, lhs.row, rhs.col);
		for (uint8_t i = 0; i < lhs.row; i++){
			for (uint8_t j = 0; j < rhs.col; j++){
				double temp = 0;
				for (int k = 0; k < lhs.col; k++){
					temp += lhs.data[i][k] * rhs.data[k][j];
				}
				returnMatrix.data[i][j] = temp;
			}
		}
	}
	else{
		mallocMatrix(returnMatrix, 0, 0);
	}
	return returnMatrix;
}

Matrix& mule(Matrix& lhs, Matrix& rhs){
	Matrix temp = lhs;
	lhs = mul(lhs, rhs);
	freeMatrix(temp);
	return lhs;
}

Matrix& scale(Matrix& lhs, double rhs){
	for (uint8_t r = 0; r < lhs.row; r++){
		for (uint8_t c = 0; c < lhs.col; c++){
			lhs.data[r][c] *= rhs;
		}
	}
	return lhs;
}

double det(Matrix& m){
	if (m.col == m.row){
		return Determinant(m.data, m.row);
	}
	return 0;
}

Matrix T(Matrix& m){
	Matrix temp;
	temp.row = 0;
	temp.col = 0;
	copy(temp, m);
	if (temp.row == temp.col){
		Transpose(temp.data, temp.row);
	}

	else{
		Transpose(&temp.data, temp.row, temp.col);
		//Swap column and row size;
		uint8_t t = temp.row;
		temp.row = temp.col;
		temp.col = t;
	}

	return temp;
}

Matrix I(Matrix& m){
	Matrix temp;
	if (m.col == 1 && m.row == 1){
		temp = copy(m);
		temp.data[0][0] = 1.0 / m.data[0][0];
	}
	else if (m.row == m.col){
		mallocMatrix(temp, m.row, m.col);
		CoFactor(m.data, m.row, temp.data);
		Transpose(temp.data temp.row);
		scale(temp, det(m));
	}
	else{ /* Not square matrix */
		mallocMatrix(temp, 0, 0);
	}
	return temp;
}


//find determinant
double Determinant(double **a, uint8_t n){
	if (n == 1){
		return a[0][0];
	}
	uint8_t i, j, j1, j2;
	double det = 0;
	double **m = NULL;

	if (n < 1) { /* Error */
		continue;
	}
	
	else if (n == 1) { /* Shouldn't get used */
		det = a[0][0];
	}
	
	else if (n == 2) {
		det = a[0][0] * a[1][1] - a[1][0] * a[0][1];
	}
	
	else {
		det = 0;
		for (j1 = 0; j1<n; j1++) {
			m = (double**) malloc((n-1) * sizeof(double*))
			for (i = 0; i < n - 1; i++){
				m[i] = (double*) malloc((n - 1) * sizeof(double))
			}
			for (i = 1; i<n; i++) {
				j2 = 0;
				for (j = 0; j<n; j++) {
					if (j == j1){
						continue;
					}
					m[i - 1][j2] = a[i][j];
					j2++;
				}
			}
			
			if(j1 % 2){
				det -= a[0][j1] * Determinant(m, n - 1);
			}
			else{
				det += a[0][j1] * Determinant(m, n - 1);
			}
			
			for (i = 0; i<n - 1; i++){
				free(m[i]);
			}
			free(m);
		}
	}
	return(det);
}


//Find the cofactor matrix of a square matrix
void CoFactor(double **a, uint8_t n, double **b){
	uint8_t i, j, ii, jj, i1, j1;
	double det;
	double **c;

	c = (double**) malloc((n-1) * sizeof(double*));
	for (i = 0; i<n - 1; i++){
		c[i] = (double*) malloc((n-1) * sizeof(double));
	}

	for (j = 0; j < n; j++) {
		for (i = 0; i < n; i++) {
			//Form the adjoint a_ij
			i1 = 0;
			for (ii = 0; ii < n; ii++) {
				if (ii == i){
					continue;
				}
				j1 = 0;
				for (jj = 0; jj < n; jj++) {
					if (jj == j){
						continue;
					}
					c[i1][j1] = a[ii][jj];
					j1++;
				}
				i1++;
			}

			//Calculate the determinate
			det = Determinant(c, n - 1);

			//Fill in the elements of the cofactor
			if((i + j) % 2){
				b[i][j] = -det;
			}
			else{
				b[i][j] = det;
			}
		}
	}
	for (i = 0; i<n - 1; i++){
		free(c[i]);
	}
	free(c);
}


//Transpose of a square matrix, in place
void Transpose(double **a, uint8_t n){
	uint8_t i, j;
	double tmp;

	for (i = 1; i < n; i++) {
		for (j = 0; j < i; j++) {
			tmp = a[i][j];
			a[i][j] = a[j][i];
			a[j][i] = tmp;
		}
	}
}

//Transpose of a none square matrix
void Transpose(double ***matrix, uint8_t row, uint8_t col){
	// dynamically allocate an array
	double **result;
	result = (double**) malloc(col * sizeof(double*)); //creates a new array of pointers to int objects
	for (uint8_t i = 0; i < col; i++){
		result[i] = (double*) malloc(row * sizeof(double));
	}

	// transposing
	for (uint8_t i = 0; i < row; i++){
		for (uint8_t j = 0; j < col; j++){
			result[j][i] = matrix[0][i][j];
		}
	}

	// swap pointers
	double** temp = *matrix;
	*matrix = result;


	// clean up
	for (uint8_t i = 0; i < row; i++){
		delete[] temp[i];
	}
	delete[] temp;
}
