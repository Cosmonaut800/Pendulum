/************************
* Obstacle.hpp
* Author: Sean Miller
* Last Modified: Jan 12, 2020
*
* Includes and class definition for Obstacle.cpp
************************/

#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "PendulumMain.hpp"

class Obstacle
{
	private:
		Vector2 pos;
		float radius;
	public:
		void draw();
		void draw(Color color);
		Vector2 getPos();
		float getRadius();
		void setPos(Vector2 newPos);
		void setPosX(float newPosX);
		void setPosY(float newPosY);
		void setRadius(float newRadius);
};

#endif //OBSTACLE_HPP