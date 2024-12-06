#include "Player.h"

Player::Player(std::istream& in, const CardFactory* factory) {
    in >> playerName;

    in >> playerNumCoins;

    int numChainsFromFile;
    in >> numChainsFromFile;
    playerMaxChainFlag = (numChainsFromFile == 3);
    chains.resize(numChainsFromFile, nullptr);

    for (int i = 0; i < numChainsFromFile; i++) {
        std::string chainType;
        in >> chainType;
        if (chainType == "Blue" || chainType == "blue") {
            chains[i] = new Chain<Blue>(in, factory);
        } else if (chainType == "Chili" || chainType == "chili") {
            chains[i] = new Chain<Chili>(in, factory);
        } else if (chainType == "Stink" || chainType == "stink") {
            chains[i] = new Chain<Stink>(in, factory);
        } else if (chainType == "Green" || chainType == "green") {
            chains[i] = new Chain<Green>(in, factory);
        } else if (chainType == "Soy" || chainType == "soy") {
            chains[i] = new Chain<soy>(in, factory);
        } else if (chainType == "Black" || chainType == "black") {
            chains[i] = new Chain<black>(in, factory);
        } else if (chainType == "Red" || chainType == "red") {
            chains[i] = new Chain<Red>(in, factory);
        } else if (chainType == "Garden" || chainType == "garden") {
            chains[i] = new Chain<garden>(in, factory);
        } else if (chainType == "Empty") {
            chains[i] = nullptr;
        } else {
            throw std::runtime_error("Unknown chain type: " + chainType);
        }
    }
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
        playerMaxChainFlag = true;
        playerNumCoins -= 3;
        chains.push_back(nullptr);
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
