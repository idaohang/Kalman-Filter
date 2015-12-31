
# Kalman Filter
This is a kalman filter for linear systems of any size compleat with a matrix library with all matrix opperations needed to compute the kalman filter equations.

Project includes both c and c++ libraries, I have mostly used the C library as this should work with most compilers and is easy to use with microcontrollers. The C library is an avr studio project and should be quite easy to implement in for example arduino projects.

To use C library in c++ it should be possible to include the files using the following code
```C
extern "C"{
	#include "Kalman Filter.h"
	#include "Matrix.h"
	Matrix X;
}
```

For testing the c in visual studio you can use the following code


```cpp
#include <iostream>
extern "C"{
	#include "Kalman Filter.h"
	#include "Matrix.h"
	Matrix X;
}

std::ostream &operator<<(std::ostream &os, const Matrix &rhs){
	for (int i = 0; i < rhs.row; i++)
	{
		for (int j = 0; j < rhs.col; j++)
		{
			os << rhs.data[i][j] << " ";
		}
		os << std::endl;
	}
	return os;
}


int main(void)
{

	setup();
	compute(0.5);
	std::cout << X << std::endl;
	compute(1.0);
	std::cout << X << std::endl;
	compute(1.3);
	std::cout << X << std::endl;
}
```
