#pragma once

#include<SFML/Graphics.hpp>
#include<vector>
#include"Game.h"

class CircleShape
{
public:
	CircleShape(GameDataRef _data ,sf::Vector2f pos) : data(_data)
	{
		cir.setPosition(pos);
		cir.setRadius(2);
		cir.setFillColor(sf::Color::Cyan);
	}

	void Update(float dt)
	{
		cir.setPosition(sf::Vector2f(cir.getPosition() + direction * speed));
		if (cir.getPosition().x > 1200.0f)
		{
			cir.setPosition(sf::Vector2f(0, cir.getPosition().y));
		}

		else if (cir.getPosition().x < 0)
		{
			cir.setPosition(sf::Vector2f(1200, cir.getPosition().y));
		}

		if (cir.getPosition().y > 800.0f)
		{
			cir.setPosition(sf::Vector2f(cir.getPosition().y,0));
		}

		else if (cir.getPosition().y < 0)
		{
			cir.setPosition(sf::Vector2f(cir.getPosition().x,800));
		}
	}

	void Draw()
	{
		data->window.draw(cir);
	}

	void SetDirection(const sf::Vector2f& dir)
	{
		direction = dir;
	}

	sf::Vector2f GetDirection() const
	{
		return direction;
	}

	sf::Vector2f GetPosition() const
	{
		return cir.getPosition();
	}

	float GetRadius() const
	{
		return cir.getRadius();
	}

	bool isInserted = false;
private:
	sf::CircleShape cir;
	GameDataRef data;
	sf::Vector2f direction;

	float speed = 2.0f;
};

inline float Distance(const sf::Vector2f& pos1, const sf::Vector2f& pos2)
{
	return sqrt((pos2.x - pos1.x) * (pos2.x - pos1.x) + (pos2.y - pos1.y) * (pos2.y - pos1.y));
}


inline bool CheckCollision(const CircleShape& c1, const CircleShape& c2)
{
	float dist = Distance(c1.GetPosition(), c2.GetPosition());
	if (dist < c1.GetRadius() + c1.GetRadius())return true;
	else return false;
}


