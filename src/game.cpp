#include "renderer.h"
#include "deck.h"
#include "hand.h"
#include "game.h"

#include <unistd.h>

Game::Game() {
    mainDeck = new Deck();
    handCards = new Hand(mainDeck);
    renderer = new Renderer(handCards);

    gameRunning = true;

    winMapping[0] = WIN_LOSS;
    winMapping[FLUSH] = WIN_FLUSH;
    winMapping[STRAIGHT] = WIN_STRAIGHT;
    winMapping[STRAIGHT | FLUSH] = WIN_STRAIGHT_FLUSH;
    winMapping[ROYAL | STRAIGHT | FLUSH] = WIN_ROYAL_FLUSH;
    winMapping[PAIR_2_KIND] = WIN_2_KIND;
    winMapping[PAIR_3_KIND] = WIN_3_KIND;
    winMapping[PAIR_2_KIND | PAIR_3_KIND] = WIN_FULL_HOUSE;
    winMapping[PAIR_4_KIND] = WIN_4_KIND;
    winMapping[TWO_PAIR_2_KIND] = WIN_2_KIND + WIN_2_KIND;
    winMapping[PAIR_5_KIND] = WIN_5_KIND;

}

Game::~Game() {
    delete renderer;
    //delete handCards;
    //delete mainDeck;
}

int Game::getWinAmount(int winCode) {
    return winMapping[winCode];
}

int Game::startGame() {
    int winCode = 0;

    while(gameRunning) {
        // Render the chosen cards
        renderer->updateFrames(winCode);
        renderer->render();

        // Get the user input (1, 2, 3, 4, 5, Space, ESC)
        int userInput = getchar();
        switch (userInput)
        {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
                handCards->selectCardToReplace(userInput - 49);
                break;

            case ' ':
                winCode = handCards->checkWinnings();
                renderer->printWinString(getWinAmount(winCode));
                mainDeck->shuffleDeck();
                handCards->replaceHandCards();
                break;

            case 27:
                // End Game
                gameRunning = false;
                return 0;

            default:
                break;
        }





    }

    return 1;
}