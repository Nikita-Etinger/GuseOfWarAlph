#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"
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
	int stage = 0;// 0- движение,1-выбор направления,2- выбор силы выстрела,4 конец хода
	sf::Text textPlayer;// вывод здоровья и имени
	float powerShot=0;
	float directionShot;
	int playerId;
	std::string playerName;
	float posX;
	float posY;
	float accelerationY;
	float accelerationX;
	bool isOnGround();
	bool direction = 0;
	int playerSize;
	bool turnOff = 0;
	void draw();
	float correctAimX=0;
public:
	Player(std::vector<std::vector<int>>& mapS, sf::RenderWindow& windowS, bool com, int newPlayerId, std::string newName);

	void update();
	void handlerEvent(sf::Event& event);
	void applyVelocity();
	void placePlayersOnMap();
	bool isValidPosition(int x, int y);
	int getId();
	float getX();
	float getY();
	void hit(float radius);
	void resetStage();
};

