#include "MapEditor.h"

#define randoms(a, b) (rand() % ((b) - (a) + 1) + (a))


MapEditor::MapEditor(sf::RenderWindow& windows) : Map(windows)
{
    map.resize(WINDOW_H / BLOCK_SIZE, std::vector<int>(WINDOW_W / BLOCK_SIZE, 0));
    isLeftMouseButtonPressed = false;
    isRightMouseButtonPressed = false;
    colors[0] = sf::Color::Yellow;
    colors[1] = sf::Color::Green;
    colors[2] = sf::Color::Red;
    colors[3] = sf::Color::Yellow;


    
   
}

void MapEditor::run() {
    loadMapFromFile();
    for (int i = 0; i < 4; i++) {
        buttons.push_back(Button(sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE / 2),
            sf::Vector2f(BUTTON_SIZE*i, 0),
            sf::Color::Color(130, 78, 100, 255),
            sf::Color::Color(255, 255, 255, 255),
            10, namesButton[i]));
    }
    buttons.push_back(Button(sf::Vector2f(BUTTON_SIZE*3, BUTTON_SIZE / 2),
        sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE / 2),
        sf::Color::Color(130, 78, 100, 255),
        sf::Color::Color(255, 255, 255, 255),
        10, namesTypePaint[0]));
    //srand(time(NULL));
    while (window.isOpen()) {
        handleEvents();
        if (needClose) {
            saveMapToFile();
            needClose = 0;
            return;
        }
        update();
        render();
    }
    saveMapToFile();
}
void MapEditor::colorMenu() {

}
void MapEditor::saveMapToFile() {
    std::ofstream outFile("map.txt");

    if (outFile.is_open()) {
        for (int y = 0; y < map.size(); ++y) {
            for (int x = 0; x < map[y].size(); ++x) {
                outFile << map[y][x] << " ";
            }
            outFile << std::endl; // Переход на новую строку после каждой строки карты
        }

        outFile.close();
    }
    else {
        // Обработка ошибки открытия файла
    }
}
void MapEditor::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        else if (event.type == sf::Event::MouseButtonPressed) {
            
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f localPosition(event.mouseButton.x, event.mouseButton.y);
                for (auto& x : buttons) {

                    if (x.getRectangle().getGlobalBounds().contains(localPosition)) {
                        std::string str = x.getString();
                        if (str == "SAVE") {
                            needClose = 1;
                            tapButton = 1;
                        }
                        else if (str == "PREV") {
                            paintType--;
                            if (paintType < 0) paintType = 1; 
                            tapButton = 1;
                        }
                        else if (str == "NEXT") {
                            paintType++;
                            if (paintType > 1) paintType = 0;
                            tapButton = 1;
                        }
                        else if (str == "CLEAR") {
                            map.clear();
                            map.resize(WINDOW_H / BLOCK_SIZE, std::vector<int>(WINDOW_W / BLOCK_SIZE, 0));
                            tapButton = 1;
                        }

                    }
                }
                if (!tapButton) {
                    isLeftMouseButtonPressed = true;
                }


                
            }
            else if (event.mouseButton.button == sf::Mouse::Right) {
                isRightMouseButtonPressed = true;
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                isLeftMouseButtonPressed = false;
                tapButton = 0;
            }
            else if (event.mouseButton.button == sf::Mouse::Right) {
                isRightMouseButtonPressed = false;
            }
        }

    }

    if (isLeftMouseButtonPressed || isRightMouseButtonPressed) {
        //координаты мыши и преобразование их в индексы матрицы карты
        int x = sf::Mouse::getPosition(window).x / BLOCK_SIZE;
        int y = sf::Mouse::getPosition(window).y / BLOCK_SIZE;

        // Установите значение 1 или 0 в выбранной клетке
        if (x >= 0 && x < map[0].size() && y >= 0 && y < map.size()) {
            map[y][x] = (isLeftMouseButtonPressed) ?paintType+1 : 0;
        }
    }
}

void MapEditor::update() {
    bool hasBlocksReachedBottom = false;

    for (int y = map.size() - 1; y > 0; --y) {
        for (int x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == 2) {
            }
            else if (map[y][x] > 0 && y < map.size() - 1 && map[y + 1][x] == 0) {
                map[y + 1][x] = map[y][x];
                map[y][x] = 0;
                hasBlocksReachedBottom = true;
            }
        }
    }

    if (hasBlocksReachedBottom) {
        for (int y = map.size() - 1; y > 0; --y) {
            for (int x = 0; x < map[y].size(); ++x) {
                if (map[y][x] == 2) {
                }
                else if (map[y][x] > 0 && y < map.size() - 1) {
                    if (x > 0 && map[y + 1][x] > 0 && map[y + 1][x - 1] == 0) {
                        map[y + 1][x - 1] = map[y][x];
                        map[y][x] = 0;
                    }
                    else if (x < map[y].size() - 1 && map[y + 1][x] > 0 && map[y + 1][x + 1] == 0) {
                        map[y + 1][x + 1] = map[y][x];
                        map[y][x] = 0;
                    }
                    else if (map[y + 1][x] == 0) {
                        map[y + 1][x] = map[y][x];
                        map[y][x] = 0;
                    }
                }
            }
        }
    }
}


void MapEditor::render() {
    window.clear();
    buttons[4].setText(namesTypePaint[paintType]);
    for (auto & but : buttons) {
        but.render(window);
    }
    
    // Отрисовка заполненных клеток
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            int value = map[y][x];
            if (value >= 1 && value <= 4) {
                sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                block.setPosition(x * BLOCK_SIZE, y * BLOCK_SIZE);
                block.setFillColor(colors[value - 1]); 
                window.draw(block);
            }
        }
    }

    window.display();
}