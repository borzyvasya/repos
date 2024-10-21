#include <cstdlib>
#include <iostream>

using namespace std;

const char* dayName(int n);
const char* monthName(int n);

int main() {
    int dayNumber, monthNumber;
    
    cout<<"Input number of day: "; 
    cin>>dayNumber; 
    cout<<dayName(dayNumber)<<endl;


    cout<<"Input number of month: ";
    cin>>monthNumber;
    cout<<monthName(monthNumber)<<endl; 
    
    
    return EXIT_SUCCESS;
}

const char* dayName(int n) {
    const char* day[] = {
        "No such day",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
        "Sunday"
    };
    
    return (n<1||n>7) ? day[0] : day[n];
}

const char* monthName(int n) {
    const char* month[] = {
        "No such month",
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };
    
    return (n<1||n>12) ? month[0] : month[n];
}