#include "deck.h"
#include "renderer.h"
#include "hand.h"
#include "game.h"

int main() {
    Game mainGame;

    int exitCode = mainGame.startGame();

    return exitCode;
}