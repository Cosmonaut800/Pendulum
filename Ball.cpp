/************************
* Ball.cpp
* Author: Sean Miller
* Last Modified: Jan 12, 2020
*
* Ball that bounces when it collides with obstacles.
************************/

#include "Ball.hpp"

Ball::Ball()
{
	pos = Vector2Zero();
	vel = Vector2Zero();
	lastPos = Vector2Zero();
	radius = 16.0;
}

void Ball::move()
{
	//Apply velocity
	pos.x += vel.x;
	pos.y += vel.y;
	
	//Keep in bounds
	if(pos.x < radius){
		pos.x = radius;
		vel.x = -vel.x * 0.9;
	}
	if(pos.x > WIN_WIDTH - radius){
		pos.x = WIN_WIDTH - radius;
		vel.x = -vel.x * 0.9;
	}
	if(pos.y < radius){
		pos.y = radius;
		vel.y = -vel.y * 0.9;
	}
	if(pos.y > WIN_HEIGHT - radius){
		pos.y = WIN_HEIGHT - radius;
		vel.y = -vel.y * 0.9;
	}
}

void Ball::collide(Vector2 collPoint, float collRadius)
{
	//Collide with circular obstacles.
	
	Vector2 tempVector;
	Vector2 tempVector2;
	
	//Only execute behavior when ball is within obstacle
	if(Vector2Distance(pos, collPoint) < collRadius+radius)
	{
		tempVector = Vector2Subtract(pos, collPoint); //Pointing to ball from center of obstacle
		tempVector = Vector2Normalize(tempVector); //Unit vector
		tempVector2 = Vector2Scale(tempVector, Vector2DotProduct(vel, tempVector)); //Component of velocity along vector to ball from obstacle
		vel = Vector2Scale(Vector2Subtract(vel, Vector2Scale(tempVector2, 2)), 0.9); //Subtract component twice, effectively reversing velocity along that direction,
		                                                                             //lose a little velocity with each bounce
		tempVector = Vector2Scale(tempVector, collRadius+radius); //Get point on circle where bounce happened
		
		//Set position to this point, avoids ball getting stuck in obstacle
		pos.x = collPoint.x + tempVector.x;
		pos.y = collPoint.y + tempVector.y;
	}
}

void Ball::gravity()
{
	vel.y += 1.0;
}

void Ball::surmiseVel()
{
	//Calculate velocity based on current and last position.
	//Used when ball is thrown by mouse.
	vel = Vector2Scale(Vector2Subtract(pos, lastPos), 0.75);
	lastPos = pos;
}

void Ball::draw()
{
	DrawCircleV(pos, radius, DARKGREEN);
}

Vector2 Ball::getPos()
{
	return pos;
}

Vector2 Ball::getVel()
{
	return vel;
}

float Ball::getRadius()
{
	return radius;
}

void Ball::setPos(Vector2 newPos)
{
	pos = newPos;
}

void Ball::setPosX(float newPosX)
{
	pos.x = newPosX;
}

void Ball::setPosY(float newPosY)
{
	pos.y = newPosY;
}

void Ball::setVel(Vector2 newVel)
{
	vel = newVel;
}

void Ball::setVelX(float newVelX)
{
	vel.x = newVelX;
}

void Ball::setVelY(float newVelY)
{
	vel.y = newVelY;
}

void Ball::setRadius(float newRadius)
{
	radius = newRadius;
}