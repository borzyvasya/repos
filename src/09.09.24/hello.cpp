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


    return EXIT_SUCCESS;
}

void findRoots(float a, float b, float c) {
    float d, x1, x2;
    
    d = (b*b) - (4*a*c);
    if (d < 0) {
        cout<<"no solution"<<endl;
    } 

    else if (d == 0) {
        x1 = (-b)/(2*a);
        cout<<"only one x = "<<x1<<endl;
    } 

    else {
        x1 = (-b+sqrt(d))/(2*a); 
        x2 = (-b-sqrt(d))/(2*a); 

        cout<<"x1 = "<<x1<<", "<<"x2 = "<<x2<<endl;
    }
    
}
