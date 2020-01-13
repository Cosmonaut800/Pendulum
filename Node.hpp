/************************
* Node.hpp
* Author: Sean Miller
* Last Modified: Jan 12, 2020
*
* Includes, defines, and class definition for Node.cpp
************************/

#ifndef NODE_HPP
#define NODE_HPP

#include "raylib.h"
#include "raymath.h"
#include "PendulumMain.hpp"

#define HOOKE 0.1

class Node
{
	private:
		Rectangle body;
		Vector2 vel;
	public:
		Node();
		Node(Rectangle newBody);
		void generateForce(Vector2 lineOfAction);
		void collide(Vector2 collPoint, float radius);
		void limit(Vector2 target);
		void move();
		void gravity();
		void draw();
		Rectangle getBody();
		Vector2 getPos();
		Vector2 getVel();
		void setBody(Rectangle newBody);
		void setBodyX(float newX);
		void setBodyY(float newY);
		void setBodyWidth(float newWidth);
		void setBodyHeight(float newHeight);
		void setVel(Vector2 newVel);
		void setVelX(float newVelX);
		void setVelY(float newVelY);
};

#endif //NODE_HPP