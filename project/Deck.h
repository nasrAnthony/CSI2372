#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <vector>
#include "Card.h"

class CardFactory;

using namespace std;

class Deck : public vector<Card*> {
public:
    Deck() = default;                                
    Deck(istream& in, const CardFactory* factory);     
    Card* draw();                                     
    friend ostream& operator<<(ostream& out, Deck& deck); 
};

#endif // DECK_H
