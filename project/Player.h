#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <exception>
#include <vector>
#include "Card.h"
#include "Chain_Base.h"
#include "Chain.h"
#include "Hand.h"
#include "CardFactory.h"

using namespace std;

class Player {
    string playerName;
    int playerNumCoins;
    Hand playerHand;
    vector<Chain_Base*> chains; // Max 3 chains per player
    bool playerMaxChainFlag;

public:
    Player() : playerName(""), playerNumCoins(0), playerMaxChainFlag(false) {} // Default constructor
    Player(string& name) : playerName(name), playerNumCoins(0), playerMaxChainFlag(false) {
        chains.resize(2, nullptr);
    }
    Player(istream& in, const CardFactory* factory);
    ~Player(); // Destructor to clean up chains
    string getName() const;
    Hand& getHand(){ return playerHand;}
    vector<Chain_Base*>& getChains() { return chains; }
    int getNumCoins() const;
    Player& operator+=(int num); // Add coins
    int getMaxNumChains() const;
    int getNumChains() const;
    Chain_Base& operator[](int index);
    void buyThirdChain();
    void printHand(ostream& out, bool verbose);
    Hand& getPlayerHand() { return playerHand; } // Getter for private member playerHand
    // Added function declarations
    void addChain(Chain_Base* newChain);
    void removeChain(int index);
    friend ostream& operator<<(ostream& out, Player& p);
};

#endif // PLAYER_H
