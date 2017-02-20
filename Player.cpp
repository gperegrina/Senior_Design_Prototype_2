#include "Player.h"


Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(50.0f, 50.0f));
	body.setPosition(206.0f, 206.0f);
	body.setTexture(texture);

}


Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		//while (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {}
		sound.play();
		std::cout << "moving left" << std::endl;
		movement.x -= speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		sound.play();
		std::cout << "moving right" << std::endl;
		movement.x += speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		sound.play();
		std::cout << "moving up" << std::endl;
		movement.y -= speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		sound.play();
		std::cout << "moving down" << std::endl;
		movement.y += speed * deltaTime;
	}


	//insert a third row when moving up and down?
	//include another if statment to move the sprite sheet

	if (movement.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;
		if (movement.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}
	if (movement.y < 0.0f) {
		row = 2;

	}
	/*if (movement.y == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 2;
		if (movement.y > 0.0f)
			faceRight = false;
		else
			faceRight = true;
	}*/

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(movement);

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
