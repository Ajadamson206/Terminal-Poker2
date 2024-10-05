#include "renderer.h"

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

#include <string>

Renderer::Renderer(Hand* handCards) {
    printf("\e[?25l]\n"); // Remove Cursor
    printf("\033[42m\n"); // Green Background

    // Terminal Settings
    tcgetattr(0, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &newt);

    this->handCards = handCards;

    renderFrame.Top = "";
    renderFrame.Middle1 = "";
    renderFrame.Middle2 = "";
    renderFrame.Middle3 = "";
    renderFrame.Bottom = "";
    renderFrame.Hold = "";
    renderFrame.WinString = "";
}

Renderer::~Renderer() {
    printf("\033[0m");
    printf("\e[?25h");
    tcsetattr(0, TCSANOW, &oldt);
    fflush(stdout);
    system("clear");
}

std::string Renderer::getSuitSymbol(char suit) {   
    return sym_map[(int)suit];
}

std::string Renderer::getValueSymbol(char value) {
    switch (value)
    {
    case 0:
        return "A";
        break;
    case 10:
        return "J";
        break;
    case 11:
        return "Q";
        break;
    case 12:
        return "K";
    default:
        return std::to_string(value + 1);
    }
}

void Renderer::updateFrames(int winAmount) {
    // Display all of the cards in the hand
    // Set Background to Green

    renderFrame.Top.clear();
    renderFrame.Middle1.clear();
    renderFrame.Middle2.clear();
    renderFrame.Middle3.clear();
    renderFrame.Bottom.clear();
    renderFrame.Hold.clear();
    renderFrame.WinString.clear();

    #ifndef DEBUG
        system("clear");
    #endif

    // Look at Cards
    for(int i = 0; i < HAND_SIZE; i++)
    {
        // If Card is red (Odd ones are red)
        const std::string* color = ((handCards->getCards())[i].suit & 1)? &RED : &BLACK;
        
        renderFrame.Top.append(*color);
        renderFrame.Middle1.append(*color);
        renderFrame.Middle2.append(*color);
        renderFrame.Middle3.append(*color);
        renderFrame.Bottom.append(*color);


        // Add top
        renderFrame.Top.append("┌────────┐ ");

        // Add Middle1
        renderFrame.Middle1.append("│");
        renderFrame.Middle1 += getValueSymbol(handCards->getCards()[i].value);
        renderFrame.Middle1.append((handCards->getCards()[i].value == 9)? "      │ " : "       │ ");

        // Add Middle2
        renderFrame.Middle2.append("│");
        renderFrame.Middle2.append(getSuitSymbol(handCards->getCards()[i].suit));
        renderFrame.Middle2.append("       │ ");

        // Middle3 and Bottom
        renderFrame.Middle3.append("│        │ ");
        renderFrame.Bottom.append("└────────┘ ");

    }

    renderFrame.Top.append("\n");
    renderFrame.Middle1.append("\n");
    renderFrame.Middle2.append("\n");
    renderFrame.Middle3.append("\n");
    renderFrame.Bottom.append("\n");

    // Hold Cards Render

    char replacementCards = handCards->getReplaceCards();
    for(int currentCard = 0; currentCard < 5; currentCard++) {
        renderFrame.Hold.append((replacementCards & 1)? " Discard   " : "           ");
        replacementCards >>= 1;
    }

    renderFrame.Hold.append("\n");


    // WinCode Renderer    
    if(winAmount) {
        renderFrame.WinString.append("You Won ");
        renderFrame.WinString.append(std::to_string(winAmount));
        renderFrame.WinString.append(" Points!\n");
    }
}

void Renderer::render() {
    std::cout << renderFrame.Top;
    std::cout << renderFrame.Middle1;
    std::cout << renderFrame.Middle2;
    std::cout << renderFrame.Middle3;
    std::cout << renderFrame.Middle3;
    std::cout << renderFrame.Middle3;
    std::cout << renderFrame.Bottom;
    std::cout << renderFrame.Hold;
    std::cout << renderFrame.WinString;
}

void Renderer::printWinString(char winAmount) {
    renderFrame.WinString.clear();

    if(winAmount) {
        renderFrame.WinString.append("You Won ");
        renderFrame.WinString.append(std::to_string(winAmount));
        renderFrame.WinString.append(" Points!\n");
    } else {
        renderFrame.WinString.append("Try Again\n");
    }
    
    render();
}