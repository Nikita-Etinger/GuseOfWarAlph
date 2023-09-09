#include <iostream>
#include "Game.h"
#include <ctime>

int main()
{
    srand(time(NULL));
    Game game;
    game.run();
    std::cout << "Hello World!\n";



}

