#ifndef HAND_H
#define HAND_H

#include <iostream>
#include <deque>
#include "Card.h"
#include "CardFactory.h"

using namespace std;

class Hand {
    deque<Card*> cardsInHand; // Use deque for better access and flexibility

public:
    Hand() = default; // Default constructor
    Hand(istream& in, const CardFactory* factory);
    Hand& operator+=(Card* newCard);
    Card* play();
    Card* top() const;
    Card* operator[](int index);
    int getSize() const { return cardsInHand.size(); }
    friend ostream& operator<<(ostream& out, const Hand& h);
};

#endif // HAND_H
