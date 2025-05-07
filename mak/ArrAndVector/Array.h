#include <assert.h>
#include <iostream>
#include <cstdlib>

using namespace std;

#ifndef ARRAY_H
#define ARRAY_H

class Array {
public:
	Array();
	Array(int);
	Array(int, int);
	~Array();

	virtual void Show() = 0;

protected:
	void init(double*, int, int);
	double* p;
	int size;
	int error;
};

#endif

