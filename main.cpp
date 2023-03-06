#include "Table.h"

int main(int argc, char *argv[]) {

    // Check whether to deal randomly or enter specific cards
    bool ifSpecify = false;
    
    if (argc > 1 && strcmp("-s", argv[1]) == 0) {
        ifSpecify = true;
    }

    // Ask configurations of the table:
    // - how many players (n)
    int n;
    std::cout << "Please enter the number of players: " << std::endl;
    std::cin >> n;
    
    // if deal randomly
        // deal the cards and print probabilities
        // Ask whether any players (1->n) should be folded
        // Deal board and ask whether any players (1->n) should be folded at each step
    // if specify hand
        // Specify hand for each player in the game
        // print probabilities and ask whether any should be folded
        // Deal board and ask whether any players (1->n) should be folded at each step
}