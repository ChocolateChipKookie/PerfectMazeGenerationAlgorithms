#pragma once
#include <vector>
#include "../Engine/Algorithms.h"
#include "../Engine/Grid.h"

typedef struct Wall{
	int x;
	int y;
	int direction;
}Wall;

class PrimsAlgorithm : Algorithms, public Grid
{
public:
	///Constructor for the class, default values set to 0
	PrimsAlgorithm(int x = 0, int y = 0);
	
	///Chooses next move for the algorithm and draws the state after the move to the window
	///Returns true if it was able to make a move, and false otherwise
	bool nextMove() override;
	
	///Takes a reference to a wall that has to be processed and processes it
	///If the wall can be deleted without making a loop it deletes it
	bool processWall(Wall& wall);
	
private:
	std::vector<Wall> walls{};
};
