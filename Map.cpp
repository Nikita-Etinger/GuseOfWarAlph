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
        // ��������� ������ �������� �����
    }
}
void Map::explosion(vt coordinate, float radius) {
    for (int x = 0; x < map.size(); ++x) {
        for (int y = 0; y < map[0].size(); ++y) {
            // ������������ ���������� �� ������� ����� �� ��������� ������
            float distance = std::sqrt((x - coordinate.x) * (x - coordinate.x) + (y - coordinate.y) * (y - coordinate.y));

            // ���������, ��������� �� ����� ������ ������� ������
            if (distance <= radius) {
                // ��������� ��������, ��������� � �������, � ������ �����
                // ��������, ������������� �������� � ������� map[x][y] ������ 0
                map[x][y] = 0;
            }
        }
    }
}
