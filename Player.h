#ifndef PLAYER_H
#define PLAYER_H
#include "Hand.h"

class Player {
    private:
        Hand hand;
    public:
        Player();

        // getters
        Hand getHand();

        // setters
        void addHand(std::vector<Card> hand);
        void addCard(Card c);
        void clear();

        // print
        void printHand();
};

#endif