#ifndef RENDERER
#define RENDERER

#include <string>
#include <iostream>
#include <termios.h>

#include "hand.h"
#include "deck.h"

const std::string RED = "\033[91m";
const std::string BLACK = "\033[30m";
const std::string sym_map[4] = {"♦", "♠", "♥", "♣"};

struct frame {
    std::string Top;
    std::string Middle1;
    std::string Middle2;
    std::string Middle3;
    std::string Bottom;
    std::string Hold;
    std::string WinString;
};

using Frame = frame;

class Renderer {
public:
    Renderer(Hand* handCards);

    ~Renderer();

    void updateFrames(int winAmount);
    void render();
    void printWinString(char winAmount);

private:
    struct termios oldt, newt;
    Hand* handCards;
    Frame renderFrame;

    std::string getValueSymbol(char value);
    std::string getSuitSymbol(char suit);


};

#endif