/************************
* Obstacle.cpp
* Author: Sean Miller
* Last Modified: Jan 12, 2020
*
* A circle. That's it.
************************/

#include "Obstacle.hpp"

void Obstacle::draw()
{
	DrawCircleV(pos, radius, RED);
}

void Obstacle::draw(Color color)
{
	DrawCircleV(pos, radius, color);
}

Vector2 Obstacle::getPos()
{
	return pos;
}

float Obstacle::getRadius()
{
	return radius;
}

void Obstacle::setPos(Vector2 newPos)
{
	pos = newPos;
}

void Obstacle::setPosX(float newPosX)
{
	pos.x = newPosX;
}

void Obstacle::setPosY(float newPosY)
{
	pos.y = newPosY;
}

void Obstacle::setRadius(float newRadius)
{
	radius = newRadius;
}