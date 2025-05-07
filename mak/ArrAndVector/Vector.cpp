#include "Array.h"
//#include "Array.cpp"

using namespace std;

class Vector : public Array {
public:
	Vector(int m) : Array(m) {}

	Vector(Vector& v) {
		init(v.p, v.row, 1);
	}

	double& operator() (int i) {
		assert(i >= 1 && i <= size);
		return p[i - 1];
	}

	Vector& operator=(Vector& v) {
		//int i; p. 112
		if (this == &v) return *this;
		delete[] p;

		init(v.p, v.row, 1);

		return *this;
	}

	void Show() {
		cout << "Vector values: " << endl;
		for (int i = 0; i < size; ++i) cout << p[i] << endl;
	}

	friend double MAXVAL(Vector &v) {
		auto max = v(1);
		for (int i = 1; i <= v.size; ++i) max = fmax(max, v(i));

		return max;
	}

private:
	int row = 0;
};




