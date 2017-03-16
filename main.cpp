#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"
#include "Audio.h"
#include "Graphic.h"
#include "Wall.h"

using namespace std;
int exitgame = 0;

int main() {
	
	sf::RenderWindow window(sf::VideoMode(720, 480), "Fight Hard Yeah! Tower Defense Game", sf::Style::Close | sf::Style::Titlebar);
	Audio audio;
	Graphic graphics;
	int flag = 0, counter = 0;

	//Player character texture, rectangle bound to box
	sf::Texture playerTexture;
	playerTexture.loadFromFile("char_sprite_walk_swords.png");
	

	// Wall creation
	vector<Wall>::const_iterator wallit;
	vector<Wall> wallArray;

	/*class Wall wall1;
	sf::Texture textureWall;
	textureWall.loadFromFile("wall.jpg");
	wall1.rect.setTexture(&textureWall);
	*/

	class Wall wall1, wall2, wall3;
	sf::Texture textureWall;
	textureWall.loadFromFile("cave_top.png");
	wall1.rect.setTexture(&textureWall);
	sf::Texture textureWall2;
	textureWall2.loadFromFile("cave_bottom_left.png");
	wall2.rect.setTexture(&textureWall2);
	sf::Texture textureWall3;
	textureWall3.loadFromFile("cave_bottom_right.png");
	wall3.rect.setTexture(&textureWall3);

	wall1.rect.setPosition(0, 0);
	wall1.rect.setSize(sf::Vector2f(720, 200));
	wallArray.push_back(wall1);

	wall2.rect.setPosition(0, 330);
	wall2.rect.setSize(sf::Vector2f(150, 150));
	wallArray.push_back(wall2);

	wall3.rect.setPosition(150, 430);
	wall3.rect.setSize(sf::Vector2f(570, 50));
	wallArray.push_back(wall3);


	Player player(&playerTexture, sf::Vector2u(3, 3), 0.3f, 100.0f);

	//Assigning Player Footstep Sounds
	if (!player.soundBuf.loadFromFile("foot.wav"))
		std::cout << "can't open sound file" << std::endl;
	player.sound.setBuffer(player.soundBuf);
	player.sound.setVolume(100);


	//Menu
	sf::RectangleShape menuImage(sf::Vector2f(720.0f, 480.0f));
	menuImage.setPosition(0.0f, 0.0f);
	sf::Texture menuTexture;
	menuTexture.loadFromFile("menu_1.png");
	menuImage.setTexture(&menuTexture);

	/*
	for (int i = 0; i <= 720; i += 50) {
		wall1.rect.setPosition(i, 0);
		wallArray.push_back(wall1);
		wall1.rect.setPosition(i, 450);
		wallArray.push_back(wall1);
		for (int j = 100; j <= 480; j += 50) {
			wall1.rect.setPosition(0, j);
			wallArray.push_back(wall1);
			wall1.rect.setPosition(700, j);
			wallArray.push_back(wall1);
		}
	}

	for (int i = 100; i <= 300; i += 50) {
		wall1.rect.setPosition(i, 100);
		wallArray.push_back(wall1);
	}
	for (int i = 150; i <= 250; i += 50) {
		wall1.rect.setPosition(100, i);
		wallArray.push_back(wall1);
	}
	for (int i = 150; i <= 550; i += 50) {
		wall1.rect.setPosition(i, 350);
		wallArray.push_back(wall1);
	}
	for (int i = 400; i <= 600; i += 50) {
		wall1.rect.setPosition(i, 100);
		wallArray.push_back(wall1);
	}
	for (int i = 150; i <= 250; i += 50) {
		wall1.rect.setPosition(600, i);
		wallArray.push_back(wall1);
	}
	*/








	//Clock for sprite rotation
	float deltaTime = 0.0f;
	sf::Clock clock;
		
	//if(music = 1) play
	//if(music = 2) play

	//Playing Background Music
	cout << "Playing background music" << endl;
	audio.backgroundmusic1.play();
	audio.backgroundmusic1.setVolume(25);
	
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{ 
			case sf::Event::Closed:
				window.close();
				break;
			}
			if (evnt.type == sf::Event::KeyPressed)
			{
				if (evnt.key.code == sf::Keyboard::Escape)
				{
					std::cout << "Menu Being Displayed" << std::endl;
					if (exitgame == 0)
						exitgame = 1;
					else
						exitgame = 0;
				}
			}
		}
		
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
		{
			flag = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
		{
			flag = 1;
		}
		if (flag == 0)
		{
			playerTexture.loadFromFile("char_sprite_walk3.png");
		}
		else if (flag == 1)
		{
			playerTexture.loadFromFile("char_sprite_walk_swords.png");
		}
		
		window.setView(player.view);


		//Player Wall Collision
		counter = 0;
		for (wallit = wallArray.begin(); wallit != wallArray.end(); wallit++) {
			if (player.body.getGlobalBounds().intersects(wallArray[counter].rect.getGlobalBounds()))
			{
				//Hit wall
				if (player.direction == 1) //Up
				{
					player.faceUp = false;
					player.body.move(0, 1);
				}
				else if (player.direction == 2) //Down
				{
					player.faceDown = false;
					player.body.move(0, -1);
				}
				else if (player.direction == 3) //Left
				{
					player.faceLeft = false;
					player.body.move(1, 0);
				}
				else if (player.direction == 4) //Right
				{
					player.faceRight = false;
					player.body.move(-1, 0);
				}
				else {}
			}
			counter++;
		}

		/*
		counter = 0;
		for (wallit = wallArray.begin(); wallit != wallArray.end(); wallit++) {
			if (player.body.getGlobalBounds().intersects(wallArray[counter].rect.getGlobalBounds()))
			{
				//Hit wall
				if (player.direction == 1) //Up
				{
					player.faceUp = false;
					player.body.move(0, 1);
				}
				else if (player.direction == 2) //Down
				{
					player.faceDown = false;
					player.body.move(0, -1);
				}
				else if (player.direction == 3) //Left
				{
					player.faceLeft = false;
					player.body.move(1, 0);
				}
				else if (player.direction == 4) //Right
				{
					player.faceRight = false;
					player.body.move(-1, 0);
				}
				else {}
			}
			counter++;
		}
		*/

		//what is this?
		window.setView(player.view);

		player.Update(deltaTime);
		window.clear(sf::Color(125, 125, 125));
		window.draw(graphics.background);
		window.draw(graphics.background2);
		window.draw(graphics.background3);
		window.draw(graphics.background4);
		window.draw(graphics.background5);

		//Draw Wall
		counter = 0;
		for (wallit = wallArray.begin(); wallit != wallArray.end(); wallit++)
		{
			wallArray[counter].update();

			window.draw(wallArray[counter].rect);
			window.draw(wallArray[counter].sprite);
			counter++;
		}



		player.Draw(window);

		window.draw(wall1.sprite);
		window.draw(wall2.sprite);
		window.draw(wall3.sprite);

		window.draw(graphics.backgroundTree);

		//displaying Escape Menu
		if (exitgame == 1)
			window.draw(menuImage);
		else
			menuImage.setTexture(&menuTexture);

		window.display();
		}
		return 0;
}


/*Old Comments*/

//1 old animation sf::RectangleShape player(sf::Vector2f(100.0f, 150.0f));
//player.setFillColor(sf::Color::Magenta);
//player.setOrigin(50.0f, 50.0f);
//1 old animation player.setPosition(206.0f, 206.0f);


//background.setOrigin(250.0f, 250.0f);
//background.setPosition(250.0f, 250.0f);



/*case sf::Event::Resized:
//std::cout << "New window width " << evnt.size.width << "New window height " << evnt.size.height << std::endl;
printf("New window width: %i New window height: %i \n", evnt.size.width, evnt.size.height);
break;
case sf::Event::TextEntered:
if (evnt.text.unicode < 128)
{
printf("%c", evnt.text.unicode);
}
*/


/*
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
{
player.move(0.1f, 0.0f);
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
{
player.move(0.0f, -0.1f);
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
{
player.move(0.f, 0.1f);
}
*/
/*
if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
{
sf::Vector2i mousePos = sf::Mouse::getPosition(window);
player.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}
*/
//old animation animation.Update(0, deltaTime, false);
//player.setTextureRect(animation.uvRect);

//window.clear();
//window.draw(player);




