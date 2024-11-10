#include <iostream>
#include <vector>
#include <exception>
#include "Card.h"
#include "Chain_Base.h"

using namespace std;

template <class T> class Chain : public Chain_Base{
    vector<T*> cardChain;
    public:
        Chain(){}; //default no args constructor
        Chain(istream&); //constructor to build chain from file when game is resumed
        Chain(Card * firstCard) { cardChain.push_back(firstCard);} //default constructor
        Chain<T>& operator+=(Card*); //operator overload for (adding a card)
        int sell();
        vector<T*> getCardChain() const { return cardChain;} //getter for priv member
        int getSize() const; //helper to access size of private member cardChain
        friend ostream& operator << (ostream& out, Chain<Card>& c); //friend << operator
};  

template <class T> int Chain<T>::getSize()const{
    return cardChain.size();
};
template <class T> Chain<T>::Chain(istream&){
    while(!in.eof()){
        string input;
        in >> input;
        if(input.size() > 0){
            if(input.at(0) == 'B'){ //card read from file
                for(int i = 0; i < input.size(); i++){
                    Card * tmpCard = new Blue();
                    cardChain.push_back(tmpCard);
                }
            }
            if(input.at(0) == 'C'){
                for(int i = 0; i < input.size(); i++){
                    Card * tmpCard = new Chili();
                    cardChain.push_back(tmpCard)
                }
            }
            if(input.at(0) == 'S'){
                for(int i = 0; i < input.size(); i++){
                    Card * tmpCard = new Stink();
                    cardChain.push_back(tmpCard)
                }
            }
            if(input.at(0) == 'G'){
                for(int i = 0; i < input.size(); i++){
                    Card * tmpCard = new Green();
                    cardChain.push_back(tmpCard)
                }
            }
            if(input.at(0) == 's'){
                for(int i = 0; i < input.size(); i++){
                    Card * tmpCard = new soy();
                    cardChain.push_back(tmpCard)
                }
            }
            if(input.at(0) == 'R'){
                for(int i = 0; i < input.size(); i++){
                    Card * tmpCard = new Red();
                    cardChain.push_back(tmpCard)
                }
            }
            if(input.at(0) == 'b'){
                for(int i = 0; i < input.size(); i++){
                    Card * tmpCard = new black();
                    cardChain.push_back(tmpCard)
                }
            }
            if(input.at(0) == 'g'){
                for(int i = 0; i < input.size(); i++){
                    Card * tmpCard = new garden();
                    cardChain.push_back(tmpCard)
                }
            }
        }
    }
};

//+= operator overload
template <class T> Chain<T>& Chain<T>:: operator+=(Card* incomingCard){
    if(!dynamic_cast<T*>(incomingCard)){ //will ne nullptr if they dont match. 
        throw std::runtime_error("IllegalType: Card type does not match chain type.");
    }
    cardChain.push_back(incomingCard);
    return *this;
};

template <class T> int Chain<T>::sell(){
    if(cardChain.size() == 0) return 0; //if chain is empty. 
    else return T.getCardsPerCoin(cardChain.size());
};

//overloading << operator with friend function
ostream& operator << (ostream& out, Chain<Card>& c){
    if(c.cardChain.size() == 0) out << " Empty";
    else{
        //first print the name of the full name of the bean
        out << c.cardChain[0]->getName();
        for(int i = 0; i < c.cardChain.size(); i++){
            c.cardChain[i]->print(out);
        }
    }
};

