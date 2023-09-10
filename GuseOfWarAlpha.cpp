#include <iostream>
#include "Game.h"
#include <ctime>
#include <SFML/Graphics.hpp>
int main()
{
    srand(time(NULL));
    Game game;
    game.run();
    if (0) {
        // Создаем окно
        sf::RenderWindow window(sf::VideoMode(800, 600), "Загрузка текстуры");

        // Создаем объект текстуры
        sf::Texture texture;

        // Загружаем текстуру из файла
        if (!texture.loadFromFile("guse.png"))
        {
            // Если не удалось загрузить текстуру, выводим сообщение об ошибке
            std::cout << "Ошибка при загрузке текстуры" << std::endl;
            return 1; // Завершаем программу с ошибкой
        }

        // Создаем спрайт и устанавливаем текстуру для него
        sf::Sprite sprite(texture);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(sprite); // Рисуем спрайт с текстурой
            window.display();
        }
    }
}

