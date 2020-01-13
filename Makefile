Pendulum: PendulumMain.o Node.o Ball.o Obstacle.o
	g++ PendulumMain.o Node.o Ball.o Obstacle.o C:\raylib\raylib\src\raylib.rc.data -s -O2 -Wall -lraylib -lopengl32 -lgdi32 -lwinmm -Iexternal -Wl,--subsystem,windows -o Pendulum

PendulumMain.o: PendulumMain.cpp
	g++ -c PendulumMain.cpp
	
Node.o: Node.cpp
	g++ -c Node.cpp
	
Ball.o: Ball.cpp
	g++ -c Ball.cpp
	
Obstacle.o: Obstacle.cpp
	g++ -c Obstacle.cpp