#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "CardFactory.h"
#include "CardFactory.cpp"
#include "Card.h"
#include "Deck.h"
#include "Deck.cpp"
#include "DiscardPile.h"
#include "DiscardPile.cpp"
#include "TradeArea.h"
#include "TradeArea.cpp"
#include "Hand.h"
#include "Hand.cpp"
#include "Chain.h"
#include "Player.h"
#include "Player.cpp"
#include "Table.h"
#include "Table.cpp"


void addCardToChain(Player& playerInstance, Table* tb, Card* card){
    bool success = false;
    for (auto chain: playerInstance.getChains()){
        if(chain!=nullptr && ((*chain).getChainType() == (*card).getName())){
            (*chain).addCard(card);
            success = true;
            cout << "Successfully added " << (*card).getName() << " to an existing chain.\n";
            break;
        }
    }
    if(success == false){
        //find empty chain slot to start new chain with new card
        bool emptyChainSlotFound = false;
        for(size_t i=0; i<playerInstance.getChains().size();++i){
            if(playerInstance.getChains()[i] == nullptr){
                //free slot found, lets create a new chain. 
                if (card->getName() == "Blue") {
                    playerInstance.getChains()[i] = new Chain<Blue>();
                }
                else if (card->getName() == "Chili") {
                    playerInstance.getChains()[i] = new Chain<Chili>();
                }
                else if (card->getName() == "Stink") {
                    playerInstance.getChains()[i] = new Chain<Stink>();
                }
                else if (card->getName() == "Green") {
                    playerInstance.getChains()[i] = new Chain<Green>();
                }
                else if (card->getName() == "soy") {
                    playerInstance.getChains()[i] = new Chain<soy>();
                }
                else if (card->getName() == "black") {
                    playerInstance.getChains()[i] = new Chain<black>();
                }
                else if (card->getName() == "Red") {
                    playerInstance.getChains()[i] = new Chain<Red>();
                }
                else if (card->getName() == "garden") {
                    playerInstance.getChains()[i] = new Chain<garden>();
                }
                playerInstance.getChains()[i]->addCard(card);
                cout << "A new " << card->getName() <<" chain was created.\n";
                emptyChainSlotFound = true;
                break;
            }
        }
        if(emptyChainSlotFound == false){
            bool boughtThirdChain = false;
            string playerChoice;
            cout << "You are full on chains! Would you like to buy a third chain slot for 3 coins? (y/n) ";
            cin >> playerChoice;
            if(playerChoice == "Y" || playerChoice == "y"){
                try{
                    playerInstance.buyThirdChain();
                    boughtThirdChain = true;
                    cout << "Success! You bought a third chain slot\n";
                    if(playerInstance.getChains()[2] == nullptr){
                        //free slot found, lets create a new chain. 
                        if (card->getName() == "Blue") {
                            playerInstance.getChains()[2] = new Chain<Blue>();
                        }
                        else if (card->getName() == "Chili") {
                            playerInstance.getChains()[2] = new Chain<Chili>();
                        }
                        else if (card->getName() == "Stink") {
                            playerInstance.getChains()[2] = new Chain<Stink>();
                        }
                        else if (card->getName() == "Green") {
                            playerInstance.getChains()[2] = new Chain<Green>();
                        }
                        else if (card->getName() == "soy") {
                            playerInstance.getChains()[2] = new Chain<soy>();
                        }
                        else if (card->getName() == "black") {
                            playerInstance.getChains()[2] = new Chain<black>();
                        }
                        else if (card->getName() == "Red") {
                            playerInstance.getChains()[2] = new Chain<Red>();
                        }
                        else if (card->getName() == "garden") {
                            playerInstance.getChains()[2] = new Chain<garden>();
                        }
                        playerInstance.getChains()[2]->addCard(card);
                        cout << "A new " << card->getName() <<" chain was created.\n";
                        
                    }
                }
                catch(runtime_error& runtime_error) {
                    cout << "Runtime error: " << runtime_error.what() << "\n";
                    cout << "You will have to sell one of your chains.\n";
                }
            }

            if(!boughtThirdChain){
                for (size_t i=0; i<playerInstance.getChains().size(); ++i){
                    if(playerInstance.getChains()[i]!=nullptr){
                        std::cout << "Chain #" << (i + 1) << ": ";
                        playerInstance.getChains()[i]->print(cout);
                        cout << " ";
                    }
                }
                int deadChainIndex;
                do {
                    std::cout << "Enter the index of the chain to sell (1-" << playerInstance.getMaxNumChains() << "): ";
                    std::cin >> deadChainIndex;
                    deadChainIndex--; // Adjust for 0-based index
                } while (deadChainIndex < 0 || deadChainIndex >= playerInstance.getMaxNumChains() || playerInstance.getChains()[deadChainIndex] == nullptr);
                int money = playerInstance.getChains()[deadChainIndex]->sell();
                playerInstance += money;
                delete playerInstance.getChains()[deadChainIndex];
                playerInstance.getChains()[deadChainIndex] = nullptr;
                cout << "You sold chain " << (deadChainIndex) << " for " << money << " coins.\n";
                if (card->getName() == "Blue") {
                    playerInstance.getChains()[deadChainIndex] = new Chain<Blue>();
                }
                else if (card->getName() == "Chili") {
                    playerInstance.getChains()[deadChainIndex] = new Chain<Chili>();
                }
                else if (card->getName() == "Stink") {
                    playerInstance.getChains()[deadChainIndex] = new Chain<Stink>();
                }
                else if (card->getName() == "Green") {
                    playerInstance.getChains()[deadChainIndex] = new Chain<Green>();
                }
                else if (card->getName() == "soy") {
                    playerInstance.getChains()[deadChainIndex] = new Chain<soy>();
                }
                else if (card->getName() == "black") {
                    playerInstance.getChains()[deadChainIndex] = new Chain<black>();
                }
                else if (card->getName() == "Red") {
                    playerInstance.getChains()[deadChainIndex] = new Chain<Red>();
                }
                else if (card->getName() == "garden") {
                    playerInstance.getChains()[deadChainIndex] = new Chain<garden>();
                }
                playerInstance.getChains()[deadChainIndex]->addCard(card);
                cout << "A new " << card->getName() <<" chain was created.\n";
                }
        }
    }
}


void saveGameToFile(Table& table){
    ofstream file("savegame.txt");
    if(file.is_open()){
        table.saveAllDataToFile(file);
        file.close();
    }
}



int main(){
    string p1Name;
    string p2Name;
    CardFactory* cf = CardFactory::getFactory();
    bool gameDoneFlag = false;
    string winningPlayerName;
    char userInput;
    cout << "Do you want to load from a saved game file? (y/n): ";
    cin >> userInput;
    Table* tbp = nullptr;
    if(userInput == 'Y' || userInput == 'y'){
        ifstream fileInStream("savegame.txt");
        bool successFlagFileOpen = fileInStream.is_open();
        bool fileIsEmpty = false;
        if(successFlagFileOpen){
            fileInStream.seekg(0, ios::end);
            if(fileInStream.tellg() == 0){
                cout << "The save file is empty. Please start a new game.\n" << endl;
                fileInStream.close();
                fileIsEmpty = true;
            }
            if(!fileIsEmpty){
                fileInStream.seekg(0, ios::beg);
                tbp = new Table(fileInStream, cf);
                fileInStream.close();
                cout << "Data read from file\n";
            }
        }
        if(!successFlagFileOpen || fileIsEmpty){
            cout << "Enter the name of the 1st player: ";
            cin >> p1Name;
            cout << "Enter the name of the 2nd player: ";
            cin >> p2Name;
            tbp = new Table(p1Name, p2Name, cf);
        }

    }else{
        cout << "Enter the name of the 1st player: ";
        cin >> p1Name;
        cout << "Enter the name of the 2nd player: ";
        cin >> p2Name;
        tbp = new Table(p1Name, p2Name, cf);
    }

    while(!gameDoneFlag){
        for(int turnIndex = 0; turnIndex <= 1; ++turnIndex){
            Player& playingPlayer = (turnIndex==0) ? *(tbp->player1) : *(tbp->player2);
            Player& stallPlayer = (turnIndex==0) ? *(tbp->player2) : *(tbp->player1);
            cout<< "\nIt's " <<  playingPlayer.getName() << "'s turn.\n";
            cout<< "\n" << *tbp << endl;
            cout<< "Would you like to save the game? (y/n): ";
            cin >> userInput;
            if(userInput == 'Y' || userInput == 'y'){
                saveGameToFile(*tbp);
                delete tbp;//delete table and break loop
                return 0;
            }
            

            int numCardsTA = tbp->tradeArea.numCards();
            //go through cards on trade floor 
            if(numCardsTA > 0){
                cout<< "Cards were left in the trade area from " << stallPlayer.getName() <<"\n"<< endl;
                cout<< "Current " << tbp->tradeArea << endl;
                auto taCards = tbp->tradeArea.getCards();
                for (auto start = taCards.begin(); start != taCards.end();){
                    Card* card = *start;
                    //propose to player to add the card to one of their chain
                    cout << "Would you like to add the card of type [" << (*card).getName() << "] to your chains? (y/n): ";
                    cin >> userInput;
                    if(userInput == 'Y' || userInput == 'y'){
                        addCardToChain(playingPlayer, tbp, card);
                        start = taCards.erase(start); //remove from the trade floor
                    }
                    else{
                        tbp->discardPile += card; //send card to the graveyard lol
                        start = taCards.erase(start); //remove from the trade floor
                        cout << "You have discarded " << (*card).getName() << ".\n";
                    }
                }
                tbp->tradeArea = TradeArea(); //reset
                //rebuild
                for (auto card : taCards){
                    tbp->tradeArea+=card;
                }
            }

            //play from hand
            playingPlayer.getHand().print(cout);
            Card* frontCard = playingPlayer.getHand().play();
            //check if we have a top card... 
            if(frontCard){
                cout << "Your top card is " << frontCard->getName()  << "\n" << endl;
                //do we ask here if user wants to add to chain? Or is it forced?? 
                addCardToChain(playingPlayer, tbp, frontCard);
            }
            //ask if player wants to repeat play from hand
            cout << "Would you like to play the next top card from your hand? (y/n): ";
            cin >> userInput;

            if(userInput == 'Y' || userInput == 'y'){
                Card* handsNextCard = playingPlayer.getHand().play();
                if(handsNextCard){
                    cout << "Your top card is " << handsNextCard->getName()  << "\n" << endl;
                    cout << "Would you like to add the card [" << (*handsNextCard).getName() << "] to your chains? (y/n): ";
                    cin >> userInput;
                    if(userInput == 'Y' || userInput == 'y'){
                        addCardToChain(playingPlayer, tbp, handsNextCard);
                    }
                    else{
                        tbp->discardPile += handsNextCard;
                        cout << "You have discarded " << (*handsNextCard).getName() << ".\n";
                    }
                }
            }

            //discard card from hand
            cout << "Would you like to discard a card from your hand? (y/n): ";
            cin >> userInput;
            if(userInput == 'Y' || userInput == 'y'){
                playingPlayer.getHand().print(cout);//show player hand
                cout << "Select which card to discard (index from 0): ";
                int userInputDesiredIndex;
                cin >> userInputDesiredIndex;
                Card* deadCard = playingPlayer.getHand()[userInputDesiredIndex];
                if(deadCard){
                    //throw to discard pile
                    tbp->discardPile += deadCard;
                    cout << "You have discarded a " << (*deadCard).getName() << " card.\n";
                }
                else{
                    cout << "You have selected an invalid index.\n";
                }
            }

            //draw three from deck and put in TA
            for(int numCards = 0; numCards < 3; numCards++){
                Card* tempCard = tbp->deck.draw();
                if(tempCard){//check if card was drawn
                    tbp->tradeArea += tempCard;
                }
            }

            //populate trade area while matches ta bean
            while(tbp->discardPile.top() && tbp->tradeArea.legal(tbp->discardPile.top())){
                tbp->tradeArea += tbp -> discardPile.pickUp();//loop until no match
            }

            //allow chain of cards from trade area
            auto taCards = tbp->tradeArea.getCards();
            for (auto start = taCards.begin(); start != taCards.end();) {
                Card* card = *start;
                std::cout << "Trade Area Card: " << card->getName() << "\n";
                std::cout << "Would you like to add it to your chain? (y/n): ";
                std::cin >> userInput;
                if (userInput == 'y' || userInput == 'Y') {
                    //TODO ADD CARD TO CHAIN!
                    addCardToChain(playingPlayer, tbp, card);
                    start = taCards.erase(start);
                }
                else {
                    ++start;
                }
            }

            tbp->tradeArea = TradeArea(); //reset
                //rebuild
            for (auto card : taCards){
                tbp->tradeArea+=card;
            }


            //Add 2 cards from deck to player hand
            for (int i = 0; i < 2; ++i) {
                Card* cardDrawn = tbp->deck.draw();
                if (cardDrawn) {
                    playingPlayer.getHand() += cardDrawn;
                }
            }

            //wincon
            if(tbp->win(winningPlayerName)){
                gameDoneFlag = true;
                break; //exit game loop
            }

        }
    } 
    cout << "Game Over! Congrats to the winner, " << winningPlayerName << "!" << endl;

    delete tbp;
    return 0;  
}