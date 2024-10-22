#include <cstdlib>
#include <iostream>

using namespace std;

int xands(int& x, int& s) {
    return (x >= 0) ? s += x : x;
}



int main() {
    int x, y, z, s;

    cin >> x >> y >> z;

    s = 0;
    
    return EXIT_SUCCESS;
}



