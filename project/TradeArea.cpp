#include "TradeArea.h"

TradeArea::TradeArea(istream& in, const CardFactory* factory) {
    string cardType;
    while (in >> cardType) {
        if(cardType == "TradeArea:"){
            continue;
        }
        if(cardType == "Empty."){
            break;
        }
        if(cardType == "."){
            break;
        }
        Card* card = factory->createCard(cardType);
        cardList.push_back(card);
    }
}

TradeArea& TradeArea::operator+=(Card* c) {
    cardList.push_back(c);
    return *this;
}

bool TradeArea::legal(Card* c) const {
    for (const auto& card : cardList) {
        if (card->getName() == c->getName()) {
            return true;
        }
    }
    return false;
}

Card* TradeArea::trade(string name) {
    for (auto it = cardList.begin(); it != cardList.end(); ++it) {
        if ((*it)->getName() == name) {
            Card* temp = *it;
            cardList.erase(it);
            return temp;
        }
    }
    return nullptr;
}

ostream& operator<<(ostream& out, const TradeArea& ta) {
    out << "TradeArea: ";
    if(ta.cardList.size() == 0){
        out << "Empty.";
        return out;
    }
    for (const auto& card : ta.cardList) {
        out << card->getName();
        out << " ";
    }
    return out;
}
