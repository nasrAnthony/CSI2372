#ifndef TRADEAREA_H
#define TRADEAREA_H

#include <iostream>
#include <list>
#include "Card.h"
#include "CardFactory.h"

using namespace std;

class TradeArea {
    list<Card*> cardList = {}; // Initialize empty

public:
    TradeArea() = default;
    TradeArea(istream& in, const CardFactory* factory);
    TradeArea& operator+=(Card* c);
    list<Card*>getCards() {return cardList;}
    bool legal(Card* c) const;
    Card* trade(string name);
    int numCards() const { return cardList.size(); }
    friend ostream& operator<<(ostream& out, const TradeArea& ta);
};

#endif // TRADEAREA_H
