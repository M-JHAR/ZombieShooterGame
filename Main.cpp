#include <iostream>

#include "SFML/Graphics.hpp"
#include "Player.h"
#include "ZombieArena.h"

int main()
{
	enum class State
	{
		PAUSED,
		LEVELING_UP,
		GAME_OVER,
		PLAYING
	};

	State state = State::GAME_OVER;

	sf::Vector2u resolution;
	resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;

	sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Zombie Shooter", sf::Style::Fullscreen);

	sf::View mainView(sf::FloatRect(0, 0, (float)resolution.x, (float)resolution.y));

	sf::Clock clock;

	sf::Time gameTimeTotal;

	sf::Vector2f mouseWolrdPosition;

	sf::Vector2i mouseScreenPosition;

	Player player;

	sf::IntRect arena;

	sf::VertexArray background;

	sf::Texture textureBackground;
	textureBackground.loadFromFile("graphics/background_sheet.png");

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter && state == State::PLAYING)
				{
					state = State::PAUSED;
				}
				else if (event.key.code == sf::Keyboard::Enter && state == State::PAUSED)
				{
					state = State::PLAYING;

					clock.restart();
				}
				else if (event.key.code == sf::Keyboard::Enter && state == State::GAME_OVER)
				{
					state = State::LEVELING_UP;
				}

				if (state == State::PLAYING)
				{

				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		if (state == State::PLAYING)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				player.moveUp();
			}
			else
			{
				player.stopUp();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				player.moveDown();
			}
			else
			{
				player.stopDown();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				player.moveLeft();
			}
			else
			{
				player.stopLeft();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				player.moveRight();
			}
			else
			{
				player.stopRight();
			}
		}

		if (state == State::LEVELING_UP)
		{
			if (event.key.code == sf::Keyboard::Num1)
			{
				state = State::PLAYING;
			}
			if (event.key.code == sf::Keyboard::Num2)
			{
				state = State::PLAYING;
			}
			if (event.key.code == sf::Keyboard::Num3)
			{
				state = State::PLAYING;
			}
			if (event.key.code == sf::Keyboard::Num4)
			{
				state = State::PLAYING;
			}
			if (event.key.code == sf::Keyboard::Num5)
			{
				state = State::PLAYING;
			}
			if (event.key.code == sf::Keyboard::Num6)
			{
				state = State::PLAYING;
			}

			if (state == State::PLAYING)
			{

				arena.width = 500;
				arena.height = 500;
				arena.left = 0;
				arena.top = 0;

				int tileSize = createBackground(background, arena);

				player.spawn(arena, resolution, tileSize);

				clock.restart();
			}
		}


		/*
		* *************************
		*	UPDATE THE FRAME
		* *************************
		*/

		if (state == State::PLAYING)
		{
			sf::Time dt = clock.restart();

			gameTimeTotal += dt;

			float dtAsSeconds = dt.asSeconds();

			mouseScreenPosition = sf::Mouse::getPosition();

			mouseWolrdPosition = window.mapPixelToCoords(sf::Mouse::getPosition(), mainView);

			player.update(dtAsSeconds, sf::Mouse::getPosition());

			sf::Vector2f playerPosition(player.getCenter());

			mainView.setCenter(player.getCenter());
		}

		/*
		*
		* ****************
		*  DRAW THE SCENE
		* ****************
		*
		*/

		if (state == State::PLAYING)
		{
			window.clear();
			window.setView(mainView);

			window.draw(background, &textureBackground);

			window.draw(player.getSprite());
		}
		if (state == State::LEVELING_UP)
		{

		}
		if (state == State::PAUSED)
		{

		}
		if (state == State::GAME_OVER)
		{

		}

		window.display();

	}


	return 0;
}