/************************
* PendulumMain.cpp
* Author: Sean Miller
* Last Modified: Jan 12, 2020
*
* Rope physics toy. The rope is attached to a ball
* which bounces when it collides with obstacles. The
* rope also collides with the obstacles. It does not
* exert a force on the ball.
* Currently only circular obstacles are supported.
*
* The rope is effectively a series of points held
* together by springs. The spring physics were very
* finicky, so a function is implemented to limit
* the length of each element of the rope. Incidentally,
* this produced a nice inelastic effect. This is
* discussed more in Node.cpp.
*
* CONTROLS
*------------------------
* The ball can be dragged and thrown with the mouse.
* Clicking the mouse snaps the ball to the mouse (it
* was frustrating to try and catch the ball once it's
* bouncing around).
* Pressing G will toggle gravity.
* Pressing Space will toggle length limitation (see Node::limit()).
************************/

#include "PendulumMain.hpp"
#include "Node.hpp"
#include "Ball.hpp"
#include "Obstacle.hpp"

#define NUM_OF_LINKS 64
int main()
{
	//Declaration of variables
	unsigned int frame = 0;
	int i = 0;
	int j = 0;
	Vector2 tempVector;
	Color color;
	bool elastic = false;
	bool gravity = true;
	Ball ball;
	Node chain[NUM_OF_LINKS];
	Obstacle statObstacle;
	Obstacle dynObstacle;
	
	//Initialize ball and rope
	ball.setPosX(WIN_WIDTH/2.0);
	ball.setPosY(WIN_HEIGHT/2.0);
	chain[0].setBodyX(ball.getPos().x);
	chain[0].setBodyY(ball.getPos().y);
	for(i=1;i<NUM_OF_LINKS;i++)
	{
		chain[i].setBodyX(chain[i-1].getBody().x);
		chain[i].setBodyY(chain[i-1].getBody().y + chain[i].getBody().height);
	}
	
	//Initialize obstacles
	statObstacle.setPosX(WIN_WIDTH*0.8);
	statObstacle.setPosY(WIN_HEIGHT*0.8);
	statObstacle.setRadius(256.0);
	dynObstacle.setPosX(0);
	dynObstacle.setPosY(WIN_HEIGHT*0.5);
	dynObstacle.setRadius(80.0);
	
	//Initialize window
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "Pendulum Demo");
	SetTargetFPS(FPS);
	
	while(!WindowShouldClose()) //Close window or hit ESC to end program
	{
		dynObstacle.setPosX(150.0*sin(frame/64.0)+150.0); //Update position of dynamic obstacle
		
		//Controls
		if(IsKeyPressed(KEY_SPACE)){elastic = !elastic;}
		if(IsKeyPressed(KEY_G)){gravity = !gravity;}
		
		if(gravity) //Execute gravity
		{
			ball.gravity();
			for(i=0;i<NUM_OF_LINKS;i++)
			{
				chain[i].gravity();
			}
		}
		
		ball.move(); //Move ball
		if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) //Possibly overwrite what ball.move() just did
		{
			ball.setPos(GetMousePosition());
			ball.surmiseVel();
		}
		
		//Set first node of chain to ball's position
		chain[0].setBodyX(ball.getPos().x);
		chain[0].setBodyY(ball.getPos().y);
		
		//Check collisions
		ball.collide(statObstacle.getPos(), statObstacle.getRadius());
		ball.collide(dynObstacle.getPos(), dynObstacle.getRadius());
		chain[0].collide(statObstacle.getPos(), statObstacle.getRadius());
		chain[0].collide(dynObstacle.getPos(), dynObstacle.getRadius());
		
		for(i=1;i<NUM_OF_LINKS-1;i++) //For each node after the first one, except the last one
		{
			//Apply force toward previous node
			tempVector = Vector2Subtract(chain[i].getPos(), chain[i-1].getPos());
			chain[i].generateForce(tempVector);
			
			//Apply force toward next node
			tempVector = Vector2Subtract(chain[i].getPos(), chain[i+1].getPos());
			chain[i].generateForce(tempVector);
			
			//Move each node
			chain[i].move();
			if(!elastic){chain[i].limit(chain[i-1].getPos());} //Decide whether elastic or inelastic motion
			
			//Check collisions
			chain[i].collide(statObstacle.getPos(), statObstacle.getRadius());
			chain[i].collide(dynObstacle.getPos(), dynObstacle.getRadius());
		}
		
		//Apply force on last node toward previous node
		tempVector = Vector2Subtract(chain[NUM_OF_LINKS-1].getPos(), chain[NUM_OF_LINKS-2].getPos());
		chain[NUM_OF_LINKS-1].generateForce(tempVector);
		
		//Move last node
		chain[NUM_OF_LINKS-1].move();
		chain[NUM_OF_LINKS-1].limit(chain[NUM_OF_LINKS-2].getPos());
		
		//Check collisions
		chain[NUM_OF_LINKS-1].collide(statObstacle.getPos(), statObstacle.getRadius());
		chain[NUM_OF_LINKS-1].collide(dynObstacle.getPos(), dynObstacle.getRadius());

		frame++; //Keep track of frames for timing
		
		//Draw frame
		BeginDrawing();
			ClearBackground(RAYWHITE);
			
			//Obstacles
			statObstacle.draw(PURPLE);
			dynObstacle.draw(DARKPURPLE);
			
			//Draw a line between each node and its previous node (first node excluded as it doesn't have a precedent node)
			for(i=1;i<NUM_OF_LINKS;i++)
			{
				if(i%2 == 0){color = (Color){255, 64, 0, 255};} //Alternate coloring
				else{color = (Color){255, 196, 0, 255};}
				DrawLineEx(chain[i].getPos(), chain[i-1].getPos(), chain[i].getBody().width, color);
			}
			//Draw ball
			ball.draw();
		
			DrawFPS(WIN_WIDTH-80, WIN_HEIGHT-30);
		EndDrawing();
	}
	
	CloseWindow();
	
	return 0;
}