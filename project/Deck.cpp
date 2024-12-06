#include "Deck.h"
#include "CardFactory.h"



Deck::Deck(const vector<Card*>& cards) : vector<Card*>(cards) {}

ostream& operator<<(ostream& out, Deck& deck) {
    out << "Deck: ";
    for (size_t i = 0; i < deck.size(); i++) {
        if(deck[i] != nullptr){
            out << deck[i]->getName() << " ";
        }
    }
    out << ".";
    return out;
}

Deck::Deck(istream& in, const CardFactory* factory) {
    string cardType;
    while (in >> cardType) {
        if(cardType == "Deck:"){
            continue;
        }
        if(cardType == "."){
            break;
        }
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
