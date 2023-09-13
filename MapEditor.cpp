#include "MapEditor.h"
#include <ctime>  // Для использования time
#include <fstream>
#define cout std::cout<<
#define randoms(a, b) (rand() % ((b) - (a) + 1) + (a))

MapEditor::MapEditor(sf::RenderWindow& windows) : Map(windows)
{
    map.resize(WINDOW_H / BLOCK_SIZE, std::vector<int>(WINDOW_W / BLOCK_SIZE, 0));
    mapTexture.create(WINDOW_W, WINDOW_H);
    isLeftMouseButtonPressed = false;
    isRightMouseButtonPressed = false;
    loadMapFromFile();
    updateMapTexture();
}

void MapEditor::run() {
    bool tapButton = false;

    for (int i = 0; i < 5; i++) {
        buttons.push_back(Button(sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE / 2),
            sf::Vector2f(BUTTON_SIZE * i, 0),
            sf::Color(130, 78, 100, 255),
            sf::Color(255, 255, 255, 255),
            10, namesButton[i]));
    }
    buttons.push_back(Button(sf::Vector2f(BUTTON_SIZE * 3, BUTTON_SIZE / 2),
        sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE / 2+2),
        sf::Color(130, 78, 100, 255),
        sf::Color(255, 255, 255, 255),
        10, namesTypePaint[0]));
    while (window.isOpen()) {
        
        if (needClose) {
            saveMapToFile();
            needClose = false;
            saveMapToFile();
            return;
        }
        
        render();
        
    }
    

}

void MapEditor::saveMapToFile() {
    std::ofstream outFile("map.txt");

    if (outFile.is_open()) {
        for (int x = 0; x < map.size(); ++x) {
            for (int y = 0; y < map[x].size(); ++y) {
                outFile << map[x][y] << " ";
            }
            outFile << std::endl; // Переход на новую строку после каждой строки карты
        }

        outFile.close();
    }
    else {
        // Обработка ошибки открытия файла
        std::cerr << "Error: Unable to open the file." << std::endl;
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
                            needClose = true;
                            tapButton = true;
                        }
                        else if (str == "PREV") {
                            paintType--;
                            if (paintType < 0) paintType = 2;
                            tapButton = true;
                        }
                        else if (str == "NEXT") {
                            paintType++;
                            if (paintType > 2) paintType = 0;
                            cout "NEXT" << '\n';
                            tapButton = true;

                        }
                        else if (str == "CLEAR") {
                            map.clear();
                            map.resize(WINDOW_H / BLOCK_SIZE, std::vector<int>(WINDOW_W / BLOCK_SIZE, 0));
                            tapButton = true;
                        }
                        else if (str == "FILL"&&paintType!=2) {
                            for (int i = 0; i < map.size();i++) {
                                for (int j = 0; j < map[0].size(); j++) {
                                    if(map[i][j] == 0)map[i][j] = paintType+1;
                                }
                            }
                            needUpdateMap = 1;
                            tapButton = true;
                        }
                    }
                }
                if (!tapButton) {
                    isLeftMouseButtonPressed = true;
                }
            }
            else if (event.mouseButton.button == sf::Mouse::Right) {
                needUpdateMap = 1;
                isRightMouseButtonPressed = true;
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                isLeftMouseButtonPressed = false;
                tapButton = false;
            }
            else if (event.mouseButton.button == sf::Mouse::Right) {
                isRightMouseButtonPressed = false;
            }
        }
    }

    if (isLeftMouseButtonPressed || isRightMouseButtonPressed) {
        
        // Координаты мыши и преобразование их в индексы матрицы карты
        int y = sf::Mouse::getPosition(window).x / BLOCK_SIZE;
        int x = sf::Mouse::getPosition(window).y / BLOCK_SIZE;
        if (paintType == 2) {
            if (y >= 0 && y < map[0].size() && x >= 0 && x < map.size()) {
                explosion(vt(x, y), 10);
            }
            
        }
        
        else if (y >= 0 && y < map[0].size() && x >= 0 && x < map.size()) {
            map[x][y] = (isLeftMouseButtonPressed) ? paintType + 1 : 0;
            
        }
        needUpdateMap = 1;
    }
}


void MapEditor::renderWithoutTexture() {
    bool hasBlocksReachedBottom = false;

    for (int x = map.size() - 1; x > 0; --x) {
        for (int y = 0; y < map[x].size(); ++y) {
            if (map[x][y] == 2) {

            }
            else if (map[x][y] > 0 && x < map.size() - 1 && map[x + 1][y] == 0) {
                map[x + 1][y] = map[x][y];
                map[x][y] = 0;
                hasBlocksReachedBottom = true;
            }
        }
    }

    if (hasBlocksReachedBottom) {
        for (int x = map.size() - 1; x > 0; --x) {
            for (int y = 0; y < map[x].size(); ++y) {
                if (map[x][y] == 2) {
                    // Çäåñü òàêæå ìîæåò ïîòðåáîâàòüñÿ îáðàáîòêà äâèæåíèÿ ïåñêà âëåâî èëè âïðàâî,
                    // åñëè ñîñåäíèå êëåòêè çàíÿòû.
                }
                else if (map[x][y] > 0 && x < map.size() - 1) {
                    if (y > 0 && map[x + 1][y] > 0 && map[x + 1][y - 1] == 0) {
                        map[x + 1][y - 1] = map[x][y];
                        map[x][y] = 0;
                    }
                    else if (y < map[x].size() - 1 && map[x + 1][y] > 0 && map[x + 1][y + 1] == 0) {
                        map[x + 1][y + 1] = map[x][y];
                        map[x][y] = 0;
                    }
                    else if (map[x + 1][y] == 0) {
                        map[x + 1][y] = map[x][y];
                        map[x][y] = 0;
                    }
                }
            }
        }
    }


    for (int x = 0; x < map.size(); ++x) {
        for (int y = 0; y < map[x].size(); ++y) {
            int value = map[x][y];
            if (value >= 1 && value <= 9) {
                sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                block.setPosition(y * BLOCK_SIZE, x * BLOCK_SIZE);
                block.setFillColor(colors[value - 1]);
                window.draw(block);
            }
        }
    }
    buttons[5].setText(namesTypePaint[paintType]);
    for (auto& but : buttons) {
        but.render(window);
    }

}
void MapEditor::render() {
    window.clear();

    //drawMap();
    renderWithoutTexture();
    for (auto& b : buttons) {
        b.render(window);
    }
    update();
    window.display();
    //std::cout << "XXXXXXXXXXXXX" << '\n';
}
void MapEditor::update() {
    handleEvents();
}