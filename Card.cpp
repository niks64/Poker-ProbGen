#include "Card.h"

Card::Card(suit s, value val) {
    this->cardSuit = s;
    this->faceValue = val;
}

suit Card::getSuit() {
    return this->cardSuit;
}

value Card::getValue() {
    return this->faceValue;
}

void Card::print() {
    printf("%-*s%-*s", SUIT_STRING_LENGTH, suitStrings[this->cardSuit].c_str(), VALUE_STRING_LENGTH, valueStrings[this->faceValue].c_str());
}

bool Card::operator==(const Card &c) {
    return this->cardSuit == c.cardSuit && this->faceValue == c.faceValue;
}

bool Card::operator!=(const Card &c) {
    return !(*this == c);
}