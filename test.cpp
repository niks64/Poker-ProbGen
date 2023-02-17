#include "Hand.h"

int main() {

    // for (int i = 1; i<=4; i++) {
    //     suit s = static_cast<suit>(i);
    //     std::cout << suitStrings[s] << " ";
    // }
    Card c1 = Card(static_cast<suit>(1),static_cast<value>(10));
    Card c2 = Card(static_cast<suit>(2),static_cast<value>(10));

    Hand h = Hand();
    h.addCard(c1);
    h.addCard(c2);

    printf("%-*s\n", TEXAS_HAND_STRING_LENGTH, "P1");
    h.print();

    std::cout << std::endl;



    // printf("%-2s%s", "s", "next");


}