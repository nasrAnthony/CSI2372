#include <iostream>
#include <fstream>
#include <string>
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
#include "Chain_Base.h"
#include "Chain.h"
#include "Player.h"
#include "Player.cpp"
#include "Table.h"
#include "Table.cpp"

using namespace std;

// Helper functions to add a card to a chain and create a new chain
bool addCardToChain(Chain_Base& chain, Card* card);
Chain_Base* createChainForCard(Card* card);

int main() {
    // Initialize variables
    CardFactory* cardFactory = CardFactory::getFactory();
    Table table;
    string input;
    string playerName1, playerName2;
    bool newGame = false;
    char choice;

    // Ask user whether to start a new game or load from file
    cout << "Do you want to load a saved game? (y/n): ";
    cin >> choice;
    cin.ignore(); // Consume newline character

    if (choice == 'y' || choice == 'Y') {
        // Load game from file
        ifstream file("gamesave.txt");
        if (!file) {
            cout << "No saved game found. Starting a new game." << endl;
            newGame = true;
        } else {
            // Load the game
            table = Table(file, cardFactory);
            file.close();
        }
    } else {
        newGame = true;
    }

    if (newGame) {
        // Start a new game
        cout << "Enter name of Player 1: ";
        getline(cin, playerName1);
        cout << "Enter name of Player 2: ";
        getline(cin, playerName2);

        // Initialize the Deck
        Deck deck = cardFactory->getDeck();

        // Create Players
        Player player1(playerName1);
        Player player2(playerName2);

        // Draw 5 cards for each player's Hand
        for (int i = 0; i < 5; ++i) {
            player1.getPlayerHand() += deck.draw();
            player2.getPlayerHand() += deck.draw();
        }

        // Initialize Table
        table = Table();
        table.player1 = player1;
        table.player2 = player2;
        table.deck = deck;
    }

    // Main game loop
    while (table.getDeck().size() > 0) {
        // Ask if user wants to pause and save the game
        cout << "Do you want to pause and save the game? (y/n): ";
        cin >> choice;
        cin.ignore();
        if (choice == 'y' || choice == 'Y') {
            // Save the game
            ofstream file("gamesave.txt");
            table.saveAllDataToFile(file);
            file.close();
            cout << "Game saved to gamesave.txt. Exiting..." << endl;
            return 0;
        }

        // For each player
        for (int i = 0; i < 2; ++i) {
            // Determine current player
            Player& currentPlayer = (i == 0) ? table.getPlayer1() : table.getPlayer2();

            cout << "\nIt's " << currentPlayer.getName() << "'s turn." << endl;

            // Display Table
            cout << table;

            // Step 1: If TradeArea is not empty
            if (table.getTradeArea()->numCards() > 0) {
                cout << "TradeArea has the following cards:" << endl;
                cout << *(table.getTradeArea()) << endl;

                // For each card in TradeArea
                while (table.getTradeArea()->numCards() > 0) {
                    Card* tradeCard = table.getTradeArea()->trade("");
                    cout << "Do you want to chain the card: " << tradeCard->getName() << "? (y/n): ";
                    cin >> choice;
                    cin.ignore();
                    if (choice == 'y' || choice == 'Y') {
                        // Add the card to the appropriate chain, or start a new chain
                        string cardName = tradeCard->getName();
                        bool chainFound = false;

                        // Check if player has a chain of this type
                        for (int c = 0; c < currentPlayer.getNumChains(); ++c) {
                            if (currentPlayer[c].getChainType() == cardName) {
                                // Add the card to the chain
                                Chain_Base& chain = currentPlayer[c];
                                bool cardAdded = addCardToChain(chain, tradeCard);
                                if (!cardAdded) {
                                    cout << "Error adding card to chain." << endl;
                                }
                                chainFound = true;
                                break;
                            }
                        }

                        if (!chainFound) {
                            // Player does not have a chain of this type
                            if (currentPlayer.getNumChains() < currentPlayer.getMaxNumChains()) {
                                // Start a new chain
                                Chain_Base* newChain = createChainForCard(tradeCard);
                                currentPlayer.addChain(newChain);
                            } else {
                                // Player must sell an existing chain to start a new one
                                cout << "No available chain slots. You must sell an existing chain to start a new one." << endl;
                                // Let the player choose a chain to sell
                                cout << "Your chains are: " << endl;
                                for (int c = 0; c < currentPlayer.getNumChains(); ++c) {
                                    cout << c+1 << ": ";
                                    currentPlayer[c].print(cout);
                                    cout << endl;
                                }
                                cout << "Select a chain to sell (enter number): ";
                                int chainIndex;
                                cin >> chainIndex;
                                cin.ignore();
                                chainIndex--; // Adjust for zero-based index
                                if (chainIndex >= 0 && chainIndex < currentPlayer.getNumChains()) {
                                    // Sell the chain
                                    int coinsEarned = currentPlayer[chainIndex].sell();
                                    currentPlayer += coinsEarned;
                                    // Remove the chain
                                    currentPlayer.removeChain(chainIndex);
                                    // Now create a new chain
                                    Chain_Base* newChain = createChainForCard(tradeCard);
                                    currentPlayer.addChain(newChain);
                                } else {
                                    cout << "Invalid choice." << endl;
                                }
                            }
                        }
                    } else {
                        // Leave the card in the TradeArea for the next player
                        table.getTradeArea()->operator+=(tradeCard);
                        break; // Exit the loop
                    }
                }
            }

            // Step 2: Play topmost card from Hand
            if (currentPlayer.getPlayerHand().getSize() > 0) {
                Card* topCard = currentPlayer.getPlayerHand().play();
                cout << "You played: " << topCard->getName() << endl;

                // Add the card to a chain with the same beans
                string cardName = topCard->getName();
                bool chainFound = false;

                // Check if player has a chain of this type
                for (int c = 0; c < currentPlayer.getNumChains(); ++c) {
                    if (currentPlayer[c].getChainType() == cardName) {
                        // Add the card to the chain
                        Chain_Base& chain = currentPlayer[c];
                        bool cardAdded = addCardToChain(chain, topCard);
                        if (!cardAdded) {
                            cout << "Error adding card to chain." << endl;
                        }
                        chainFound = true;
                        break;
                    }
                }

                if (!chainFound) {
                    // Player does not have a chain of this type
                    if (currentPlayer.getNumChains() < currentPlayer.getMaxNumChains()) {
                        // Start a new chain
                        Chain_Base* newChain = createChainForCard(topCard);
                        currentPlayer.addChain(newChain);
                    } else {
                        // Player must sell an existing chain to start a new one
                        cout << "No available chain slots. You must sell an existing chain to start a new one." << endl;
                        // Let the player choose a chain to sell
                        cout << "Your chains are: " << endl;
                        for (int c = 0; c < currentPlayer.getNumChains(); ++c) {
                            cout << c+1 << ": ";
                            currentPlayer[c].print(cout);
                            cout << endl;
                        }
                        cout << "Select a chain to sell (enter number): ";
                        int chainIndex;
                        cin >> chainIndex;
                        cin.ignore();
                        chainIndex--; // Adjust for zero-based index
                        if (chainIndex >= 0 && chainIndex < currentPlayer.getNumChains()) {
                            // Sell the chain
                            int coinsEarned = currentPlayer[chainIndex].sell();
                            currentPlayer += coinsEarned;
                            // Remove the chain
                            currentPlayer.removeChain(chainIndex);
                            // Now create a new chain
                            Chain_Base* newChain = createChainForCard(topCard);
                            currentPlayer.addChain(newChain);
                        } else {
                            cout << "Invalid choice." << endl;
                        }
                    }
                }
            }

            // Step 3: Option to repeat Step 2
            cout << "Do you want to play the next topmost card from your hand? (y/n): ";
            cin >> choice;
            cin.ignore();
            if (choice == 'y' || choice == 'Y') {
                if (currentPlayer.getPlayerHand().getSize() > 0) {
                    // Repeat Step 2
                    Card* topCard = currentPlayer.getPlayerHand().play();
                    cout << "You played: " << topCard->getName() << endl;

                    // Add the card to a chain with the same beans
                    string cardName = topCard->getName();
                    bool chainFound = false;

                    // Check if player has a chain of this type
                    for (int c = 0; c < currentPlayer.getNumChains(); ++c) {
                        if (currentPlayer[c].getChainType() == cardName) {
                            // Add the card to the chain
                            Chain_Base& chain = currentPlayer[c];
                            bool cardAdded = addCardToChain(chain, topCard);
                            if (!cardAdded) {
                                cout << "Error adding card to chain." << endl;
                            }
                            chainFound = true;
                            break;
                        }
                    }

                    if (!chainFound) {
                        // Player does not have a chain of this type
                        if (currentPlayer.getNumChains() < currentPlayer.getMaxNumChains()) {
                            // Start a new chain
                            Chain_Base* newChain = createChainForCard(topCard);
                            currentPlayer.addChain(newChain);
                        } else {
                            // Player must sell an existing chain to start a new one
                            cout << "No available chain slots. You must sell an existing chain to start a new one." << endl;
                            // Let the player choose a chain to sell
                            cout << "Your chains are: " << endl;
                            for (int c = 0; c < currentPlayer.getNumChains(); ++c) {
                                cout << c+1 << ": ";
                                currentPlayer[c].print(cout);
                                cout << endl;
                            }
                            cout << "Select a chain to sell (enter number): ";
                            int chainIndex;
                            cin >> chainIndex;
                            cin.ignore();
                            chainIndex--; // Adjust for zero-based index
                            if (chainIndex >= 0 && chainIndex < currentPlayer.getNumChains()) {
                                // Sell the chain
                                int coinsEarned = currentPlayer[chainIndex].sell();
                                currentPlayer += coinsEarned;
                                // Remove the chain
                                currentPlayer.removeChain(chainIndex);
                                // Now create a new chain
                                Chain_Base* newChain = createChainForCard(topCard);
                                currentPlayer.addChain(newChain);
                            } else {
                                cout << "Invalid choice." << endl;
                            }
                        }
                    }
                } else {
                    cout << "Your hand is empty." << endl;
                }
            }

            // Step 4: Option to discard a card
            cout << "Do you want to discard an arbitrary card from your hand? (y/n): ";
            cin >> choice;
            cin.ignore();
            if (choice == 'y' || choice == 'Y') {
                // Show the player's full hand and player selects an arbitrary card
                cout << "Your hand is: " << endl;
                currentPlayer.printHand(cout, true);
                cout << "Enter the index (starting from 1) of the card you want to discard: ";
                int discardIndex;
                cin >> discardIndex;
                cin.ignore();
                discardIndex--; // Adjust for zero-based index
                if (discardIndex >= 0 && discardIndex < currentPlayer.getPlayerHand().getSize()) {
                    // Discard the arbitrary card from the player's hand and place it on the discard pile.
                    Card* discardedCard = currentPlayer.getPlayerHand()[discardIndex];
                    table.getDiscardPile()->operator+=(discardedCard);
                } else {
                    cout << "Invalid index." << endl;
                }
            }

            // Step 5: Draw three cards from the deck and place them in the trade area
            for (int i = 0; i < 3; ++i) {
                if (table.getDeck().size() > 0) {
                    Card* tradeCard = table.getDeck().draw();
                    table.getTradeArea()->operator+=(tradeCard);
                } else {
                    cout << "Deck is empty." << endl;
                    break;
                }
            }

            // Draw cards from the discard pile as long as the card matches one of the beans in the trade area
            while (table.getDiscardPile()->top() != nullptr &&
                table.getTradeArea()->legal(table.getDiscardPile()->top())) {
                // Draw the top-most card from the discard pile and place it in the trade area
                Card* discardTopCard = table.getDiscardPile()->pickUp();
                table.getTradeArea()->operator+=(discardTopCard);
            }

            // Player can either chain the cards or leave them in the trade area for the next player
            cout << "TradeArea has the following cards:" << endl;
            cout << *(table.getTradeArea()) << endl;

            // For each card in TradeArea
            while (table.getTradeArea()->numCards() > 0) {
                Card* tradeCard = table.getTradeArea()->trade("");
                cout << "Do you want to chain the card: " << tradeCard->getName() << "? (y/n): ";
                cin >> choice;
                cin.ignore();
                if (choice == 'y' || choice == 'Y') {
                    // Add the card to the appropriate chain, or start a new chain
                    string cardName = tradeCard->getName();
                    bool chainFound = false;

                    // Check if player has a chain of this type
                    for (int c = 0; c < currentPlayer.getNumChains(); ++c) {
                        if (currentPlayer[c].getChainType() == cardName) {
                            // Add the card to the chain
                            Chain_Base& chain = currentPlayer[c];
                            bool cardAdded = addCardToChain(chain, tradeCard);
                            if (!cardAdded) {
                                cout << "Error adding card to chain." << endl;
                            }
                            chainFound = true;
                            break;
                        }
                    }

                    if (!chainFound) {
                        // Player does not have a chain of this type
                        if (currentPlayer.getNumChains() < currentPlayer.getMaxNumChains()) {
                            // Start a new chain
                            Chain_Base* newChain = createChainForCard(tradeCard);
                            currentPlayer.addChain(newChain);
                        } else {
                            // Player must sell an existing chain to start a new one
                            cout << "No available chain slots. You must sell an existing chain to start a new one." << endl;
                            // Let the player choose a chain to sell
                            cout << "Your chains are: " << endl;
                            for (int c = 0; c < currentPlayer.getNumChains(); ++c) {
                                cout << c+1 << ": ";
                                currentPlayer[c].print(cout);
                                cout << endl;
                            }
                            cout << "Select a chain to sell (enter number): ";
                            int chainIndex;
                            cin >> chainIndex;
                            cin.ignore();
                            chainIndex--; // Adjust for zero-based index
                            if (chainIndex >= 0 && chainIndex < currentPlayer.getNumChains()) {
                                // Sell the chain
                                int coinsEarned = currentPlayer[chainIndex].sell();
                                currentPlayer += coinsEarned;
                                // Remove the chain
                                currentPlayer.removeChain(chainIndex);
                                // Now create a new chain
                                Chain_Base* newChain = createChainForCard(tradeCard);
                                currentPlayer.addChain(newChain);
                            } else {
                                cout << "Invalid choice." << endl;
                            }
                        }
                    }
                } else {
                    // Leave the card in the TradeArea for the next player
                    table.getTradeArea()->operator+=(tradeCard);
                    break; // Exit the loop
                }
            }

            // Step 6: Draw two cards from Deck and add to player's hand
            for (int i = 0; i < 2; ++i) {
                if (table.getDeck().size() > 0) {
                    Card* drawnCard = table.getDeck().draw();
                    currentPlayer.getPlayerHand() += drawnCard;
                } else {
                    cout << "Deck is empty." << endl;
                    break;
                }
            }
        } // End of player loop
    } // End of main game loop

    // Check who wins
    string winnerName;
    if (table.win(winnerName)) {
        cout << "Game over! The winner is " << winnerName << endl;
    } else {
        cout << "Game over! It's a tie!" << endl;
    }

    return 0;
}

// Helper function to add a card to a chain
bool addCardToChain(Chain_Base& chain, Card* card) {
    string cardName = card->getName();

    // For each possible card type
    if (cardName == "Red") {
        Chain<Red>* chainPtr = dynamic_cast<Chain<Red>*>(&chain);
        if (chainPtr) {
            *chainPtr += card;
            return true;
        }
    } else if (cardName == "Blue") {
        Chain<Blue>* chainPtr = dynamic_cast<Chain<Blue>*>(&chain);
        if (chainPtr) {
            *chainPtr += card;
            return true;
        }
    } else if (cardName == "Chili") {
        Chain<Chili>* chainPtr = dynamic_cast<Chain<Chili>*>(&chain);
        if (chainPtr) {
            *chainPtr += card;
            return true;
        }
    } else if (cardName == "Stink") {
        Chain<Stink>* chainPtr = dynamic_cast<Chain<Stink>*>(&chain);
        if (chainPtr) {
            *chainPtr += card;
            return true;
        }
    } else if (cardName == "Green") {
        Chain<Green>* chainPtr = dynamic_cast<Chain<Green>*>(&chain);
        if (chainPtr) {
            *chainPtr += card;
            return true;
        }
    } else if (cardName == "Soy") {
        Chain<soy>* chainPtr = dynamic_cast<Chain<soy>*>(&chain);
        if (chainPtr) {
            *chainPtr += card;
            return true;
        }
    } else if (cardName == "Black") {
        Chain<black>* chainPtr = dynamic_cast<Chain<black>*>(&chain);
        if (chainPtr) {
            *chainPtr += card;
            return true;
        }
    } else if (cardName == "Garden") {
        Chain<garden>* chainPtr = dynamic_cast<Chain<garden>*>(&chain);
        if (chainPtr) {
            *chainPtr += card;
            return true;
        }
    }

    return false;
}

// Helper function to create a new chain for a card and add the card to it
Chain_Base* createChainForCard(Card* card) {
    string cardName = card->getName();

    if (cardName == "Red") {
        Chain<Red>* chain = new Chain<Red>();
        *chain += card;
        return chain;
    } else if (cardName == "Blue") {
        Chain<Blue>* chain = new Chain<Blue>();
        *chain += card;
        return chain;
    } else if (cardName == "Chili") {
        Chain<Chili>* chain = new Chain<Chili>();
        *chain += card;
        return chain;
    } else if (cardName == "Stink") {
        Chain<Stink>* chain = new Chain<Stink>();
        *chain += card;
        return chain;
    } else if (cardName == "Green") {
        Chain<Green>* chain = new Chain<Green>();
        *chain += card;
        return chain;
    } else if (cardName == "Soy") {
        Chain<soy>* chain = new Chain<soy>();
        *chain += card;
        return chain;
    } else if (cardName == "Black") {
        Chain<black>* chain = new Chain<black>();
        *chain += card;
        return chain;
    } else if (cardName == "Garden") {
        Chain<garden>* chain = new Chain<garden>();
        *chain += card;
        return chain;
    }

    return nullptr;
}
