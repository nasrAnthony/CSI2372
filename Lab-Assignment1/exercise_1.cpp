#include <iostream>
#include <iomanip>

using namespace std;

int main(){

    /**
     * first portion
     * print the different data types and their respective sizes
    **/
    cout << "Size in bytes of a character: " << sizeof(char) << endl;
    cout << "Size in bytes of a Integer: " << sizeof(int) << endl;
    cout << "Size in bytes of a float: " << sizeof(float) << endl;
    cout << "Size in bytes of a double: " << sizeof(double) << endl;
    cout << "Size in bytes of a short Integer: " << sizeof(short int) << endl;
    cout << "Size in bytes of an unsigned integer:" << sizeof(unsigned int) << endl;

    return 0;
}