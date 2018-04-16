#pragma once
#include "Engine/Algorithms.h"
#include "Engine/Grid.h"



class ShortestDistanceMaze: Algorithms, public Grid
{
public:
	ShortestDistanceMaze(bool showFinding = true, int x = Con::width / 2, int y = Con::height / 2);

	bool nextMove() override;

private:

	sf::RectangleShape searchRect;
	int tilesLeft;

	bool showFinding;
};
