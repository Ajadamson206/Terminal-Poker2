#include "hand.h"
#include "deck.h"

Hand::Hand(Deck* currentDeck) {
    drawingDeck = currentDeck;

    maxReplace = 3;
    
    for(int i = 0; i < HAND_SIZE; i++) {
        char currentCard = drawingDeck->draw();
        currentCards[i].suit = currentCard / 13;
        currentCards[i].value = currentCard % 13;

        if(currentCards[i].value == 0)
            maxReplace = 4;
    }


}

char Hand::checkWinnings() {
    char winningType = 0;
    char handValues[DECK_SIZE] = {0};


    // Check for a flush
    bool flush = true;
    for(int i = 0; i < HAND_SIZE - 1; i++) {
        handValues[i] = currentCards[i].value;
        if(currentCards[i].suit != currentCards[i + 1].suit)
            flush = false;
    }

    if(flush)
        winningType |= FLUSH;

    // Sort the hand values
    sort(handValues, HAND_SIZE);

    char binaryPairs = 0;
    int numStraight = 0;

    for(int i = 0; i < HAND_SIZE - 1; i++) {
        if(handValues[i] == handValues[i+1]) // Check for a pair
            binaryPairs++;
        else if(handValues[i] + 1 == handValues[i+1]) // Check for a straight
            numStraight++;
        
        binaryPairs <<= 1;
    }

    if(numStraight == HAND_SIZE - 1) {
        return winningType |= (handValues[HAND_SIZE - 1] == 12)? ROYAL | STRAIGHT : STRAIGHT;
    }

    switch(binaryPairs) {
        case 0:
            break;
        case 1:  // 0001
        case 2:  // 0010
        case 4:  // 0100
        case 8:  // 1000
            return winningType |= PAIR_2_KIND; // Two of a kind
        case 5:  // 0101
        case 9:  // 1001
        case 10: // 1010
            return winningType |= TWO_PAIR_2_KIND; // 2x Two of a kind
        case 3:  // 0011
        case 6:  // 0110
        case 12: // 1100
            return winningType |= PAIR_3_KIND; // Three of a kind
        case 7:  // 0111
        case 14: // 1110
            return winningType |= PAIR_4_KIND; // Four of A Kind
        case 11:  // 1011
        case 13:  // 1101
            return winningType |= PAIR_2_KIND | PAIR_3_KIND; // Full House
    }

    return winningType;

}

void Hand::sort(char array[], int arrayLength) {
    for(int i = 0; i < arrayLength - 1; i++) {
        int min = i;
        
        for (int j = i + 1; j < arrayLength; j++) {
            if(array[j] < array[min])
                min = j;
        }

        char temp = array[i];
        array[i] = array[min];
        array[min] = temp;
    }
}

HandCard* Hand::getCards() {
    return &currentCards[0];
}

void Hand::selectCardToReplace(char card) {
    cardsToBeReplaced & (1<<card)? maxReplace++ : maxReplace--; 
    
    if(maxReplace < 0)
        maxReplace++;
    else 
        cardsToBeReplaced ^= (1 << card);
}

char Hand::getReplaceCards() {
    return cardsToBeReplaced;
}

void Hand::replaceHandCards() {
    maxReplace = 3;

    for(int i = 0; i < HAND_SIZE; i++) {
        char currentCard = drawingDeck->draw();
        currentCards[i].suit = currentCard / 13;
        currentCards[i].value = currentCard % 13;

        if(currentCards[i].value == 0)
            maxReplace = 4;
    }

    cardsToBeReplaced = 0;
}