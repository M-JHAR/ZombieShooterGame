#include "Player.h"
#include "SFML/Graphics.hpp"

Player::Player()
	: m_Speed(START_SPEED),
	m_Health((int)START_HEALTH),
	m_MaxHealth((int)START_HEALTH),
	m_Texture(),
	m_Sprite()
{


	m_Texture.loadFromFile("graphics/player.png");
	m_Sprite.setTexture(m_Texture);

	m_Sprite.setOrigin(25, 25);

	m_TileSize = 0;
	m_LeftPressed = m_RightPressed = m_UpPressed = m_DownPressed = false;
}

void Player::spawn(sf::IntRect arena, sf::Vector2u resolution, int tileSize)
{
	m_Position.x = arena.width / 2.0f;
	m_Position.y = arena.height / 2.0f;

	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;

	m_TileSize = tileSize;

	m_Resolution.x = (float)resolution.x;
	m_Resolution.y = (float)resolution.y;
}

void Player::resetPlayerStats()
{
	m_Speed = START_SPEED;
	m_Health = (int)START_HEALTH;
	m_MaxHealth = (int)START_HEALTH;

}

bool Player::hit(sf::Time timeHit)
{
	if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200)
	{
		m_LastHit = timeHit;
		m_Health -= 10;
		return true;
	}

	return false;
}

sf::Time Player::getLastHitTime()
{
	return m_LastHit;
}

sf::FloatRect Player::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

sf::Vector2f Player::getCenter()
{
	return m_Position;
}

float Player::getRotation()
{
	return m_Sprite.getRotation();
}

sf::Sprite Player::getSprite()
{
	return m_Sprite;
}

void Player::moveLeft()
{
	m_LeftPressed = true;
}

void Player::moveRight()
{
	m_RightPressed = true;
}

void Player::moveUp()
{
	m_UpPressed = true;
}

void Player::moveDown()
{
	m_DownPressed = true;
}

void Player::stopLeft()
{
	m_LeftPressed = false;
}

void Player::stopRight()
{
	m_RightPressed = false;
}

void Player::stopUp()
{
	m_UpPressed = false;
}

void Player::stopDown()
{
	m_DownPressed = false;
}

void Player::update(float elapsedTime, sf::Vector2i mousePosition)
{
	if (m_UpPressed)
	{
		m_Position.y -= m_Speed * elapsedTime;
	}
	if (m_DownPressed)
	{
		m_Position.y += m_Speed * elapsedTime;
	}
	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
	}
	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}

	m_Sprite.setPosition(m_Position);

	if (m_Position.x > m_Arena.width - m_TileSize)
	{
		m_Position.x = (float)(m_Arena.width - m_TileSize);
	}
	if (m_Position.x < m_Arena.left + m_TileSize)
	{
		m_Position.x = (float)(m_Arena.left + m_TileSize);
	}
	if (m_Position.y > m_Arena.height - m_TileSize)
	{
		m_Position.y = (float)(m_Arena.height - m_TileSize);
	}
	if (m_Position.y < m_Arena.top + m_TileSize)
	{
		m_Position.y = (float)(m_Arena.top + m_TileSize);
	}

	float angle = (atan2(mousePosition.y - m_Resolution.y / 2, mousePosition.x - m_Resolution.x / 2) * 180) / 3.141f;

	m_Sprite.setRotation(angle);

}

void Player::upgradeSpeed()
{
	m_Speed += (START_SPEED * 0.2f);
}

void Player::upgradeHealth()
{
	m_MaxHealth += (int)(START_HEALTH * 0.2f);
}

void Player::increaseHealthLevel(int amount)
{
	m_Health += amount;

	if (m_Health > m_MaxHealth)
	{
		m_Health = m_MaxHealth;
	}
}

int Player::getHealth()
{
	return m_Health;
}
