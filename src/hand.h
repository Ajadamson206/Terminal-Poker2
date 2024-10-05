#ifndef HAND
#define HAND

#include "deck.h"
#include <stdlib.h>

#define HAND_SIZE 5

#define FLUSH (1<<0)
#define STRAIGHT (1<<1)
#define ROYAL (1<<2)
#define PAIR_2_KIND (1<<3)
#define PAIR_3_KIND (1<<4)
#define PAIR_4_KIND (1<<5)
#define TWO_PAIR_2_KIND (1<<6)
#define PAIR_5_KIND (1<<7)


struct handcard{
    char value;
    char suit;
};

using HandCard = handcard;

class Hand {
public:

    Hand(Deck* currentDeck);

    ~Hand();

    char checkWinnings();
    void selectCardToReplace(char card);
    HandCard* getCards();
    char getReplaceCards();
    void replaceHandCards();

private:
    Deck* drawingDeck;
    HandCard currentCards[HAND_SIZE];
    int maxReplace;

    char cardsToBeReplaced;

    void sort(char array[], int arrayLength);

};


#endif