/************************
* Node.cpp
* Author: Sean Miller
* Last Modified: Jan 12, 2020
*
* An individual node is considered
* as a point, with springs linking
* all nodes together. The spring-like
* behavior is handled by
* generateForce(), which applies a
* force in the specified direction on
* the node it's called by. This force follows
* Hooke's law, F=-kx, where k is Hooke's
* constant, and x is the distance of the
* node from equilibrium.
*
* In this simulation, the treatment of
* Hooke's law gives some rather unpredictable results.
* Values of HOOKE (defined in Node.hpp) greater than
* 0.2 give strange behavior where the rope tends
* to jump in the direction of travel. Through
* trial and error, a value of 0.1 has been chosen,
* though it's encouraged that other values
* be tried to observe the effects.
* 
* Values less than 0.2 are insufficient to combat gravity,
* so limit() is used to keep the length of each element
* to a specific value. This produces better inelastic
* behavior.
************************/

#include "Node.hpp"

Node::Node()
{
	//Node is remembered as a rectangle because of a previous rigid body approach,
	//but the associated width and height information are useful in considering the length and width of each rope element.
	body = (Rectangle){WIN_WIDTH/2.0, 0.0, 4.0, 4.0};
	vel = Vector2Zero();
}

Node::Node(Rectangle newBody)
{
	body = newBody;
}

void Node::generateForce(Vector2 lineOfAction)
{
	//Force applied to node in the direction specified.
	float arm = Vector2Length(lineOfAction) - body.height; //arm is equivalent to 'x' in Hooke's law
	if(Vector2Length(lineOfAction) != 0.0){lineOfAction = Vector2Normalize(lineOfAction);} //Avoid divide-by-zero error
	vel = Vector2Add(vel, Vector2Scale(lineOfAction, -HOOKE*arm)); //Hooke's law, in the direction supplied
}

void Node::collide(Vector2 collPoint, float radius)
{
	Vector2 tempVector;
	
	//Execute behavior if node is within obstacle
	if(Vector2Distance((Vector2){body.x, body.y}, collPoint) < radius)
	{
		tempVector = Vector2Subtract((Vector2){body.x, body.y}, collPoint); //Pointing to node from center of obstacle
		tempVector = Vector2Normalize(tempVector); //Unit vector
		tempVector = Vector2Scale(tempVector, radius); //Vector is now length of obstacle radius
		
		//Place node on the outside of obstacle
		body.x = collPoint.x + tempVector.x;
		body.y = collPoint.y + tempVector.y;
		
		//Reduce velocity, causes rope to "drag" against surface of obstacle.
		//The effect is mostly visible when the rope is elastic.
		vel = Vector2Scale(vel, 0.5);
	}
}

void Node::limit(Vector2 target)
{
	//If the node is one side of a rope element, target is the position of the other side.
	Vector2 tempVector;
	
	//Restrict rope element length
	if(Vector2Distance((Vector2){body.x, body.y}, target) > 2.0*body.height)
	{
		tempVector = Vector2Subtract((Vector2){body.x, body.y}, target); //Pointing to node from target
		tempVector = Vector2Scale(tempVector, 2.0*body.height/Vector2Length(tempVector)); //Adjust length of vector to be 2*height
		
		//reposition node to be within 2*height of target
		body.x = target.x + tempVector.x;
		body.y = target.y + tempVector.y;
	}
	
	//Note that this behavior implies that there is a definite head and tail to the rope,
	//a node can only have this relationship with the node above it in the chain.
}

void Node::move()
{
	vel = Vector2Scale(vel, 0.91); //Slowly lose momentum
		//This value is also very finicky, different values can produce unexpected behavior.
	
	//Apply velocity
	body.x += vel.x;
	body.y += vel.y;
	
	//Keep within bounds
	if(body.x < 0.0){body.x = 0.0; vel.x = 0;}
	if(body.x > WIN_WIDTH){body.x = WIN_WIDTH; vel.x = 0;}
	if(body.y < 0.0){body.y = 0.0; vel.y = 0;}
	if(body.y > WIN_HEIGHT){body.y = WIN_HEIGHT; vel.y = 0;}
}

void Node::gravity()
{
	vel = Vector2Add(vel, (Vector2){0.0, 0.9});
}

void Node::draw()
{
	DrawCircle(body.x, body.y, 4.0, RED);
}

Rectangle Node::getBody()
{
	return body;
}

Vector2 Node::getPos()
{
	return (Vector2){body.x, body.y};
}

Vector2 Node::getVel()
{
	return vel;
}

void Node::setBody(Rectangle newBody)
{
	body = newBody;
}

void Node::setBodyX(float newX)
{
	body.x = newX;
}

void Node::setBodyY(float newY)
{
	body.y = newY;
}

void Node::setBodyWidth(float newWidth)
{
	body.width = newWidth;
}

void Node::setBodyHeight(float newHeight)
{
	body.height = newHeight;
}

void Node::setVel(Vector2 newVel)
{
	vel = newVel;
}

void Node::setVelX(float newVelX)
{
	vel.x = newVelX;
}

void Node::setVelY(float newVelY)
{
	vel.y = newVelY;
}