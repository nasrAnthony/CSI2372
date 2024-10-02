/*code*/
#include <iostream>
using namespace std;
int main(void) {


    //4
    //1
    //1
    //1
    //1
    //1

    int tab[10];
    int* p;
    for (int i = 0;i < 10;i++) {
        tab[i] = i * i;
    }
    cout << tab[2] << endl; //4
    tab[2] = tab[1];
    cout << tab[2] << endl; //1
    tab[2] = *(tab + 1);
    cout << tab[2] << endl; //1
    *(tab + 2) = tab[1];
    cout << tab[2] << endl; //1
    *(tab + 2) = *(tab + 1);
    cout << tab[2] << endl; //1
    p = &tab[0];
    p = tab + 1;
    tab[4] = *p;
    cout << tab[4] << endl; //1 
}
