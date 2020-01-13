/************************
* Ball.hpp
* Author: Sean Miller
* Last Modified: Jan 12, 2020
*
* Includes and class definition for Ball.cpp
************************/

#ifndef BALL_HPP
#define BALL_HPP

#include "PendulumMain.hpp"

class Ball
{
	private:
		Vector2 pos;
		Vector2 vel;
		Vector2 lastPos;
		float radius;
	public:
		Ball();
		void move();
		void collide(Vector2 collPoint, float collRadius);
		void gravity();
		void surmiseVel();
		void draw();
		Vector2 getPos();
		Vector2 getVel();
		float getRadius();
		void setPos(Vector2 newPos);
		void setPosX(float newPosX);
		void setPosY(float newPosY);
		void setVel(Vector2 newVel);
		void setVelX(float newVelX);
		void setVelY(float newVelY);
		void setRadius(float newRadius);
};

#endif