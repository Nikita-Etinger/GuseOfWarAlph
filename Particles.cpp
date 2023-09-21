
#include "Particles.h"

#include "string"

Particles::Particles(int type, float positionXS, float positionYS, float& timeF,std::string newtext="")
	:typeS(type),timeS(timeF),positionX(positionXS),positionY(positionYS) {
	setTexture();


	sizeVape = rand() % (10 - 5 + 1) + 5;
	switch (typeS) {
	case(1):
		//дым
		timeLive = 255 / 3;
		texture.loadFromFile("vape.png");
		break;
	case(2):
		//взрыв
		timeLive = 30;
		texture.loadFromFile("explosion.png");
		break;

	case(3):
		//взрыв
		timeLive = 70;
		text.setString(newtext);
		break;
	}
	randSize = rand() % 3;
}
void Particles::setTexture() {
	// Проверка на наличие данных в текстуре
	if (!Particles::vapeTexture.getSize().x > 0 && !Particles::vapeTexture.getSize().y > 0) {
		Particles::vapeTexture.loadFromFile("vape.png");
	}
	if (!Particles::explosionTexture.getSize().x > 0 && !Particles::explosionTexture.getSize().y > 0) {
		Particles::explosionTexture.loadFromFile("explosion.png");
	}
}
void Particles::update() {
	if (typeS !=2) {
		positionY += 0.2f;
	}
	timeLive -= 1;
	

}
bool Particles::getStatus() {
	return needDelete;
}
void Particles::render(sf::RenderWindow& window) {
	if (timeLive>10) {
		sf::Sprite sp;
		sizeVape += 1.00001;
		if (typeS == 1) {
			
				sp.setTexture(Particles::vapeTexture);
				sp.setColor(sf::Color(255, 255, 255, timeLive * 1.5));
				sp.setOrigin(sf::Vector2f((sizeVape + randSize) / 2, (sizeVape + randSize) / 2));
				sp.setScale(sf::Vector2f((sizeVape + randSize) / 20, (sizeVape + randSize) / 20));

				sp.setPosition(sf::Vector2f(positionX * BLOCK_SIZE - 5, positionY * BLOCK_SIZE));
				window.draw(sp);
			
		}
		else if (typeS == 2) {
			sp.setTexture(Particles::explosionTexture);
			sp.setColor(sf::Color(255, 255, 255, timeLive*4));
			// Установка масштаба
			sp.setScale(sf::Vector2f(5, 5));

			// Рассчитываем позицию с учетом центра спрайта
			sp.setPosition(sf::Vector2f(positionX * BLOCK_SIZE - sp.getGlobalBounds().getSize().x/2, positionY * BLOCK_SIZE-sp.getGlobalBounds().getSize().y/2));

			window.draw(sp);
		}
		else if (typeS == 3) {
			
			
			font.loadFromFile("font.ttf");
			text.setFont(font);
			text.setPosition(positionX * BLOCK_SIZE , positionY * BLOCK_SIZE - BLOCK_SIZE * 6);
			text.setCharacterSize(20); // Размер шрифта
			text.setFillColor(sf::Color::Red);
			text.setOutlineThickness(2);
			window.draw(text);
		}
	}
	else
	needDelete = 1;


}

sf::Texture vapeTexture;
sf::Texture explosionTexture;
