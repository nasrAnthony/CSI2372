#include "Table.h"

Table::Table(istream& in, const CardFactory* factory)
    : player1(in, factory), player2(in, factory), deck(in, factory), discardPile(in, factory), tradeArea(in, factory) {}

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
    out << "Deck:\n" << tab.getDeck() << endl;
    out << "DiscardPile:\n";
    tab.getDiscardPile()->print(out);
    out << endl;
    out << "TradeArea:\n" << *tab.getTradeArea() << endl;
    out << "Player 1:\n" << tab.getPlayer1() << endl;
    out << "Player 2:\n" << tab.getPlayer2() << endl;
    return out;
}

void Table::saveAllDataToFile(ostream& file) {
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
