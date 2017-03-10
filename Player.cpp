#include "Player.h"


Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(50.0f, 50.0f));
	body.setPosition(360.0f, 240.0f);
	body.setTexture(texture);

	view.setSize(720, 480);
	view.setCenter(360.0f, 240.0f);
	//view.zoom(0.6f);
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

//Switching map locations
	const float playerposx = body.getPosition().x;
	const float playerposy = body.getPosition().y;
	std::cout << "x: " << playerposx << "     " << "y: " << playerposy << std::endl;

	//checking if player is in east quadrant
	if (body.getPosition().x > 720.0f ) {
		std::cout << "out of bounds East" << std::endl;
		view.setCenter(1080.0f, 240.0f);
		//east = 1;
	}
	//south quadrant
	else if (body.getPosition().y > 480.0f) {
		std::cout << "out of bounds South" << std::endl;
		view.setCenter(360.0f, 720.0f);
	}
	else if (body.getPosition().y < -50.0f) {
		std::cout << "out of bounds North" << std::endl;
		view.setCenter(360.0f, -240.0f);
	}
	else if (body.getPosition().x < -50.0f) {
		std::cout << "out of bounds West" << std::endl;
		view.setCenter(-360.0f, 240.0f);
	}
	else {
		view.setCenter(360.0f, 240.0f);
	}
	
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
