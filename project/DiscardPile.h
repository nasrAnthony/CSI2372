#ifndef DISCARDPILE_H
#define DISCARDPILE_H

#include <iostream>
#include <vector>
#include "CardFactory.h"
#include "Card.h"

class DiscardPile {
    std::vector<Card*> pile; // Use composition instead of inheritance

public:
    DiscardPile() = default; // Default constructor
    DiscardPile(std::istream& in, const CardFactory* factory);
    DiscardPile& operator+=(Card* c); // Add a card to the pile
    Card* pickUp();                   // Show and remove the top card
    Card* top() const;                // Show only the top card
    void print(std::ostream& out) const;
    friend std::ostream& operator<<(std::ostream& out, const DiscardPile& discPile);
};

#endif // DISCARDPILE_H
