#include "CardFactory.h"

CardFactory* CardFactory::factory = nullptr; // Initialize static member

CardFactory::CardFactory() {
    for (int i = 0; i < 20; i++) {
        cards.push_back(new Blue());
    }
    for (int i = 0; i < 18; i++) {
        cards.push_back(new Chili());
    }
    for (int i = 0; i < 16; i++) {
        cards.push_back(new Stink());
    }
    for (int i = 0; i < 14; i++) {
        cards.push_back(new Green());
    }
    for (int i = 0; i < 12; i++) {
        cards.push_back(new soy());
    }
    for (int i = 0; i < 10; i++) {
        cards.push_back(new black());
    }
    for (int i = 0; i < 8; i++) {
        deck.push_back(new Red());
    }
    for (int i = 0; i < 6; i++) {
        cards.push_back(new garden());
    }
}

Deck CardFactory::getDeck() const {
    Deck deck(cards);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // Shuffle before returning
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
    return deck;
}

Card* CardFactory::createCard(const string& type) const {
    if (type == "Blue" || type == "blue" || type == "B") return new Blue();
    else if (type == "Chili" || type == "chili" || type == "C") return new Chili();
    else if (type == "Stink"|| type == "stink" || type == "S") return new Stink();
    else if (type == "Green"|| type == "green" || type == "G") return new Green();
    else if (type == "Soy" || type == "soy" || type == "s") return new soy();
    else if (type == "Black"|| type == "black" || type == "b") return new black();
    else if (type == "Red"|| type == "red" || type == "R") return new Red();
    else if (type == "Garden"|| type == "garden" || type == "g") return new garden();
    else return nullptr; // Handle unrecognized types
}

CardFactory* CardFactory::getFactory() {
    if (factory == nullptr) { // Initialize if null (first time running)
        factory = new CardFactory();
    }
    return factory;
}
