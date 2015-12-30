#pragma once
#include <iostream>

class Matrix
{
public:
	Matrix();
	explicit Matrix(unsigned int nRows);
	Matrix(unsigned int nRows, unsigned int nColumns);
	Matrix(unsigned int nRows, unsigned int nColumns, double data[]);
	~Matrix();
	double getElm(int r, int c) const;
	void setElm(int r, int c, double num);
	bool isValid() const;
	void makeInvalid();
	int rows() const;
	int columns() const;

	double det();
	Matrix T();
	Matrix I();

	Matrix& operator =(Matrix &rhs);
	Matrix(Matrix &rhs);
	Matrix& operator +=(Matrix &rhs);
	Matrix& operator -=(Matrix &rhs);
	Matrix operator +(Matrix &rhs);
	Matrix operator -(Matrix &rhs);
	Matrix operator *(Matrix &rhs);
	Matrix operator *(double rhs);
	Matrix& operator *=(Matrix &rhs);
	Matrix& operator *=(double rhs);
	

private:
	int M;
	int N;
	double **Mat = nullptr;

};

std::ostream &operator<<(std::ostream &os, const Matrix &rhs);

double Determinant(double **a, int n);
void CoFactor(double **a, int n, double **b);
void Transpose(double **a, int n);
void Transpose(double ***matrix, int row, int col);