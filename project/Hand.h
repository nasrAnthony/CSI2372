#include <iostream> 
#include <list>
#include <queue>
#include "Card.h"

using namespace std;

class Hand {
    queue<Card*> cardsInHand;
    public:
        Hand(){}; //default constructor
        Hand(istream&);
        Hand& operator+=(Card*);
        Card* play();
        Card* top() const;
        Card* operator[] (int);
        int getSize() const { return cardsInHand.size();}; //helper to access size of the cardsInHand member
        friend ostream& operator << (ostream&, Hand&);
};

Hand::Hand(istream& in){
    if(!in.eof()){
        string temp;
        in >> temp;
        if(temp == "Blue"){
            Card* tempCard = new Blue();
            cardsInHand.push(tempCard);
        }
        if(temp == "Chili"){
            Card* tempCard = new Chili();
            cardsInHand.push(tempCard);
        }
        if(temp == "Stink"){
            Card* tempCard = new Stink();
            cardsInHand.push(tempCard);
        }
        if(temp == "Green"){
            Card* tempCard = new Green();
            cardsInHand.push(tempCard);
        }
        if(temp == "soy"){
            Card* tempCard = new soy();
            cardsInHand.push(tempCard);
        }
        if(temp == "Red"){
            Card* tempCard = new Red();
            cardsInHand.push(tempCard);
        }
        if(temp == "black"){
            Card* tempCard = new black();
            cardsInHand.push(tempCard);
        }
        if(temp == "garden"){
            Card* tempCard = new garden();
            cardsInHand.push(tempCard);
        }
    }
};

Hand& Hand::operator+=(Card* newCard){
    cardsInHand.push(newCard);
    return *this;
};

Card* Hand::play(){
    Card* temp = cardsInHand.front();
    cardsInHand.pop();
    return temp;
};

Card* Hand::top() const{
    if(cardsInHand.size() == 0) return NULL;
    else return cardsInHand.front();
};

Card* Hand::operator[](int index){
    if (index >= 0 && index < cardsInHand.size()){
        Card* targetCard = nullptr;
        queue<Card*> tempQueue;
        for(int i = 0; i < index; i++){//empty out original queue into a temp queue iuntil index is reached
            tempQueue.push(cardsInHand.front());
            cardsInHand.pop();
        }
        targetCard = cardsInHand.front(); //get card at required index
        cardsInHand.pop();
        while(cardsInHand.size() != 0){ //empty out rest of queue into temp queue
            tempQueue.push(cardsInHand.front());
            cardsInHand.pop();
        }
        cardsInHand = tempQueue; //restore original queue with the temp queue values
        return targetCard;
    }
};

ostream& operator<<(ostream& out, Hand& h){
    queue<Card*> tempQueue; //will use to copy hand cards list
    list<Card*> listCopy; //will use to restore copy before restoring original.
    int tempSize = h.cardsInHand.size(); 
    for(int i = 0; i < h.cardsInHand.size(); i++){
        listCopy.push_back(h.cardsInHand.front());
        h.cardsInHand.pop();

    }
    out << "Hand: ";
    for(int j = 0; j < tempSize; j ++ ){
        out << listCopy.front()->getName() << " ";
        tempQueue.push(listCopy.front());
        listCopy.pop_front();
    }
    out << endl;
    h.cardsInHand = tempQueue; //restore
    return out;
}