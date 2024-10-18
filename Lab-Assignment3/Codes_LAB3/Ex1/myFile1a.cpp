/*Ex1a - a3 CSI2372A*/

#include <iostream>
using namespace std;

enum Color { club, diamond, spades, heart };
enum Face { seven, eight, nine, ten, jack, queen, king, ace };

struct Card{
	Color color;
	Face face;
};

void display(Card * deckPointer){
	for(int i = 0; i < 32; i++){
		cout <<"card number " << i << " -> Color: " <<  deckPointer[i].color << ", Face: " << deckPointer[i].face << endl;
	};
};

int main(){
	Card game[32];
	//YOUR CODE HERE

	/*
	Some assumptions:
		Card deck composition:
			#color (4) x #Face (8) = 32 total cards
			- We therefore would have each the full set of Face in each of the Color. 
	 */

	int indx = 0;
	for (int colorIndex = club; colorIndex <= heart; colorIndex++){
		for(int faceIndex = seven; faceIndex <= ace; faceIndex++){
			game[indx].color = static_cast<Color>(colorIndex);
			game[indx].face = static_cast<Face>(faceIndex);
			indx++; //increment to move on to the next card in deck
		};
	};
	display(game);
	

}

