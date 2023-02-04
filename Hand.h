#ifndef HAND_H
#define HAND_H
#include <Card.h>
#include <vector>


class Hand {
    private:
        std::vector<Card> cards;
    public:
        Hand();
        int getSize();
        void addCard(Card c);
        void clear();
        std::vector<Card> getCards();        
};

#endif