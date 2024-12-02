#ifndef CHAIN_H
#define CHAIN_H

#include <iostream>
#include <vector>
#include <exception>
#include "Card.h"
#include "Chain_Base.h"
#include "CardFactory.h"

using namespace std;

template <class T>
class Chain : public Chain_Base {
    vector<T*> cardChain;

public:
    Chain() = default; // Default constructor
    Chain(istream& in, const CardFactory* factory); // Constructor to build chain from file when game is resumed

    Chain<T>& operator+=(Card* incomingCard) {
        if (!dynamic_cast<T*>(incomingCard)) { // Will be nullptr if they don't match
            throw std::runtime_error("IllegalType: Card type does not match chain type.");
        }
        cardChain.push_back(static_cast<T*>(incomingCard));
        return *this;
    }

    int sell();
    vector<T*> getCardChain() const { return cardChain; } // Getter for private member
    int getSize() const;                                  // Helper to access size of private member cardChain
    void print(ostream& out) const;

    string getChainType() {
        if (cardChain.empty()) return "No type (Empty Chain)";
        else return cardChain[0]->getName();
    };

    template <class U>
    friend ostream& operator<<(ostream& out, const Chain<U>& c);
};

template <class T>
int Chain<T>::getSize() const {
    return cardChain.size();
}

template <class T>
Chain<T>::Chain(istream& in, const CardFactory* factory) {
    string cardType;
    while (in >> cardType) {
        Card* card = factory->createCard(cardType);
        if (dynamic_cast<T*>(card)) {
            cardChain.push_back(static_cast<T*>(card));
        } else {
            // Stop reading when a card of different type is found
            break;
        }
    }
}

template <class T>
int Chain<T>::sell() {
    if (cardChain.size() == 0) return 0;
    int numCards = cardChain.size();
    T tempCard;
    int coins = 0;
    for (int c = 4; c >= 1; --c) {
        int cardsNeeded = tempCard.getCardsPerCoin(c);
        if (cardsNeeded == 0) continue;
        if (numCards >= cardsNeeded) {
            coins = c;
            break;
        }
    }
    return coins;
}

template <class T>
void Chain<T>::print(ostream& out) const {
    if (cardChain.empty()) {
        out << "Empty";
    } else {
        out << cardChain[0]->getName() << " ";
        for (const auto& card : cardChain) {
            card->print(out);
            out << " ";
        }
    }
}

template <class T>
ostream& operator<<(ostream& out, const Chain<T>& c) {
    c.print(out);
    return out;
}

#endif
