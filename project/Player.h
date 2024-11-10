#include <iostream>
#include <exception> 
#include "Card.h"
#include "Chain.h"
#include "Hand.h"

class Player{
    string playerName;
    int playerNumCoins;
    Hand playerHand;
    Chain<Card> chains[3]; //max 3 chains per player
    bool playerMaxChainFlag;
    public:
        Player(string& name): playerName(name), playerNumCoins(0), playerMaxChainFlag(false){};
        Player(istream&, Chain<Card>&, Chain<Card>&, Chain<Card>&, Hand&);
        string getName() const;
        int getNumCoins() const;
        Player& operator+=(int); //add coins
        int getMaxNumChains() const;
        int getNumChains()const;
        Chain<Card>& operator[] (int);
        void buyThirdChain();
        void printHand(ostream&, bool);
        Hand& getPlayerHand(){ return playerHand;} //getter for private member playerHand
        friend ostream& operator <<(ostream&, Player&);
};

Player::Player(istream& in, Chain<Card>& chain1, Chain<Card>& chain2, Chain<Card>& chain3, Hand& h){
    in >> playerName;
    in >> playerNumCoins;
    int numChainsFromFile;
    in >> numChainsFromFile;
    if(numChainsFromFile == 3) playerMaxChainFlag = true;
    else playerMaxChainFlag = false;
    chains[0] = chain1;
    chains[1] = chain2;
    chains[3] = chain3;
    playerHand = h;
};

string Player::getName() const{
    return playerName;
};

int Player::getNumCoins() const{
    return playerNumCoins;
};

Player& Player::operator+=(int num){
    playerNumCoins += num;
};

int Player::getMaxNumChains() const{
    if(playerMaxChainFlag) return 3;
    else return 2;
};

int Player::getNumChains() const{
    int chainCount = 0;
    //iterate over player chains
    for (Chain<Card> c: chains){
        //check if chain is empty (empty chain not counted as chain a player has)
        if(!(c.getSize() == 0)){chainCount++;}
    }
    return chainCount;
};

Chain<Card>& Player::operator[](int index){
    return chains[index];
};

void Player::buyThirdChain(){
    if(playerNumCoins < 3){
        throw("NotEnoughCoins");
    }
    else{
        playerMaxChainFlag = true; //just bought the 3rd chain
        playerNumCoins -= 2;
    }
};

void Player::printHand(ostream& out, bool verbose){
    if(playerHand.getSize() == 0){
        out << "Hand is empty";
    }
    else{
        if(!verbose){
            playerHand.top()->print(out);
        }
        else{   
            for(int i = 0; i < playerHand.getSize(); i++){
                playerHand[i]->print(out);
            }
        }
    }
};

ostream& operator<<(ostream& out, Player& p){
    out << p.getName();
    out << " " << p.getNumCoins() << " coins" << endl;
    //display player chains:
    for(int i = 0; i < p.chains->getSize(); i++){
        if(p.chains[i].getSize() == 0){
            out << "Chain# " << i + 1 << " is empty." << endl;
        }
        else{
            out << p.chains[i].getCardChain()[0]->getName(); //expecting Red R R R R format...
            for (Card* c : p.chains[i].getCardChain()){
                out << " ";
                c->print(out);
            }
            out << endl;
        }
    }
}
