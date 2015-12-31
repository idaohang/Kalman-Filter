/*
 * kalman-Filter.c
 *
 * Created: 28.12.2015 19.19.44
 * Author : AndreasBell
 */ 

#include <avr/io.h>
#include "Kalman Filter.h"


int main(void)
{
    /* Replace with your application code */
	
	//Example setup with return values of estimate X
	//See details in PDF solution_exam_2013.pdf (problem 4)
	setup();
	compute(0.5);	//X = [0.35, 0.1]^T
	compute(1.0);	//X = [0.8429, 0.4143]^T
	compute(1.3);	//X = [1.2982, 0.4530]^T
	
    while (1) 
    {
    }
}

