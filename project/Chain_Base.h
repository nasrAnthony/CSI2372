#include <iostream>

class Chain_Base {
    public:
        virtual ~Chain_Base() = default;
        virtual int sell() = 0;
};