#include <iostream> 
#include <vector>
#include "Card.h"

using namespace std;

class Deck : public vector<Card*>{
    public:
        Deck(istream&); //constructor to build deck from file. 
        Card* draw(); //Draw top Card.
        friend ostream& operator <<(ostream&, const Deck&); //friend function
};

ostream& operator<<(ostream& out, Deck& deck){
    out << "Deck: ";
    for (int i = 0; i < deck.size(); i++){
        out << deck[i]->getName() <<" ";
    }
    return out;
}

Deck:: Deck(istream& in){
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

Card* Deck:: draw(){
    Card * drawnCard = back(); //draw card
    //remove it
    pop_back();
    return drawnCard;
};
