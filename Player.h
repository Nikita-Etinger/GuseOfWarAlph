#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
	sf::RenderWindow& window;
	std::vector<std::vector<int>>& map;
	float hp=100;
	float velocityX=0;
	float velocityY=0;
	bool command;
	std::string name;
	int stage = 0;// 0- ��������,1-����� �����������,2- ����� ���� ��������,4 ����� ����
	sf::Text textPlayer;// ����� �������� � �����
	float powerShot=0;
	float directionShot=0;
	int playerId;
	std::string playerName;
	float posX;
	float posY;
public:
	Player(std::vector<std::vector<int>>& mapS, sf::RenderWindow& windowS, bool com, int newPlayerId, std::string newName);

	void update();
	void handlerEvent(sf::Event event);
	void applyVelocity();
	void placePlayersOnMap();
	bool isValidPosition(int x, int y);
	int getId();
	float getX();
	float getY();
	void hit(float radius);
};

