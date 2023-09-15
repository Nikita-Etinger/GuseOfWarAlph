
#include "Particles.h"

#include "string"

Particles::Particles(int type, float positionXS, float positionYS, float& timeF,std::string newtext="")
	:typeS(type),timeS(timeF),positionX(positionXS),positionY(positionYS) {

	sizeVape = rand() % (10 - 5 + 1) + 5;
	switch (typeS) {
	case(1):
		//дым
		timeLive = 255 / 2;
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
	int r, g, b;
	int buf = rand() % (50 - 5 + 1) + 5;
	r = 210-buf;
	g = 210 - buf;
	b = 210 - buf;
	colorVape = sf:: Color(r, g, b);
}

void Particles::update() {
	if (typeS !=2) {
		positionY += 0.1f;
	}
	timeLive -= 1;
	//std::cout << "timeLive " << timeLive << std::endl;
	//if (timeLive<0) {

	//	needDelete = true;
	//}

}
bool Particles::getStatus() {
	return needDelete;
}
void Particles::draw(sf::RenderWindow& window) {
	if (needDelete == false&&timeLive>5) {

		sizeVape += 1.00001;
		if (typeS == 1) {
			
			sprite.setTexture(texture);
			sprite.setColor(sf::Color(255, 255, 255, timeLive*2));
			
		
			sprite.setOrigin(sf::Vector2f(sizeVape / 2, sizeVape / 2));
			sprite.setScale(sf::Vector2f(sizeVape/20, sizeVape/20));

			sprite.setPosition(sf::Vector2f(positionX * BLOCK_SIZE - 5, positionY * BLOCK_SIZE));


			window.draw(sprite);
		}
		else if (typeS == 2) {
			sprite.setTexture(texture);
			sprite.setColor(sf::Color(255, 255, 255, timeLive*4));



			// Установка масштаба
			sprite.setScale(sf::Vector2f(5, 5));

			// Рассчитываем позицию с учетом центра спрайта
			sprite.setPosition(sf::Vector2f(positionX * BLOCK_SIZE - sprite.getGlobalBounds().getSize().x/2, positionY * BLOCK_SIZE-sprite.getGlobalBounds().getSize().y/2));

			window.draw(sprite);
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


