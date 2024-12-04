#include "Player.h"

Player::Player(istream& in, const CardFactory* factory) {
    in >> playerName;
    in >> playerNumCoins;
    int numChainsFromFile;
    in >> numChainsFromFile;
    playerMaxChainFlag = (numChainsFromFile == 3);
    chains.resize(numChainsFromFile, nullptr);
    for (int i = 0; i < numChainsFromFile; i++) {
        std::string chainType;
        in >> chainType;
        // Create the appropriate chain based on the type
        if (chainType == "Blue") {
            chains.push_back(new Chain<Blue>(in, factory));
        } else if (chainType == "Chili") {
            chains.push_back(new Chain<Chili>(in, factory));
        } else if (chainType == "Stink") {
            chains.push_back(new Chain<Stink>(in, factory));
        } else if (chainType == "Green") {
            chains.push_back(new Chain<Green>(in, factory));
        } else if (chainType == "Soy") {
            chains.push_back(new Chain<soy>(in, factory));
        } else if (chainType == "Black") {
            chains.push_back(new Chain<black>(in, factory));
        } else if (chainType == "Red") {
            chains.push_back(new Chain<Red>(in, factory));
        } else if (chainType == "Garden") {
            chains.push_back(new Chain<garden>(in, factory));
        } else {
            throw runtime_error("Unknown chain type: " + chainType);
        }
    }
    // Read player's hand
    playerHand = Hand(in, factory);
}

Player::~Player() {
    // Clean up chains
    for (auto chain : chains) {
        delete chain;
    }
}

void Player::addChain(Chain_Base* newChain) {
    if (chains.size() < getMaxNumChains()) {
        chains.push_back(newChain);
    } else {
        throw runtime_error("Cannot add more chains, maximum number reached.");
    }
}

void Player::removeChain(int index) {
    if (index >= 0 && index < static_cast<int>(chains.size())) {
        delete chains[index];
        chains.erase(chains.begin() + index);
    } else {
        throw out_of_range("Invalid chain index");
    }
}

string Player::getName() const {
    return playerName;
}

int Player::getNumCoins() const {
    return playerNumCoins;
}

Player& Player::operator+=(int num) {
    playerNumCoins += num;
    return *this;
}

int Player::getMaxNumChains() const {
    return playerMaxChainFlag ? 3 : 2;
}

int Player::getNumChains() const {
    return chains.size();
}

Chain_Base& Player::operator[](int index) {
    if (index < 0 || index >= static_cast<int>(chains.size())) {
        throw out_of_range("Invalid chain index");
    }
    return *chains[index];
}

void Player::buyThirdChain() {
    if (playerNumCoins < 3) {
        throw runtime_error("NotEnoughCoins");
    } else {
        playerMaxChainFlag = true; // Just bought the 3rd chain
        playerNumCoins -= 3;
        // Chains are added when cards are played
    }
}

void Player::printHand(ostream& out, bool verbose) {
    if (playerHand.getSize() == 0) {
        out << "Hand is empty. ";
    } else {
        if (!verbose) {
            playerHand.top()->print(out);
        } else {
            for (int i = 0; i < playerHand.getSize(); i++) {
                playerHand[i]->print(out);
                out << " ";
            }
        }
    }
}

std::ostream& operator<<(std::ostream& out, Player& p) {
    out << p.getName() << " " << p.getNumCoins() << " coins" << std::endl;

    // Display player chains
    for (size_t i = 0; i < p.getChains().size(); i++) {
        out << "Chain " << i + 1 << ": ";
        if(p.getChains()[i] == nullptr){
            out << "Empty"<<endl;
        }else{
            if (p.getChains()[i]->getSize() == 0) {
                out << "Empty" << endl;
            } else {
                p.getChains()[i]->print(out);
                out << endl;
            }
        }
    }

    return out;
}
