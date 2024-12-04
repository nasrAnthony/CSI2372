#include "Deck.h"
#include "CardFactory.h"



Deck::Deck(const vector<Card*>& cards) : vector<Card*>(cards) {}

ostream& operator<<(ostream& out, Deck& deck) {
    for (size_t i = 0; i < deck.size(); i++) {
        out << deck[i]->getName() << " ";
    }
    return out;
}

Deck::Deck(istream& in, const CardFactory* factory) {
    string cardType;
    while (in >> cardType) {
        Card* card = factory->createCard(cardType);
        push_back(card);
    }
}

Card* Deck::draw() {
    if (empty()) return nullptr;
    Card* drawnCard = back(); // Draw card
    pop_back();               // Remove it
    return drawnCard;
}
