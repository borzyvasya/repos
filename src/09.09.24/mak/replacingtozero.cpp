#include <cstdlib>
#include <iostream>
#include <istream>


using namespace std;

float maxfloat(float&, float&);


int main() {
    float a, b;
    cin>>a>>b;
    maxfloat(a, b);
    
    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;

    return EXIT_SUCCESS;
}

float maxfloat(float& a, float& b) {
    return (a > b) ? b = 0 : a = 0; 
}                                   
