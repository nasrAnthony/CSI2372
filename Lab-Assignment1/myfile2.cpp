#include <iostream>
using namespace std;

const long pi = 3.14159265;

int surface(double radius){
    //based on A= pi*r^2
    float area = pi * (radius * radius);
    cout << "The surface is: " << area << endl;
    return 1;
}


int volume(double radius, double height){
    //based on V = h*pi*r^2
    float vol = height * (pi * (radius * radius));
    cout << "The volume is: " << vol << endl;
    return 1;
}

char menu(void) {
    char choice;
    cout << "What do you want to do?:" << endl << endl;
    cout << "\t-Calculate the area of a disk from a radius (Press 1)" << endl
    << endl;
    cout << "\t-Calculate the volume of a cylinder from a radius and a height (Press 2)" << endl << endl;
    cout << "\t-Exit the program (press 3)" << endl << endl;
    cout << "Your choice:";
    cin >> choice;
    return (choice);
    cout << endl;
}
/*main Function*/
int main() {
    char choice;
    int nvolume = 0; //number of times the volume function has been executed
    int nsurface = 0; // number of times the surface function has been executed
    double radius, height;
    while (1)
    {
        choice = menu();
        switch (choice)
            {
            case '1': cout << endl << "Surface calculation" << endl;
                cout << "Enter the radius:";
                cin >> radius;
                nsurface += surface(radius);
                break;
            case '2': cout << endl << "Volume calculation" << endl;
                cout << " Enter the radius:";
                cin >> radius;
                cout << " Enter the height:";
                cin >> height;
                nvolume += volume(radius, height);
                break;
            case '3': cout << endl << "Exit the program" << endl;
                cout << "The volume function has been executed " << nvolume <<
                "times" << endl;
                cout << "The surface function has been executed " << nsurface
                << "times" << endl;
                exit(0);
                default: break;
        }
    }
}
