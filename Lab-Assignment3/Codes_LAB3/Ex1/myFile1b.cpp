/*Ex1b - a3 CSI2372A*/

#include <iostream>
using namespace std;

enum Color { club, diamond, spades, heart };
enum Face { seven, eight, nine, ten, jack, queen, king, ace };

struct Card
{
	Color color;
	Face face;
};

typedef Card Hand[5];

/* testPair() function*/
bool testPair(const Hand& h)
{
	//YOUR CODE 
	bool pairNotFoundFlag = true;
	int i = 0;
	while(pairNotFoundFlag){
		for (int j= 0; j < 5; j++){
			if(i != j && (h[i].face == h[j].face)){
				pairNotFoundFlag = false;
				break;
			}
		}
		i++;
	}
	return !pairNotFoundFlag;
}


/*Example of main()*/
int main()
{
	bool testPair(const Hand&);
	Hand myHand = { {club,nine}, {diamond, eight}, {spades, ace}, {spades, jack}, {club, ace} };
	cout << "\nI have at least: " << testPair(myHand) << " pair" << endl;
	return 0;
}



