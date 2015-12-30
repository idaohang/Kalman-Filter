/*
 * Kalman_Filter.c
 *
 * Created: 30.12.2015 23.14.56
 *  Author: AndreasBell
 */ 

#include "Matrix.h"
#include "Kalman Filter.h"

/*
//State
double x[] = { 0.2, 0.1 };
Matrix X_(2, 1, x);	//a priori
Matrix X;	//a posteriori

//Measurement
double y[] = { 0.5 };
Matrix Y(1, 1, y);

//model
double f[] = { 1, 1, 0, 1 };
Matrix F(2, 2, f);
Matrix G(2,1);
double h[] = { 1, 0 };
Matrix H(1, 2, h);

//Covarians matrix
double p[] = { 0.2, 0, 0, 0.4 };
Matrix P_(2, 2, p);	//a priori
Matrix P;	//a posteriori

//Kalman gain
Matrix K;

//Variance
double r[] = { 0.2 };
Matrix R(1, 1, r);	//Measurement noise
double q[] = { 0, 0, 0, 4 };
Matrix Q(2, 2, q);	//Process noise

//Other
double i[] = { 1, 0, 0, 1 };
Matrix I(2, 2, i);




void compute(double y){
	Y.setElm(0, 0, y);

	//Compute Kalman Gain
	K = P_ * H.T() * (H * P_ * H.T() + R).I();
	//cout << K << endl;

	//Update Estimate
	X = X_ + K*(Y - H * X_);
	cout << X << endl;

	//Compute error covariance
	P = (I - K * H) * P_;

	//Project ahead
	X_ = F*X;
	P_ = F * P * F.T() + Q;
	//cout << X_ << endl;
	//cout << P_ << endl;
}
*/