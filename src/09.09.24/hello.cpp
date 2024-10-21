#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

void findRoots(float, float, float);

int main() {
    float a, b, c;
    cout<<"Input a: "; cin>>a;
    cout<<"Input b: "; cin>>b;
    cout<<"Input c: "; cin>>c;
    
    
    findRoots(a, b, c);
    return 0;
}

void findRoots(float a, float b, float c) {
    float x1, x2;
    
    x1 = (-b-sqrt((b*b)-4*a*c))/2*a;
    x2 = (-b+sqrt((b*b)-4*a*c))/2*a;
    
    cout<<"x1 = "<<x1<<", "<<"x2 = "<<x2<<endl;
}
