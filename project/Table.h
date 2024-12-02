#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include "Player.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include "CardFactory.h"

using namespace std;

class Table {

public: 
    Player player1;
    Player player2;
    Deck deck;
    DiscardPile discardPile;
    TradeArea tradeArea;
    Table() = default;
    Table(istream& in, const CardFactory* factory);
    bool win(string& winningPlayerName);
    void printHand(bool verbose);
    friend ostream& operator<<(ostream& out, Table& tab);
    // Getters
    Player& getPlayer1() { return player1; }
    Player& getPlayer2() { return player2; }
    Deck& getDeck() { return deck; }
    DiscardPile* getDiscardPile() { return &discardPile; }
    TradeArea* getTradeArea() { return &tradeArea; }
    // Function for saving all data to file
    void saveAllDataToFile(ostream& file);
};

#endif // TABLE_H
