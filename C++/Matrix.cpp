#include "Matrix.h"

Matrix::Matrix()
{
	this->M = 0;
	this->N = 0;
}

Matrix::Matrix(unsigned int nRows)
{
	this->Matrix::Matrix(nRows, nRows);
}

Matrix::Matrix(unsigned int nRows, unsigned int nColumns)
{
	this->Mat = new double* [nRows];
	for (int i = 0; i < nRows; i++)
	{
		this->Mat[i] = new double[nColumns];
	}
	this->M = nRows;
	this->N = nColumns;
}

Matrix::Matrix(unsigned int nRows, unsigned int nColumns, double data[])
{
	this->Matrix::Matrix(nRows, nColumns);
	for (int r = 0; r < nRows; r++){
		for (int c = 0; c < nColumns; c++){
			this->Mat[r][c] = data[r*nColumns + c];
		}
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < this->rows(); i++){
		delete[] this->Mat[i];
	}
	delete[] this->Mat;
	Mat = nullptr;
}

double Matrix::getElm(int r, int c) const
{
	return this->Mat[r][c];
}

void Matrix::setElm(int r, int c, double num)
{
	this->Mat[r][c] = num;
}

bool Matrix::isValid() const
{
	if (this->Mat == nullptr)
	{
		return false;
	}

	else
	{
		return true;
	}
}

int Matrix::rows() const
{
	return this->M;
}

int Matrix::columns() const
{
	return this->N;
}

std::ostream &operator<<(std::ostream &os, const Matrix &rhs)
{
	if (rhs.isValid())
	{
		for (int i = 0; i < rhs.rows(); i++)
		{
			for (int j = 0; j < rhs.columns(); j++)
			{
				os << rhs.getElm(i, j) << " ";
			}
			os << std::endl;
		}
	}

	else
	{
		os << "invalid";
	}
	return os;
}

Matrix& Matrix::operator=(Matrix &rhs)
{
	this->makeInvalid();
	if (rhs.isValid())
	{
		this->Matrix::Matrix(rhs.rows(), rhs.columns());
		for (int r = 0; r < this->M; r++)
		{
			for (int c = 0; c < this->N; c++)
			{
				this->setElm(r, c, rhs.getElm(r, c));
			}
		}
	}
	else
	{
		this->makeInvalid();
	}
	return *this;
}

Matrix::Matrix(Matrix &rhs)
{
	if (rhs.isValid())
	{
		this->Matrix::Matrix(rhs.rows(), rhs.columns());
		for (int r = 0; r < this->M; r++)
		{
			for (int c = 0; c < this->N; c++)
			{
				this->setElm(r, c, rhs.getElm(r, c));
			}
		}
	}
	else
	{
		this->makeInvalid();
	}
}

Matrix& Matrix::operator +=(Matrix &rhs)
{
	if (this->rows() == rhs.rows() && this->columns() == rhs.columns())
	{
		for (int r = 0; r < this->M; r++)
		{
			for (int c = 0; c < this->N; c++)
			{
				this->setElm(r, c, (this->getElm(r, c) + rhs.getElm(r, c)));
			}
		}
	}
	else
	{
		this->makeInvalid();
	}
	return *this;
}

Matrix& Matrix::operator -=(Matrix &rhs)
{
	if (this->rows() == rhs.rows() && this->columns() == rhs.columns())
	{
		for (int r = 0; r < this->M; r++)
		{
			for (int c = 0; c < this->N; c++)
			{
				this->setElm(r, c, (this->getElm(r, c) - rhs.getElm(r, c)));
			}
		}
	}
	else
	{
		this->M = 0;
		this->N = 0;
		this->Mat = nullptr;
	}
	return *this;
}

Matrix Matrix::operator +(Matrix &rhs)
{
	Matrix returnMatrix = *this;
	returnMatrix += rhs;
	return returnMatrix;
}

Matrix Matrix::operator -(Matrix &rhs)
{
	Matrix returnMatrix = *this;
	returnMatrix -= rhs;
	return returnMatrix;
}

Matrix Matrix::operator *(Matrix &rhs)
{
	Matrix returnMatrix(this->rows(), rhs.columns());
	for (int i = 0; i < this->rows(); i++)
	{
		for (int j = 0; j < rhs.columns(); j++)
		{
			double temp = 0;
			for (int k = 0; k < this->columns(); k++)
			{
				temp += (this->getElm(i, k) * rhs.getElm(k, j));
			}
			returnMatrix.setElm(i, j, temp);
		}
	}
	return returnMatrix;
}

Matrix Matrix::operator *(double rhs){
	Matrix temp = *this;
	return temp *= rhs;
}

Matrix& Matrix::operator *=(Matrix &rhs)
{
	Matrix temp(this->rows(), rhs.rows());
	temp = *this *rhs;
	*this = temp;
	return *this;
}

Matrix& Matrix::operator *=(double rhs){
	for (int r = 0; r < this->rows(); r++){
		for (int c = 0; c < this->columns(); c++){
			this->Mat[r][c] *= rhs;
		}
	}

	return *this;
}

void Matrix::makeInvalid()
{
	this->~Matrix();
}

double Matrix::det(){
	if (this->columns() == this->rows()){
		return Determinant(Mat, this->columns());
	}
	return 0;
}

//Transpose
Matrix Matrix::T(){
	Matrix temp = *this;
	if (this->rows() == this->columns()){
		Transpose(temp.Mat, temp.columns());
	}

	else{
		Transpose(&temp.Mat, temp.rows(), temp.columns());
		//Swap column and row size;
		int t = temp.M;
		temp.M = temp.N;
		temp.N = t;
	}

	return temp;
}

//inverse
Matrix Matrix::I(){
	if (this->columns() == 1){
		Matrix temp = *this;
		temp.setElm(0, 0, (1.0 / temp.getElm(0,0)));
		return temp;
	}
	else{
		Matrix temp(this->columns());
		CoFactor(this->Mat, this->columns(), temp.Mat);
		Transpose(temp.Mat, temp.columns());
		temp *= (1 / this->det());
		return temp;
	}
}

//find determinant
double Determinant(double **a, int n)
{
	if (n == 1){
		return a[0][0];
	}
	int i, j, j1, j2;
	double det = 0;
	double **m = NULL;

	if (n < 1) { /* Error */

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
			m = new double*[n - 1];
			for (i = 0; i < n - 1; i++)
				m[i] = new double[n - 1];
			for (i = 1; i<n; i++) {
				j2 = 0;
				for (j = 0; j<n; j++) {
					if (j == j1)
						continue;
					m[i - 1][j2] = a[i][j];
					j2++;
				}
			}
			det += pow(-1.0, j1 + 2.0) * a[0][j1] * Determinant(m, n - 1);
			for (i = 0; i<n - 1; i++)
				free(m[i]);
			free(m);
		}
	}
	return(det);
}


//Find the cofactor matrix of a square matrix
void CoFactor(double **a, int n, double **b)
{
	int i, j, ii, jj, i1, j1;
	double det;
	double **c;

	c = new double*[n - 1];
	for (i = 0; i<n - 1; i++)
		c[i] = new double[n - 1];

	for (j = 0; j<n; j++) {
		for (i = 0; i<n; i++) {

			//Form the adjoint a_ij
			i1 = 0;
			for (ii = 0; ii<n; ii++) {
				if (ii == i)
					continue;
				j1 = 0;
				for (jj = 0; jj<n; jj++) {
					if (jj == j)
						continue;
					c[i1][j1] = a[ii][jj];
					j1++;
				}
				i1++;
			}

			//Calculate the determinate
			det = Determinant(c, n - 1);

			//Fill in the elements of the cofactor
			b[i][j] = pow(-1.0, i + j + 2.0) * det;
		}
	}
	for (i = 0; i<n - 1; i++)
		free(c[i]);
	free(c);
}


//Transpose of a square matrix, in place
void Transpose(double **a, int n)
{
	int i, j;
	double tmp;

	for (i = 1; i<n; i++) {
		for (j = 0; j<i; j++) {
			tmp = a[i][j];
			a[i][j] = a[j][i];
			a[j][i] = tmp;
		}
	}
}

//Transpose of a none square matrix
void Transpose(double ***matrix, int row, int col)
{
	// dynamically allocate an array
	double **result;
	result = new double *[col]; //creates a new array of pointers to int objects
	for (int i = 0; i < col; i++)
		result[i] = new double[row];

	// transposing
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			result[j][i] = matrix[0][i][j];
		}
	}

	//swap pointers
	double** temp = *matrix;
	*matrix = result;


	//Clean up
	for (int i = 0; i < row; i++){
		delete[] temp[i];
	}
	delete[] temp;
}

