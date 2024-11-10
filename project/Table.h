#include <iostream> 
#include <Player.h>
#include <Deck.h>
#include <DiscardPile.h>
#include <TradeArea.h>

using namespace std;


class Table{
    Player* player1;
    Player* player2;
    Deck* deck;
    DiscardPile discardPile;
    TradeArea tradeArea;
    public:
        Table(Player* p1, Player* p2, Deck* d) { //default constructor
            //init the game at the start
            player1 = p1;
            player2 = p2;
            deck = d;
            discardPile = DiscardPile();
            tradeArea = TradeArea();
        }
        Table(istream&); //?
        bool win(string&);
        void printHand(bool);
        friend ostream& operator<<(ostream&, Table&);
        //getters
        Player& getPlayer1() { return *player1;}
        Player& getPlayer2() { return *player2;}
        Deck& getDeck() { return *deck;}
        DiscardPile* getDiscardPile() { return &discardPile;}
        TradeArea* getTradeArea() { return &tradeArea;}
};

bool Table::win(string& playerName){
    //win cons: deck size is 0 (no cards left) and one player has more coins than the other. 
    if((*deck).size() != 0){
         //here no one has won yet since there are still cards left in the deck..
        return false;
    }else{
        if(player1->getName() == playerName){
            if(player1->getNumCoins() > player2->getNumCoins()) return true;
            else return false;
        }
        if(player2->getName() == playerName){
            if(player2->getNumCoins() > player1->getNumCoins()) return true;
            else return false;
        }
    }
}

void Table::printHand(bool verbose){ //top card of both players, or all cards of both players. 
    player1->printHand(cout, verbose); //can make use of this? 
    player2->printHand(cout, verbose);
};

ostream& operator<< (ostream& out, Table& tab){
    out << "Deck:]\n" << tab.getDeck() << endl;
    out << "DiscardPile\n" << *tab.getDiscardPile() <<endl;
    out << "TradeArea\n" << *tab.getTradeArea() << endl;
    out << "Player1\n" << tab.getPlayer1() << endl;
    out << "Player2\n" << tab.getPlayer2() << endl;
    return out;
}




