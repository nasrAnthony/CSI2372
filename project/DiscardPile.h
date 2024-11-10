#include <iostream>
#include <vector>
#include "Card.h"

using namespace std;

class DiscardPile : public vector<Card*>{
    public:
        DiscardPile(istream&);
        DiscardPile& operator +=(Card*);
        Card* pickUp(); //show and remove
        Card* top();//show only
        void print(ostream&);
        friend ostream& operator<<(ostream&, DiscardPile&);
};

DiscardPile::DiscardPile(istream& in){
    while(!in.eof()){
        string temp;
        in >> temp;
        if(temp == "Blue"){
            Card* tempCard = new Blue();
            push_back(tempCard);
        }
        if(temp == "Chili"){
                Card* tempCard = new Chili();
                push_back(tempCard);
        }
        if(temp == "Stink"){
            Card* tempCard = new Stink();
            push_back(tempCard);
        }
        if(temp == "Green"){
            Card* tempCard = new Green();
            push_back(tempCard);
        }
        if(temp == "soy"){
            Card* tempCard = new soy();
            push_back(tempCard);
        }
        if(temp == "Red"){
            Card* tempCard = new Red();
            push_back(tempCard);
        }
        if(temp == "black"){
            Card* tempCard = new black();
            push_back(tempCard);
        }
        if(temp == "garden"){
            Card* tempCard = new garden();
            push_back(tempCard);
        }
    }
};

DiscardPile& DiscardPile::operator +=(Card *c){
    this->push_back(c);
    return *this;
};

Card* DiscardPile:: pickUp(){   
    if(this->size() == 0){
        return NULL;
    }
    else{
        Card * topCard = this->back();
        this->pop_back();
        return topCard;
    }
};

Card* DiscardPile::top(){
    if(this->size() == 0){
        return NULL;
    }
    else{
        return this->back();
    }
}

void DiscardPile::print(ostream& out){
    for(Card* c : *this){
        c->print(out);
    }
}

ostream& operator<<(ostream& out, DiscardPile& discPile){
    out << "DiscardPile= ";
    Card * topCard = discPile.back();
    out << topCard->getName();
}

