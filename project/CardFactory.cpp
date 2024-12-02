#include "CardFactory.h"

CardFactory* CardFactory::factory = nullptr; // Initialize static member

CardFactory::CardFactory() {
    for (int i = 0; i < 20; i++) {
        deck.push_back(new Blue());
    }
    for (int i = 0; i < 18; i++) {
        deck.push_back(new Chili());
    }
    for (int i = 0; i < 16; i++) {
        deck.push_back(new Stink());
    }
    for (int i = 0; i < 14; i++) {
        deck.push_back(new Green());
    }
    for (int i = 0; i < 12; i++) {
        deck.push_back(new soy());
    }
    for (int i = 0; i < 10; i++) {
        deck.push_back(new black());
    }
    for (int i = 0; i < 8; i++) {
        deck.push_back(new Red());
    }
    for (int i = 0; i < 6; i++) {
        deck.push_back(new garden());
    }
    // Shuffle
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(deck.begin(), deck.end(), default_random_engine(seed));
}

Deck CardFactory::getDeck() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // Shuffle before returning
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
    return deck;
}

Card* CardFactory::createCard(const string& type) const {
    if (type == "Blue") return new Blue();
    else if (type == "Chili") return new Chili();
    else if (type == "Stink") return new Stink();
    else if (type == "Green") return new Green();
    else if (type == "Soy") return new soy();
    else if (type == "Black") return new black();
    else if (type == "Red") return new Red();
    else if (type == "Garden") return new garden();
    else return nullptr; // Handle unrecognized types
}

CardFactory* CardFactory::getFactory() {
    if (factory == nullptr) { // Initialize if null (first time running)
        factory = new CardFactory();
    }
    return factory;
}
