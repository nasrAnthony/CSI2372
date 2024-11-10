#include <iostream>
#include <list>
#include "Card.h"

using namespace std;


class TradeArea{
    list<Card*> cardList = {}; //init empty
    public:
        TradeArea(){};
        TradeArea(istream&); //custom constructor from file
        TradeArea& operator+=(Card*);
        bool legal(Card*);
        Card* trade(string);
        int numCards() { return cardList.size(); }
        friend ostream& operator<<(ostream&, TradeArea&);
};

TradeArea:: TradeArea(istream& in){
    while(!in.eof()){
        string temp;
        in >> temp;
        if(temp == "Blue"){
            Card* tempCard = new Blue();
            cardList.push_back(tempCard);
        }
        if(temp == "Chili"){
                Card* tempCard = new Chili();
                cardList.push_back(tempCard);
        }
        if(temp == "Stink"){
            Card* tempCard = new Stink();
            cardList.push_back(tempCard);
        }
        if(temp == "Green"){
            Card* tempCard = new Green();
            cardList.push_back(tempCard);
        }
        if(temp == "soy"){
            Card* tempCard = new soy();
            cardList.push_back(tempCard);
        }
        if(temp == "Red"){
            Card* tempCard = new Red();
            cardList.push_back(tempCard);
        }
        if(temp == "black"){
            Card* tempCard = new black();
            cardList.push_back(tempCard);
        }
        if(temp == "garden"){
            Card* tempCard = new garden();
            cardList.push_back(tempCard);
        }
    }
};

TradeArea& TradeArea::operator+=(Card* c){ //DOESNT check if legal. 
    this->cardList.push_back(c);
    return *this;
};

bool TradeArea::legal(Card* c){
    if(cardList.size() == 0){ //meaning no cards in trade Area yet, anything coming in is legal
        return true;
    }
    else{
        for (list<Card*>::iterator itr = cardList.begin(); itr != cardList.end(); itr++){
            if((*itr)->getName() == c->getName()){ //card of same bean was found
                return true;
            }
        }
    }
};

Card* TradeArea:: trade(string name){
        for (list<Card*>::iterator itr = cardList.begin(); itr != cardList.end(); itr++){
            if((*itr)->getName() == name){ //card of same bean was found
                Card* temp = (*itr);
                cardList.erase(itr);
                return temp;
            }
        }
};

ostream& operator << (ostream& out, TradeArea& ta){
    out << "TradeArea: ";
    for (list<Card*>::iterator itr = ta.cardList.begin(); itr != ta.cardList.end(); itr++){
        (*itr)->print(out); //or just getName() here??? 
        }
    return out;
};


