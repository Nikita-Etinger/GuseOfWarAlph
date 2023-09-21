#include <iostream>
#include "Game.h"
#include <ctime>
#include <SFML/Graphics.hpp>
sf::Texture Particles::vapeTexture;
sf::Texture Particles::explosionTexture;
int main()
{

    srand(time(NULL));
    Game game;
    game.run();

}

