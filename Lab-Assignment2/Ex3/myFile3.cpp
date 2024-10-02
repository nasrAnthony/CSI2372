/*myFile3.cpp : Ex3 a2 CSI2372A*/

#include <iostream>
using namespace std;

int** triangleInf(int n)
{
	//YOUR CODE
	int** p2p = new int*[n]; //create an array of pointers that will each point to a row of the triangle. 
							 //new is used here since n is only determined on run time. So put the array on the heap. 
	for(int i = 0; i < n; i++){
		p2p[i] = new int[i + 1]; //make space -> row 1 has 1 element, row 2 has 2 elements, row 3 has 3 elements, etc...
		for(int j = 0; j <= i; j++){
			if(j == 0 || j == i){ //edges of triangle should be 1 automatically
				p2p[i][j] = 1;
			}
			else {
				p2p[i][j] = p2p[i - 1][j - 1] + p2p[i - 1][j]; //formula given in lab manual...
			}
		}
	}
	return p2p;
}

int main() {
	int** tab;
	const int size = 10;
	tab = triangleInf(size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j <= i; j++)
			cout << tab[i][j] << " ";
		cout << endl;
	}
}