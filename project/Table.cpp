#include "Table.h"

Table::Table(istream& in, const CardFactory* factory)
    : player1(in, factory), player2(in, factory), deck(in, factory), discardPile(in, factory), tradeArea(in, factory) {}


Table::Table(string& p1name, string& p2name, const CardFactory* cf):
    player1(p1name), player2(p2name), deck(cf->getDeck()){
    for (int i = 0; i < 5; ++i) {//give 5 cards to each player 
        player1.getHand() += deck.draw();
        player2.getHand() += deck.draw();
    }
    }

bool Table::win(string& winningPlayerName) {
    // Winning condition: deck size is 0 and one player has more coins than the other
    if (deck.size() != 0) {
        // No one has won yet since there are still cards left in the deck
        return false;
    } else {
        if (player1.getNumCoins() > player2.getNumCoins()) {
            winningPlayerName = player1.getName();
            return true;
        } else if (player2.getNumCoins() > player1.getNumCoins()) {
            winningPlayerName = player2.getName();
            return true;
        } else {
            winningPlayerName = "Tie";
            return false;
        }
    }
}

void Table::printHand(bool verbose) { // Top card of both players, or all cards of both players
    player1.printHand(cout, verbose);
    cout << endl;
    player2.printHand(cout, verbose);
    cout << endl;
}

ostream& operator<<(ostream& out, Table& tab) {
out << "----- Table -----\n";
    out << tab.player1 << std::endl;
    out << tab.player2 << std::endl;
    out << "Discard Pile Top Card: ";
    if (tab.discardPile.top()) {
        tab.discardPile.top()->print(out);
    }
    else {
        out << "Pile is empty.";
    }
    out << std::endl;

    out << tab.tradeArea << std::endl;
    out << "------------------------\n";
    return out;
}

void Table::saveAllDataToFile(ostream& file){
    // Save Player 1
    file << player1.getName() << endl;
    file << player1.getNumCoins() << endl;
    file << player1.getNumChains() << endl;
    for (const auto& chain : player1.getChains()) {
        chain->print(file);
        file << endl;
    }
    file << player1.getPlayerHand() << endl;

    // Save Player 2
    file << player2.getName() << endl;
    file << player2.getNumCoins() << endl;
    file << player2.getNumChains() << endl;
    for (const auto& chain : player2.getChains()) {
        chain->print(file);
        file << endl;
    }
    file << player2.getPlayerHand() << endl;

    // Save Deck
    file << deck << endl;

    // Save DiscardPile
    discardPile.print(file);
    file << endl;

    // Save TradeArea
    file << tradeArea << endl;
}
