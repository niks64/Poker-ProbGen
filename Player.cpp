#include <Player.h>

Player::Player() {}

void Player::addHand(std::vector<Card> hand) {
    for (Card c : hand) {
        this->hand.addCard(c);
    }
}

Hand Player::getHand() {
    return this->hand;
}

void Player::clear() {
    this->hand.clear();
}

