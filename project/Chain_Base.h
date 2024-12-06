#ifndef CHAIN_BASE_H
#define CHAIN_BASE_H

#include <iostream>
#include <string>

class Chain_Base {
public:
    virtual ~Chain_Base() = default;
    virtual int sell() = 0;
    virtual int getSize() const = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual std::string getChainType() const = 0; // Explicitly use std::string
    virtual void addCard(Card* card) = 0;
};

#endif // CHAIN_BASE_H
