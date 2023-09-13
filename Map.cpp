#include "Map.h"


Map::Map(sf::RenderWindow& windowS) :window(windowS),needClose(false)
{
}

void Map::loadMapFromFile()
{
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
            if (value >= 0 && value <= 2) {
                sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                block.setPosition(y * BLOCK_SIZE, (map.size() - x - 1) * BLOCK_SIZE);
                block.setFillColor(colors[value - 1]);
                //block.setFillColor((value >= 1 && value <= 2) ? colors[value - 1] : sf::Color::Black);
                //block.setOutlineThickness(1);
                mapTexture.draw(block); // Рисуем блоки на текстуре
            }
        }
    }
    mapSprite.setTexture(mapTexture.getTexture()); // Устанавливаем текстуру из буфера на спрайт
}

void Map::applyPhysics() {


    

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
        
        if (mapBuf == map) {//проверка на отличие 
            needUpdateMap = 0;
            std::cout << "MapTexture UpdateComlite" << "\n";
        }
        
        



}
void Map::drawMap() {
    if (needUpdateMap) {
        applyPhysics();
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
                // Выполняем действия, связанные с взрывом, в данной точке
                // Например, устанавливаем значение в матрице map[x][y] равным 0
                map[x][y] = 0;
            }
        }
    }
    needUpdateMap = 1;
}
