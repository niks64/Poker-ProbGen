/*
AUTHORS:

   Paul Senzee (perfect hash optimization)
   http://www.senzee5.com/2006/06/some-perfect-hash.html

   Kevin Suffecool (original C code)
   http://www.suffecool.net/poker/evaluator.html
   
   James Devlin (minor code modes: Visual Studio support, RNG, etc.)
   http://www.codingthewheel.com/archives/poker-hand-evaluator-roundup
*/

// HandRankSetup.cpp : Sets up the HandRank File for VERY fast Lookups
// by Ray Wotton and the 2+2 list  My code is GPL, use it as you like

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <algorithm>
#include "arrays.h"

const char HandRanks[][16] = {"BAD!!","High Card","Pair","Two Pair","Three of a Kind","Straight","Flush","Full House","Four of a Kind","Straight Flush"};

__int64_t IDs[612978];
int HR[32487834];   

int numIDs = 1;
int numcards = 0;
int maxHR = 0;
__int64_t maxID = 0;

unsigned find_fast(unsigned u)
{
    unsigned a, b, r;
    u += 0xe91aaa35;
    u ^= u >> 16;
    u += u << 8;
    u ^= u >> 4;
    b  = (u >> 8) & 0x1ff;
    a  = (u + (u << 2)) >> 19;
    r  = a ^ hash_adjust[b];
    return r;
}

int eval_5hand_fast(int c1, int c2, int c3, int c4, int c5)
{
    int q = (c1 | c2 | c3 | c4 | c5) >> 16;
    short s;
    if (c1 & c2 & c3 & c4 & c5 & 0xf000) return flushes[q]; // check for flushes and straight flushes
    if ((s = unique5[q]))                return s;          // check for straights and high card hands
    return hash_values[find_fast((c1 & 0xff) * (c2 & 0xff) * (c3 & 0xff) * (c4 & 0xff) * (c5 & 0xff))];
}

short
eval_7hand( int *hand )
{
    int i, j, q, best = 9999, subhand[5];

	for ( i = 0; i < 21; i++ )
	{
		q = eval_5hand_fast(hand[perm7[i][0]], hand[perm7[i][1]], hand[perm7[i][2]], hand[perm7[i][3]], hand[perm7[i][4]]);
		if ( q < best )
			best = q;
	}
	return( best );
}

__int64_t MakeID(__int64_t IDin, int newcard)  // adding a new card to this ID
{
	__int64_t ID = 0;
	int suitcount[4 + 1];
	int rankcount[13 + 1];
	int workcards[8];  // intentially keeping one as a 0 end
	int cardnum;
	int getout = 0;

	memset(workcards, 0, sizeof(workcards));
	memset(rankcount, 0, sizeof(rankcount));
	memset(suitcount, 0, sizeof(suitcount));

	// can't have more than 6 cards!
	for (cardnum = 0; cardnum < 6; cardnum++)
	{  
		workcards[cardnum + 1] =  (int) ((IDin >> (8 * cardnum)) & 0xff);  // leave the 0 hole for new card
	}

	// my cards are 2c = 1, 2d = 2  ... As = 52
	newcard--;  // make 0 based!

	workcards[0] = (((newcard >> 2) + 1) << 4) + (newcard & 3) + 1;  // add next card formats card to rrrr00ss

	for (numcards = 0; workcards[numcards]; numcards++)
	{
		suitcount[workcards[numcards] & 0xf]++;           // need to see if suit is significant
		rankcount[(workcards[numcards] >> 4) & 0xf]++;	  // and rank to be sure we don't have 4!
		if (numcards)
		{
			if (workcards[0] == workcards[numcards]) {	  // can't have the same card twice
				getout = 1;								  // if so need to get out after counting numcards
			}
		}
	}

	if (getout) {
		return 0;     // duplicated another card (ignore this one)    
	}


	int needsuited = numcards - 2;	   // for suit to be significant - need to have n-2 of same suit

	if (numcards > 4) {  
		for (int rank = 1; rank < 14; rank++) {
			if (rankcount[rank] > 4) {  // if I have more than 4 of a rank then I shouldn't do this one!!
				return 0;   // can't have more than 4 of a rank so return an ID that can't be!
			}
		}
	}

	// However in the ID process I prefered that
	// 2s = 0x21, 3s = 0x31,.... Kc = 0xD4, Ac = 0xE4
	// This allows me to sort in Rank then Suit order

	// if we don't have at least 2 cards of the same suit for 4, we make this card suit 0.

	if (needsuited > 1) { 
		for (cardnum = 0; cardnum < numcards; cardnum++) {  // for each card
			if (suitcount[workcards[cardnum] & 0xf] < needsuited) {	// check suitcount to the number I need to have suits significant
				workcards[cardnum] &= 0xf0;   // if not enough - 0 out the suit - now this suit would be a 0 vs 1-4
			}
		}
	}

	// Sort Using XOR.  Network for N=7, using Bose-Nelson Algorithm: Thanks to the thread!
#define SWAP(I,J) {if (workcards[I] < workcards[J]) {workcards[I]^=workcards[J]; workcards[J]^=workcards[I]; workcards[I]^=workcards[J];}}		

	SWAP(0, 4);		
	SWAP(1, 5);		
	SWAP(2, 6);		
	SWAP(0, 2);		
	SWAP(1, 3);		
	SWAP(4, 6);		
	SWAP(2, 4);		
	SWAP(3, 5);		
	SWAP(0, 1);		
	SWAP(2, 3);		
	SWAP(4, 5);		
	SWAP(1, 4);		
	SWAP(3, 6);		
	SWAP(1, 2);		
	SWAP(3, 4);		
	SWAP(5, 6);	

	// long winded way to put the pieces into a __int64_t 
	// cards in bytes --66554433221100	 
	// the resulting ID is a 64 bit value with each card represented by 8 bits.
	ID =  (__int64_t) workcards[0] +
		((__int64_t) workcards[1] << 8) +
		((__int64_t) workcards[2] << 16) + 
		((__int64_t) workcards[3] << 24) +
		((__int64_t) workcards[4] << 32) +
		((__int64_t) workcards[5] << 40) +
		((__int64_t) workcards[6] << 48);    

	return ID;
}

int SaveID(__int64_t ID) 
{
	if (ID == 0) return 0;   // don't use up a record for a 0!

	if (ID >= maxID) {           // take care of the most likely first goes on the end...
		if (ID > maxID) {        // greater than create new else it was the last one!
			IDs[numIDs++] = ID;  // add the new ID
			maxID = ID;
		}
		return numIDs - 1;
	}

	// find the slot I will find it (by a pseudo bsearch algorithm)
	int low = 0;
	int high = numIDs - 1;
	__int64_t testval;
	int holdtest;

	while (high - low > 1) {
		holdtest = (high + low + 1) / 2;
		testval = IDs[holdtest] - ID;
		if (testval > 0) high = holdtest;
		else if (testval < 0) low = holdtest;
		else return holdtest;   // got it!!
	}
	// I guess it couldn't be found so must be added to the current location (high)
	// make space...  // don't expect this much!
	memmove(&IDs[high + 1], &IDs[high], (numIDs - high) * sizeof(IDs[0]));  

	IDs[high] = ID;   // do the insert into the hole created
	numIDs++;        
	return high;
}

int DoEval(__int64_t IDin)
{
	// I guess I have some explaining to do here...  I used the Cactus Kevs Eval ref http://www.suffecool.net/poker/evaluator.html
	// I Love the pokersource for speed, but I needed to do some tweaking to get it my way
	// and Cactus Kevs stuff was easy to tweak ;-)  
	int handrank = 0;
	int cardnum;
	int workcard;
	int rank;
	int suit;
	int mainsuit = 20;      // just something that will never hit...  need to eliminate the main suit from the iterator
	//int suititerator = 0;
	int suititerator = 1; // changed as per Ray Wotton's comment at http://archives1.twoplustwo.com/showflat.php?Cat=0&Number=8513906&page=0&fpart=18&vc=1
	int holdrank;
	int workcards[8];  // intentially keeping one as a 0 end
	int holdcards[8];
	int numevalcards = 0;

	// See Cactus Kevs page for explainations for this type of stuff...
	const int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41 };

	memset(workcards, 0, sizeof(workcards));
	memset(holdcards, 0, sizeof(holdcards));

	if (IDin)
	{	 // if I have a good ID then do it...
		for (cardnum = 0; cardnum < 7; cardnum++)
		{  // convert all 7 cards (0s are ok)
			holdcards[cardnum] =  (int) ((IDin >> (8 * cardnum)) & 0xff); 
			if (holdcards[cardnum] == 0) break;	// once I hit a 0 I know I am done
			numevalcards++;						// if not 0 then count the card
			if ((suit = holdcards[cardnum] & 0xf)) {	// find out what suit (if any) was significant
				mainsuit = suit;					// and remember it
			}
		}


		for (cardnum = 0; cardnum < numevalcards; cardnum++)
		{  
			// just have numcards...
			workcard = holdcards[cardnum];

			// convert to cactus kevs way!!  ref http://www.suffecool.net/poker/evaluator.html
			//   +--------+--------+--------+--------+
			//   |xxxbbbbb|bbbbbbbb|cdhsrrrr|xxpppppp|
			//   +--------+--------+--------+--------+
			//   p = prime number of rank (deuce=2,trey=3,four=5,five=7,...,ace=41)
			//   r = rank of card (deuce=0,trey=1,four=2,five=3,...,ace=12)
			//   cdhs = suit of card
			//   b = bit turned on depending on rank of card

			rank = (workcard >> 4) - 1;	 // my rank is top 4 bits 1-13 so convert
			suit = workcard & 0xf;  // my suit is bottom 4 bits 1-4, order is different, but who cares?  
			if (suit == 0) {		// if suit wasn't significant though...
				suit = suititerator++;   // Cactus Kev needs a suit!
				if (suititerator == 5)	 // loop through available suits
					suititerator = 1;
				if (suit == mainsuit) {   // if it was the sigificant suit...  Don't want extras!!
					suit = suititerator++;    // skip it
					if (suititerator == 5)	  // roll 1-4
						suititerator = 1;
				}
			}
			// now make Cactus Kev's Card
			workcards[cardnum] = primes[rank] | (rank << 8) | (1 << (suit + 11)) | (1 << (16 + rank));
		}

		// James Devlin: replaced all calls to Cactus Kev's eval_5cards with calls to
		// Senzee's improved eval_5hand_fast

		switch (numevalcards) {  // run Cactus Keys routines

			case 5 :  holdrank = eval_5hand_fast(workcards[0],workcards[1],workcards[2],workcards[3],workcards[4]);
				break;
				// if 6 cards I would like to find HandRank for them 
				// Cactus Key is 1 = highest - 7362 lowest I need to get the min for the permutations
			case 6 :  holdrank = eval_5hand_fast(workcards[0],workcards[1],workcards[2],workcards[3],workcards[4]);
				holdrank = std::min(holdrank, eval_5hand_fast(workcards[0],workcards[1],workcards[2],workcards[3],workcards[5]));
				holdrank = std::min(holdrank, eval_5hand_fast(workcards[0],workcards[1],workcards[2],workcards[4],workcards[5]));
				holdrank = std::min(holdrank, eval_5hand_fast(workcards[0],workcards[1],workcards[3],workcards[4],workcards[5]));
				holdrank = std::min(holdrank, eval_5hand_fast(workcards[0],workcards[2],workcards[3],workcards[4],workcards[5]));
				holdrank = std::min(holdrank, eval_5hand_fast(workcards[1],workcards[2],workcards[3],workcards[4],workcards[5]));
				break;
			case 7 : holdrank = eval_7hand(workcards);  
				break;
			default : // problem!!  shouldn't hit this... 
				printf("    Problem with numcards = %d!!\n", numcards);
				break;
		}

		// I would like to change the format of Catus Kev's ret value to:
		// hhhhrrrrrrrrrrrr   hhhh = 1 high card -> 9 straight flush
		//                    r..r = rank within the above	1 to max of 2861
		handrank = 7463 - holdrank;  // now the worst hand = 1

		if      (handrank < 1278) handrank = handrank -    0 + 4096 * 1;  // 1277 high card
		else if (handrank < 4138) handrank = handrank - 1277 + 4096 * 2;  // 2860 one pair
		else if (handrank < 4996) handrank = handrank - 4137 + 4096 * 3;  //  858 two pair
		else if (handrank < 5854) handrank = handrank - 4995 + 4096 * 4;  //  858 three-kind
		else if (handrank < 5864) handrank = handrank - 5853 + 4096 * 5;  //   10 straights
		else if (handrank < 7141) handrank = handrank - 5863 + 4096 * 6;  // 1277 flushes
		else if (handrank < 7297) handrank = handrank - 7140 + 4096 * 7;  //  156 full house
		else if (handrank < 7453) handrank = handrank - 7296 + 4096 * 8;  //  156 four-kind
		else                      handrank = handrank - 7452 + 4096 * 9;  //   10 straight-flushes

	}
	return handrank;  // now a handrank that I like
}


int main(int argc, char* argv[])
{
	int IDslot, card = 0, count = 0;
	__int64_t ID;

	// Store the count of each type of hand (One Pair, Flush, etc)
	int handTypeSum[10];

	// Clear our arrays
	memset(handTypeSum, 0, sizeof(handTypeSum));
	memset(IDs, 0, sizeof(IDs));
	memset(HR, 0, sizeof(HR));


	// step through the ID array - always shifting the current ID and adding 52 cards to the end of the array.
	// when I am at 7 cards put the Hand Rank in!!  
	// stepping through the ID array is perfect!!

	int IDnum;
	int holdid;

	printf("\nGetting Card IDs!\n");

	// Jmd: Okay, this loop is going to fill up the IDs[] array which has 612,967 slots.
	// as this loops through and find new combinations it adds them to the end
	// I need this list to be stable when I set the handranks (next set)  (I do the insertion sort on new IDs these)
	// so I had to get the IDs first and then set the handranks
	for (IDnum = 0; IDs[IDnum] || IDnum == 0; IDnum++) 
	{   
		// start at 1 so I have a zero catching entry (just in case)
		for (card = 1; card < 53; card++)
		{	
			// the ids above contain cards upto the current card.  Now add a new card 
			ID = MakeID(IDs[IDnum], card);   // get the new ID for it
			if (numcards < 7) holdid = SaveID(ID);   // and save it in the list if I am not on the 7th card
		}
		printf("\rID - %d", IDnum);	  // just to show the progress -- this will count up to  612976
	}

	printf("\nSetting HandRanks!\n");

	// this is as above, but will not be adding anything to the ID list, so it is stable
	for (IDnum = 0; IDs[IDnum] || IDnum == 0; IDnum++)
	{  
		// start at 1 so I have a zero catching entry (just in case)
		for (card = 1; card < 53; card++) 
		{
			ID = MakeID(IDs[IDnum], card);
			
			if (numcards < 7)
			{
				IDslot = SaveID(ID) * 53 + 53;  // when in the index mode (< 7 cards) get the id to save
			}
			else
			{
				IDslot = DoEval(ID);   // if I am at the 7th card, get the equivalence class ("hand rank") to save
			}

			maxHR = IDnum * 53 + card + 53;	// find where to put it 
			HR[maxHR] = IDslot;				// and save the pointer to the next card or the handrank
		}

		if (numcards == 6 || numcards == 7)
		{  
			// an extra, If you want to know what the handrank when there is 5 or 6 cards
			// you can just do HR[u3] or HR[u4] from below code for Handrank of the 5 or 6 card hand
			HR[IDnum * 53 + 53] = DoEval(IDs[IDnum]);  // this puts the above handrank into the array  
		}

		printf("\rID - %d", IDnum);	  // just to show the progress -- this will count up to  612976 same as above!
	}

	printf("\nNumber IDs = %d\nmaxHR = %d\n", numIDs, maxHR);  // for warm fuzzys

	// another algorithm right off the thread

	int c0, c1, c2, c3, c4, c5, c6;
	int u0, u1, u2, u3, u4, u5;

	for (c0 = 1; c0 < 53; c0++) {
		u0 = HR[53+c0];
		for (c1 = c0+1; c1 < 53; c1++) {
			u1 = HR[u0+c1];
			for (c2 = c1+1; c2 < 53; c2++) {
				u2 = HR[u1+c2];
				for (c3 = c2+1; c3 < 53; c3++) {
					u3 = HR[u2+c3];
					for (c4 = c3+1; c4 < 53; c4++) {
						u4 = HR[u3+c4];
						for (c5 = c4+1; c5 < 53; c5++) {
							u5 = HR[u4+c5];
							for (c6 = c5+1; c6 < 53; c6++) {
								handTypeSum[HR[u5+c6] >> 12]++;
								count++;
							}
						}
					}
				}
			}
		}
	}

	// output the array now that I have it!!
	FILE * fout = fopen("./TableGeneration/HandRanks.dat", "wb");
	if (!fout) {
		printf("Problem creating the Output File!\n");
		return 1;
	}
	fwrite(HR, sizeof(HR), 1, fout);  // big write, but quick

	fclose(fout);

	return 0;
}

///////////////////////////////// end code!!