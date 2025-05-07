#include "Vector.cpp"

using namespace std;

int main() {
	int size = 5;

	Vector first(size), second(size), third(size);

	for (int i = 1; i <= size; ++i) first(i) = 1;
	for (int i = 1; i <= size; ++i) second(i) = 2. / i;

	first.Show(); 
	cout << endl; // для отступа
	second.Show();

	cout << endl << "Second vector max value = " << MAXVAL(second);

	return EXIT_SUCCESS;
}