# Poker Probability Calculator

Built this in order to better understand how probabilities of a hand winning are generated live during cash games and tournaments. This is specific to Texas Holdem.

## How it Works
1. Storing hands and table information:
   Structured/Composite classes are made for the cards, hand, player and table. This allows me to create a definition header file that is imported into the lowest level and can be accessed by each class. The suits and values of the cards are represented using enums which makes it easy to convert them to symbols and integers for printing and other functions.
2. Dealing Cards:
   A Mersenne Twister pseudo-random generator is used to shuffle the deck. Since this is done with a different seed everytime and is also executed when the table is initialized, every run of the program is pseudo-random.
3. TwoPlusTwo table generation:
   Running "make table" creates the HandRanks.dat file which can be queried to get the strength of a hand.  
4. Calculating the probability of a hand winning:
   Given n number of players, the code iterates through all the possibilities of what the board (the shared cards) could be and checks which player wins each possibility. Keeping a count of this allows us to generate the probability of each player winning.

## Running the program
Prior to running the program, the table needs to be generated using "make table".

There are two possible modes:
1. Random hands
   This can be run using "make". It will prompt you for the number of players in the game. It will then generate hands for each of the players and generate probabilities for each stage of the game (pre-flop, flop, turn and river). You can also fold any players you like at any stage of the game. This will change the winning probabilities.
2. Specific hands
   This can be run using "make specific". You will need to enter the number of players and the hands for each of the players. You can also enter cards for the board if you wish. It will then generate probabilities for this and also allow you to simulate the rest of the game similar to option 1.

## Extensions

