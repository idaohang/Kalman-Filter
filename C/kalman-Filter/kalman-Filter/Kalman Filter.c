/*
 * Kalman_Filter.c
 *
 * Created: 30.12.2015 23.14.56
 *  Author: AndreasBell
 */ 

#include "Matrix.h"
#include "Kalman Filter.h"


//State
Matrix X_;	//a priori
Matrix X;	//a posteriori

//Measurement
Matrix Y;

//model
Matrix F;
Matrix FT;
Matrix H;
Matrix HT;

//Covarians matrix
Matrix P_;	//a priori
Matrix P;	//a posteriori

//Kalman gain
Matrix K;


//Variance
Matrix R;	//Measurement noise
Matrix Q;	//Process noise


//Other
Matrix I2x2;
Matrix temp;


void compute(double y){
	Y.data[0][0] = y;

	//Compute Kalman Gain K = P_ * H.T() * (H * P_ * H.T() + R).I();
	freeMatrix(&temp);
	freeMatrix(&K);
	temp = mul(&H, &P_);
	adde(mule(&temp, &HT), &R);
	K = mul(&P_, &HT);
	mule(&K, Ie(&temp));
	

	//Update Estimate X = X_ + K*(Y - H * X_);
	freeMatrix(&temp);
	freeMatrix(&X);
	X = mul(&H, &X_);
	temp = sub(&Y, &temp);
	freeMatrix(&X);
	X = mul(&K, &temp);
	adde(&X, &X_);

	//Compute error covariance P = (I - K * H) * P_;
	freeMatrix(&temp);
	freeMatrix(&P);
	temp = mul(&K, &H);
	P = sub(&I2x2, &temp);
	mule(&P, &temp);

	//Project ahead X_ = F*X; P_ = F * P * F.T() + Q;
	freeMatrix(&X_);
	X_ = mul(&F, &X);
	freeMatrix(&P_);
	P_ = mul(&F, &P);
	adde(mule(&P_, &FT), &Q);
	
}

void setup(){
	mallocMatrix(&X_, 2, 1);
	X_.data[0][0] = 0.2;
	X_.data[1][0] = 0.1;
	
	mallocMatrix(&X, 2, 1);
	
	mallocMatrix(&Y, 1, 1);
	Y.data[0][0] = 0.5;
	
	mallocMatrix(&F, 2, 2);
	F.data[0][0] = 1;
	F.data[0][1] = 1;
	F.data[1][0] = 0;
	F.data[1][1] = 1;
	
	FT = T(&F);
	
	mallocMatrix(&H, 1, 2);
	H.data[0][0] = 1;
	H.data[0][1] = 0;
	
	HT = T(&H);
	
	mallocMatrix(&P_, 2, 2);
	P_.data[0][0] = 0.2;
	P_.data[0][1] = 0;
	P_.data[1][0] = 0;
	P_.data[1][1] = 0.4;
	
	mallocMatrix(&P, 2, 2);
	
	mallocMatrix(&R, 1, 1);
	R.data[0][0] = 0.2;
	
	mallocMatrix(&Q, 2, 2);
	Q.data[0][0] = 0;
	Q.data[0][1] = 0;
	Q.data[1][0] = 0;
	Q.data[1][1] = 4;
	
	mallocMatrix(&I2x2, 2, 2);
	I2x2.data[0][0] = 1;
	I2x2.data[0][1] = 0;
	I2x2.data[1][0] = 0;
	I2x2.data[1][1] = 1;
}