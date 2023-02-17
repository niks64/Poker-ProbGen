#include "Hand.h"

int Hand::getSize() {
    return this->cards.size();
}

void Hand::addCard(Card c) {
    this->cards.push_back(c);
}

void Hand::clear() {
    this->cards.clear();
}

std::vector<Card> Hand::getCards() {
    return this->cards;
}

void Hand::print() {
    for (Card c : this->cards) {
        c.print();
    }
}  