#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

using namespace std;

class Card{

    public:
        virtual int getCardsPerCoin (int coins) = 0;
        virtual string getName() = 0;
        virtual void print(ostream& out) = 0;
        friend ostream& operator<< (ostream& out, Card& c){
            c.print(out);
            return out;
        }
};

class Blue : public Card {
    const string name;
    public:
    
        int coinTable [4];
        Blue() : name("Blue"), coinTable{4,6,8,10}{}

        int getCardsPerCoin(int coins){
            return *(coinTable + (coins - 1));
        }

        string getName(){
            return name;
        }
        void print(ostream& out){
            out << name.front();
        }
};

class Chili : public Card {
    const string name;
    public:
        int coinTable [4];
        Chili(): name("Chili"), coinTable{3,6,8,9}{}
        int getCardsPerCoin(int coins){
            return *(coinTable + (coins - 1));
        }
        string getName(){
            return name;
        }
        void print(ostream& out){
            out << name.front();
        }
};

class Stink : public Card {
    const string name;
    public:
        int coinTable [4];
        Stink(): name("Stink"), coinTable{3,5,7,8}{}
        int getCardsPerCoin(int coins){
            return 0;
        }
        string getName(){
            return name;
        }
        void print(ostream& out){
            out << name.front();
        }
};

class Green : public Card {
    const string name;
    public:
        int coinTable[4];
        Green(): name("Green"), coinTable{3,5,6,7}{}
        int getCardsPerCoin(int coins){
            return *(coinTable + (coins - 1));
        }
        string getName(){
            return name;
        }
        void print(ostream& out){
            out << name.front();
        }
};

class soy : public Card {
    const string name;
    public:
        int coinTable[4];
        soy() : name("soy"), coinTable{2,4,6,7}{}
        int getCardsPerCoin(int coins){
            return *(coinTable + (coins - 1));
        }
        string getName(){
            return name;
        }
        void print(ostream& out){
            out << name.front();
        }
};

class black : public Card {
    const string name;
    public:
        int coinTable[4];
        black(): name("black"), coinTable{2,4,5,6}{}
        int getCardsPerCoin(int coins){
            return *(coinTable + (coins - 1));
        }
        string getName(){
            return name;
        }
        void print(ostream& out){
            out << name.front();
        }
};

class Red : public Card {
    const string name;
    public:
            
        int coinTable[4];
        Red(): name("Red"), coinTable{2,3,4,5}{}
        int getCardsPerCoin(int coins){
            return *(coinTable + (coins - 1));
        }
        string getName(){
            return name;
        }
        void print(ostream& out){
            out << name.front();
        }
};

class garden : public Card {
    const string name;
    public:
        int coinTable[4];
        garden(): name("garden"), coinTable {0,2,3,0}{}
        int getCardsPerCoin(int coins){
            return *(coinTable + (coins - 1)); //if 0 it means we cannot have that amount of coins with this card. 
        }
        string getName(){
            return name;
        }
        void print(ostream& out){
            out << name.front();
        }
};



#endif // CARD_H