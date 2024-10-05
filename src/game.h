#ifndef GAME
#define GAME

#include <map>

#include "renderer.h"
#include "deck.h"
#include "hand.h"

#define WIN_5_KIND 350
#define WIN_ROYAL_FLUSH 250
#define WIN_STRAIGHT_FLUSH 50
#define WIN_4_KIND 30
#define WIN_FULL_HOUSE 10
#define WIN_FLUSH 8
#define WIN_STRAIGHT 6
#define WIN_3_KIND 5
#define WIN_2_KIND 2
#define WIN_LOSS -1

class Game {
public:
    Game();

    ~Game();

    int startGame();
    int getWinAmount(int winCode);

private:

    std::map<int, int> winMapping;
    Hand* handCards;
    Deck* mainDeck;
    Renderer* renderer;
    bool gameRunning;
};

#endif