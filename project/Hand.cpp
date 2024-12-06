#include "Hand.h"
#include <sstream>

// Constructor to build Hand from a stream
Hand::Hand(istream& in, const CardFactory* factory) {
    string cardType;
    
    while (in >> cardType) {
        if(cardType == "Hand:"){
            continue;
        }
        else if(cardType == "."){
            break;
            
        }
        else{
            Card* card = factory->createCard(cardType);
            cardsInHand.push_back(card); // Add to deque
        }
    }
}

// Add a card to the Hand
Hand& Hand::operator+=(Card* newCard) {
    cardsInHand.push_back(newCard); // Add card to the back
    return *this;
}

// Play the top card
Card* Hand::play() {
    if (cardsInHand.empty()) return nullptr;
    Card* temp = cardsInHand.front(); // Get the front card
    cardsInHand.pop_front();          // Remove it
    return temp;
}

// Show the top card without removing it
Card* Hand::top() const {
    if (cardsInHand.empty()) return nullptr;
    return cardsInHand.front(); // Return the front card
}

// Access a card by index
Card* Hand::operator[](int index) {
    if (index >= 0 && index < static_cast<int>(cardsInHand.size())) {
        return cardsInHand[index]; // Random access
    }
    return nullptr; // Index out of bounds
}


void Hand::print(ostream& out){
    out << "Your Hand: ";
    for (auto* card : cardsInHand){
        out << card->getName() << " ";
    }
    out << "\n";
}
// Output the hand to an ostream
ostream& operator<<(ostream& out, const Hand& h) {
    out << "Hand: ";
    for (auto* card : h.cardsInHand) {
        card->print(out);
        out << " ";
    }
    out << " . ";
    return out;
}
