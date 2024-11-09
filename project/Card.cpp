#include "Card.h"

class Card{

    public:
        virtual int getCardsPerCoin (int coins) = 0;
        virtual string getName() = 0;
        virtual void print(ostream& out) = 0;
        //last function weird
        friend ostream& operator<< (ostream& out, Card& c){
            c.print(out);
            return out;
        }
};

class Blue : public Card {
    string name;
    int coinTable [4];
    public:
        Blue(string n = "Blue") : name(n), coinTable{4,6,8,10}{}
        int getCardsPerCoin(int coins){
            return *(coinTable + (coins - 1));
        }
        string getName(){ //?
            return name;
        }
        void print(ostream& out){
            out << "B";
        }
};

class Chili : public Card {
    string name;
    int coinTable [4];
    public:
        Chili(string n = "Chili"): name(n), coinTable{3,6,8,9}{}
        int getCardsPerCoin(int coins){
            return *(coinTable + (coins - 1));
        }
        string getName(){ //?
            return name;
        }
        void print(ostream& out){
            out << "C";
        }
};

class Stink : public Card {
    string name;
    public:
        int getCardsPerCoin(int coins){
            return 0;
        }
        string getName(){ //?
            return name;
        }
        void print(ostream& out){
            out << "S";
        }
};

class Green : public Card {
    string name;
    int coinTable[4];
    public:
        Green(string n = "Green"): name(n), coinTable{3,5,6,7}{}
        int getCardsPerCoin(int coins){
            return *(coinTable + (coins - 1));
        }
        string getName(){ //?
            return name;
        }
        void print(ostream& out){
            out << "G";
        }
};

class soy : public Card {
    string name;
    int coinTable[4];
    public:
        soy(string n = "soy") : name(n), coinTable{2,4,6,7}{}
        int getCardsPerCoin(int coins){
            return *(coinTable + (coins - 1));
        }
        string getName(){ //?
            return name;
        }
        void print(ostream& out){
            out << "s";
        }
};

class black : public Card {
    string name;
    int coinTable[4];
    public:
        black(string n = "black"): name(n), coinTable{2,4,5,6}{}
        int getCardsPerCoin(int coins){
            return *(coinTable + (coins - 1));
        }
        string getName(){ //?
            return name;
        }
        void print(ostream& out){
            out << "b";
        }
};

class Red : public Card {
    string name;
    int coinTable[4];
    public:
        Red(string n = "Red"): name(n), coinTable{2,3,4,5} {}
        int getCardsPerCoin(int coins){
            return *(coinTable + (coins - 1));
        }
        string getName(){ //?
            return name;
        }
        void print(ostream& out){
            out << "R";
        }
};

class garden : public Card {
    string name;
    int coinTable[4];
    public:
        garden(string n = "garden"): name(n), coinTable {0,2,3,0}{}
        int getCardsPerCoin(int coins){
            return *(coinTable + (coins - 1)); //if 0 it means we cannot have that amount of coins with this card. 
        }
        string getName(){ //?
            return name;
        }
        void print(ostream& out){
            out << "g";
        }
};

int main(){
    //Testing:
    //Red redCard;
    //int n = redCard.getCardsPerCoin(3);
    //cout << n << endl;
    return 0;
};