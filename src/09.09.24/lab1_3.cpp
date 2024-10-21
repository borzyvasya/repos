#include <cstdlib>
#include <iostream>

using namespace std;

void Input(float&, float&);
void Output(float, float);
void Swap(float, float);

int main() {
    // float a, b, c;
    float a, b;
    
    long double var;
    Input(a, b);
    Output(a, b);
    Swap(a, b);
    cout<<"Size: "<<sizeof(var)<<endl;
    
    return EXIT_SUCCESS;
}

void Input(float &a, float &b) {
    cout<<"gimme a data: "<<endl;
    cin>>a>>b;    
}

void Output(float a, float b) {
    cout<<"your data is: "<<endl;
    cout<<a<<b<<endl;    
}

void Swap(float a, float b) {
    float temp = a;
    a = b;
    b = temp;
    
    cout<<a<<" "<<b<<endl;
}