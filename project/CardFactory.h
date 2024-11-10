#include <iostream> 
#include <algorithm>
#include <random>
#include <chrono>
#include "Card.h"
#include "Deck.h"

using namespace std;

class CardFactory{
    private:
        Deck* deck;
        static CardFactory* factory;
        CardFactory(const CardFactory&); //private copy constructor,assure 1 instance of cardFactory...
        CardFactory(){
            deck = new Deck();
            for(int i=0; i < 20; i++){
                Card* newCard = new Blue();
                (*deck).push_back(newCard);
            }
            for(int i=0; i < 18; i++){
                Card* newCard = new Chili();
                (*deck).push_back(newCard);
            }
            for(int i=0; i < 16; i++){
                Card* newCard = new Stink();
                (*deck).push_back(newCard);
            }
            for(int i=0; i < 14; i++){
                Card* newCard = new Green();
                (*deck).push_back(newCard);
            }
            for(int i=0; i < 12; i++){
                Card* newCard = new soy();
                (*deck).push_back(newCard);
            }
            for(int i=0; i < 10; i++){
                Card* newCard = new black();
                (*deck).push_back(newCard);
            }
            for(int i=0; i < 8; i++){
                Card* newCard = new Red();
                (*deck).push_back(newCard);
            }
            for(int i=0; i < 6; i++){
                Card* newCard = new garden();
                (*deck).push_back(newCard);
            }
            //shuffle
            unsigned seed = chrono::system_clock::now().time_since_epoch().count();
            shuffle((*deck).begin(), (*deck).end(), default_random_engine(seed));
        };

    
    public:
        static CardFactory* getFactory();
        Deck getDeck(){
            return (*deck);
        };

};

CardFactory* CardFactory:: factory = NULL; //reference to static factory initialization
CardFactory* CardFactory:: getFactory(){ //getter
            if(factory==NULL){ //initialize if null. (will be first time running)
                factory = new CardFactory();
            }
            return(factory);
    };