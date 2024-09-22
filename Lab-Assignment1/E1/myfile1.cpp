#include <iostream>
#include <iomanip>
#include "myfile1.h"

using namespace std;

void variableInfo(){
    cout << "\nSize in bytes of a character: " << sizeof(char) << endl;
    cout << "Size in bytes of a Integer: " << sizeof(int) << endl;
    cout << "Size in bytes of a float: " << sizeof(float) << endl;
    cout << "Size in bytes of a double: " << sizeof(double) << endl;
    cout << "Size in bytes of a short Integer: " << sizeof(short int) << endl;
    cout << "Size in bytes of an unsigned integer: " << sizeof(unsigned int)  << "\n" << endl;
}

void convertInteger(int num){
    //print results:
    cout << "\nnumber in decimal \t" << std::dec << num << endl;
    cout << "number in octal   \t" << std::oct << num << endl;
    cout << "number in hexa    \t" << std::hex << num << "\n" << endl;
}

void convertInteger2ndMethod(int num){
    //the above code can be accomplished through usage of the printf() function...
    printf("number in decimal\t%d\n", num); //indicate decimal formatting with %d
    printf("number in octal  \t%o\n", num); //indicate octal formatting with %o
    printf("number in hexa   \t%x\n", num); //indicate hexadecimal formatting with %x
}

void convertRealNumber(double realNum){
    cout << fixed << setprecision(3);
    cout << realNum << endl;
    //cout << hexfloat << setprecision(13);
    //cout << userInputRealNumber << endl;
    printf("%.3a\n", realNum); //how to add 0s?
}

void convertHex(char inputChar){
    cout << inputChar << endl;
    cout << (int)inputChar << endl;
}

int main(){

    /**
     * first portion
     * print the different data types and their respective sizes
    **/
    variableInfo();

    //second portion
    int userInput;
    cout  << "Enter an integer: ";
    cin  >> userInput;

    convertInteger(userInput);

    //the above code can be accomplished through usage of the printf() function...
    convertInteger2ndMethod(userInput);
    
    //Third portion of exercise 3
    double userInputRealNumber;
    cout  << "\nEnter a real number: ";
    cin  >> userInputRealNumber;

    convertRealNumber(userInputRealNumber);

    //3rd part:
    char userInputChar;
    cout << "\nEnter a character: ";
    cin >> userInputChar;

    convertHex(userInputChar);

    return 0;
}