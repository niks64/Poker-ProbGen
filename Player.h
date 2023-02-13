#ifndef PLAYER_H
#define PLAYER_H
#include <Hand.h>

class Player {
    private:
        Hand hand;
    public:
        Player();
        void addHand(std::vector<Card> hand);
        Hand getHand();
        void clear();
};

#endif