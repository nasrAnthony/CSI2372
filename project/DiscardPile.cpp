#include "DiscardPile.h"

DiscardPile::DiscardPile(std::istream& in, const CardFactory* factory) {
    std::string cardType;
    while (in >> cardType) {
        if(cardType == "DiscardPile:"){
            continue;
        }
        if(cardType == "."){
            break;
        }
        Card* card = factory->createCard(cardType);
        pile.push_back(card); // Use the composed vector
    }
}

DiscardPile& DiscardPile::operator+=(Card* c) {
    pile.push_back(c); // Use the composed vector
    return *this;
}

Card* DiscardPile::pickUp() {
    if (pile.empty()) {
        return nullptr;
    } else {
        Card* topCard = pile.back();
        pile.pop_back();
        return topCard;
    }
}

Card* DiscardPile::top() const {
    if (pile.empty()) {
        return nullptr;
    } else {
        return pile.back();
    }
}

void DiscardPile::print(std::ostream& out) const {
    out << "DiscardPile: ";
    for (Card* c : pile) {
        if(c!=nullptr){
            c->print(out);
            out << " ";
        }
    }
    out << ".";
}

std::ostream& operator<<(std::ostream& out, const DiscardPile& discPile) {
    out << "DiscardPile: ";
    if (!discPile.pile.empty()) {
        Card* topCard = discPile.pile.back();
        out << topCard->getName();
    }
    return out;
}
