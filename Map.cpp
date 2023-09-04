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
