#ifndef CARD_FACTORY_H
#define CARD_FACTORY_H

#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include "Card.h"
#include "Deck.h"

using namespace std;

class CardFactory {
private:
    Deck deck;
    static CardFactory* factory;
    CardFactory(const CardFactory&) = delete;             // Private copy constructor
    CardFactory& operator=(const CardFactory&) = delete;  // Private assignment operator
    CardFactory();

public:
    static CardFactory* getFactory();
    Deck getDeck();

    Card* createCard(const string& type) const;
};

#endif // CARD_FACTORY_H
