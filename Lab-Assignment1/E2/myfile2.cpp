#include <iostream>
#include "./myfile2.h"

using namespace std;

int surface(double const& ray){
    //based on A= Pi*r^2
    float area = Pi * (ray * ray);
    cout << "The surface is: " << area << endl;
    return 1;
}

int volume(double const& ray, double const& height){
    //based on V = h*Pi*r^2
    float vol = height * (Pi * (ray * ray));
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
