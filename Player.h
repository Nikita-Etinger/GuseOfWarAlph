#pragma once
#include "Projectile.h"
#include <string>

#include <cmath>
#include <ctime>
#include <algorithm>
#include <iomanip> // Для std::setprecision (обрезание float)
#include <sstream>



class Player
{
private:
	float& timeF;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	sf::RenderWindow& window;
	std::vector<std::vector<int>>& map;
	std::vector<Particles>& particlesF;
	float hp = 100;
	float velocityX = 0;
	float velocityY = 0;
	bool command;
	std::string name;
	int stage = 0;// 0- движение,1-выбор направления,2- выбор силы выстрела,4 конец хода

	sf::Text textPlayer;// вывод здоровья и имени


	float powerShot = 0;
	std::vector<sf::CircleShape> circles;
	float projectileSpeed;
	float velocityXPr;
	float velocityYPr;
	float positionX;
	float positionY;
	float directionShot;


	int playerId;
	std::string playerName;
	float posX;
	float posY;
	float accelerationY=0;
	float accelerationX=0;
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
	int coorectCollision = 0;//корректировка колизии персонажа 
	int distanceFall = 0;
public:

	bool scanContactProjectile(float radius, vt coordinatePr);

	Player(std::vector<std::vector<int>>& mapS, sf::RenderWindow& windowS, bool com, int newPlayerId, std::string newName, std::vector<Projectile>& projectileS,float& time , std::vector<Particles>& particles);
	~Player();
	void update(bool turn);
	void handlerEvent(sf::Event& event);
	void applyVelocity();
	int getId();
	float getX();
	float getY();
	void hit(float radius);
	void resetStage();
	bool getEndTurn();

};

