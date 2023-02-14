#ifndef CARD_H
#define CARD_H
#include "definitions.h"
#include <iostream>

class Card {
    private: 
        suit cardSuit;
        value faceValue;
    public:
        Card(suit s, value val) {
            this->cardSuit = s;
            this->faceValue = val;
        }


        suit getSuit() {
            return this->cardSuit;
        }

        value getValue() {
            return this->faceValue;
        }

        void print() {
            printf("%-*s%-*s", SUIT_STRING_LENGTH, suitStrings[this->cardSuit].c_str(), VALUE_STRING_LENGTH, valueStrings[this->faceValue].c_str());
        }
};
#endif