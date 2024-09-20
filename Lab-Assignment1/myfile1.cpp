#include <iostream>
#include <iomanip>

using namespace std;

int main(){

    /**
     * first portion
     * print the different data types and their respective sizes
    **/
    cout << "\nSize in bytes of a character: " << sizeof(char) << endl;
    cout << "Size in bytes of a Integer: " << sizeof(int) << endl;
    cout << "Size in bytes of a float: " << sizeof(float) << endl;
    cout << "Size in bytes of a double: " << sizeof(double) << endl;
    cout << "Size in bytes of a short Integer: " << sizeof(short int) << endl;
    cout << "Size in bytes of an unsigned integer: " << sizeof(unsigned int)  << "\n" << endl;

    //second portion
    int userInput;
    cout  << "Enter an integer: ";
    cin  >> userInput;
    
    //print results:
    cout << "\nnumber in decimal \t" << std::dec << userInput << endl;
    cout << "number in octal   \t" << std::oct << userInput << endl;
    cout << "number in hexa    \t" << std::hex << userInput << "\n" << endl;
    
    
    //the above code can be accomplished through usage of the printf() function...
    printf("number in decimal\t%d\n", userInput); //indicate decimal formatting with %d
    printf("number in octal  \t%o\n", userInput); //indicate octal formatting with %o
    printf("number in hexa   \t%x\n", userInput); //indicate hexadecimal formatting with %x
    
    //Third portion of exercise 3
    double userInputRealNumber;
    cout  << "\nEnter a real number: ";
    cin  >> userInputRealNumber;

    cout << fixed << setprecision(3);
    cout << userInputRealNumber << endl;

    //cout << hexfloat << setprecision(13);
    //cout << userInputRealNumber << endl;
    printf("%.3a\n", userInputRealNumber); //how to add 0s?


    //3rd part:
    char userInputChar;
    cout << "\nEnter a character: ";
    cin >> userInputChar;

    cout << userInputChar << endl;
    cout << (int)userInputChar << endl;

    return 0;
}