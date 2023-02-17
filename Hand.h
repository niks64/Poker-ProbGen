#ifndef HAND_H
#define HAND_H
#include "Card.h"


class Hand {
    private:
        std::vector<Card> cards;
    public:
        Hand() {};

        //getters
        int getSize();
        std::vector<Card> getCards();

        // setters
        void addCard(Card c);
        void clear();
        
        //print
        void print(); 
};

#endif