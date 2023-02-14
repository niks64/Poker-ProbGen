#ifndef HAND_H
#define HAND_H
#include "Card.h"
#include <vector>


class Hand {
    private:
        std::vector<Card> cards;
    public:
        Hand() {};
        
        int getSize() {
            return this->cards.size();
        }

        void addCard(Card c) {
            this->cards.push_back(c);
        }

        void clear() {
            this->cards.clear();
        }

        std::vector<Card> getCards() {
            return this->cards;
        }

        void print() {
            for (Card c : this->cards) {
                c.print();
            }
        }   
};

#endif