#ifndef PLAYER_H
#define PLAYER_H
#include "Hand.h"

class Player {
    private:
        Hand hand;
        int num = 0;
    public:
        Player();

        // getters
        Hand getHand();
        int getNum();

        // setters
        void addHand(std::vector<Card> hand);
        void addCard(Card c);
        void clear();
        void setNum(int n);

        // print
        void printHand();
};

#endif