#include "deck.h"
#include <time.h>
#include <stdlib.h>

Deck::Deck() {
    shuffleDeck();
}

Deck::~Deck() {

}

char Deck::draw() {
    return cardDeck[currentDeckPosition++];
}

void Deck::shuffleDeck() {
    struct timespec tv;
    timespec_get(&tv, TIME_UTC);
    srand48(tv.tv_nsec);


    size_t i;
    for (i = DECK_SIZE - 1; i > 0; i--) {
        size_t j = (unsigned int) (drand48()*(i+1));
        char t = cardDeck[j];
        cardDeck[j] = cardDeck[i];
        cardDeck[i] = t;
    }
}