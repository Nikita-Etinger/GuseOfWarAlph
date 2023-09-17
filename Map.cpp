#include "Map.h"


Map::Map(sf::RenderWindow& windowS) :window(windowS),needClose(false)
{
}

void Map::loadMapFromFile()
{
    backGroundTexture.loadFromFile("background.png");
    backGroundSprite.setTexture(backGroundTexture);
    backGroundSprite.setScale(2.5f, 1.5f);
    std::ifstream inFile("map.txt");

    if (inFile.is_open()) {
        map.clear();

        std::string line;
        while (std::getline(inFile, line)) {
            std::vector<int> row;
            std::istringstream iss(line);
            int value;

            while (iss >> value) {
                row.push_back(value);
            }

            map.push_back(row);
        }

        inFile.close();
    }
    else {
        // Обработка ошибки открытия файла
    }
}
void Map::updateMapTexture()
{
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
    mapTexture.clear(sf::Color::Transparent); // Очищаем текстуру

    
    for (int x = 0; x < map.size(); ++x) {
        for (int y = 0; y < map[x].size(); ++y) {
            int value = map[x][y];
            if (value == 1 || value == 2) {
                sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                block.setPosition(y * BLOCK_SIZE, (map.size() - x - 1) * BLOCK_SIZE);

                // Вычисляем количество блоков над текущим блоком
                int blocksAbove = 0;
                for (int i = x - 1; i >= 0; --i) {
                    if (map[i][y] > 0 && map[i][y] <= 2) {
                        ++blocksAbove;
                    }
                    else {
                        break; // Прекращаем подсчет, если встречаем другой тип блока
                    }
                }

                // Вычисляем количество блоков под текущим блоком
                int blocksBelow = 99;


                int r, g, b;
                int colorReduction;

                    colorReduction = std::min(blocksAbove, blocksBelow) * 15; // Примерный коэффициент для уменьшения цвета

                if (value == 1) {
                    r = std::max(0, 189 - colorReduction); // Минимальное значение R - 0
                    g = std::max(0, 183 - colorReduction); // Минимальное значение G - 0
                    b = std::max(0, 107 - colorReduction); // Минимальное значение B - 0
                }
                else {
                    r = std::max(0, 34 - colorReduction); // Минимальное значение R - 0
                    g = std::max(0, 139 - colorReduction); // Минимальное значение G - 0
                    b = std::max(0, 34 - colorReduction); // Минимальное значение B - 0
                }

                block.setFillColor(sf::Color(r, g, b));
                mapTexture.draw(block); // Рисуем блоки на текстуре
            }
        }
    }
    mapSprite.setTexture(mapTexture.getTexture()); // Устанавливаем текстуру из буфера на спрайт
}


void Map::applyPhysics() {
    while (!map.empty()) {
        {
            std::lock_guard<std::mutex> lock(mutex);
            /*std::cout << "thread no close " << '\n';*/
            if (needClose) {
                std::cout << "thread close " << '\n';
                break;
            }
        }
        
        if (mapBuf != map) {



            mapBuf = map;
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

            if (/*hasBlocksReachedBottom*/1) {
                for (int x = map.size() - 1; x > 0; --x) {
                    for (int y = 0; y < map[x].size(); ++y) {
                        if (map[x][y] == 2) {

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

            if (mapBuf == map) {//проверка на отличие 
                needUpdateMap = 0;
                std::cout << "MapTexture UpdateComlite" << "\n";
            }

            mapUpdateComlite = 1;
        }

        //std::cout << "thread2 is open "<<"need Close: "<<needClose << '\n';

    }
    
    if (!map.empty()) {
        map.clear();
        
    }
    
        
}

void Map::drawMap() {
        window.draw(backGroundSprite);
        if (1/*mapBuf != map*/) {
            updateMapTexture();
        }
        window.draw(mapSprite);

}
void Map::explosion(vt coordinate, float radius) {
    for (int x = 0; x < map.size(); ++x) {
        for (int y = 0; y < map[0].size(); ++y) {
            // Рассчитываем расстояние от текущей точки до эпицентра взрыва
            float distance = std::sqrt((x - coordinate.x) * (x - coordinate.x) + (y - coordinate.y) * (y - coordinate.y));

            // Проверяем, находится ли точка внутри радиуса взрыва
            if (distance <= radius) {

                //устанавливаем значение в матрице map[x][y] равным 0
                map[x][y] = 0;
            }
        }
    }


    needUpdateMap = 1;
}
