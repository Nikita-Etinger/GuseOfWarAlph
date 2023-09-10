#pragma once
#include "Projectile.h"
#include <string>

#include <cmath>
#include <ctime>
#include <algorithm>
#include <iomanip> // ��� std::setprecision (��������� float)
#include <sstream>



class Player
{
private:
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	sf::RenderWindow& window;
	std::vector<std::vector<int>>& map;
	float hp = 100;
	float velocityX = 0;
	float velocityY = 0;
	bool command;
	std::string name;
	int stage = 0;// 0- ��������,1-����� �����������,2- ����� ���� ��������,4 ����� ����

	sf::Text textPlayer;// ����� �������� � �����
	float powerShot = 0;
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
	void drawAim();
	void drawHpName();
	void drawPower();
	void drawPlayer();
	float correctAimX = 0;
	std::vector<Projectile>& projectile;
	void drawCenter();
	void PlacePositionOnMap();
	bool ScanPosition();
public:
	Player(std::vector<std::vector<int>>& mapS, sf::RenderWindow& windowS, bool com, int newPlayerId, std::string newName, std::vector<Projectile>& projectileS);
	~Player();
	void update();
	void handlerEvent(sf::Event& event);
	void applyVelocity();
	int getId();
	float getX();
	float getY();
	void hit(float radius);
	void resetStage();

};

