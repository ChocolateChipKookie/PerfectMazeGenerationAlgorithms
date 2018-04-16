#pragma once
#include "Engine/Algorithms.h"
#include "Engine/Grid.h"

class DepthFirstAlgorithm: Algorithms, public Grid
{
public:
	///Constructor
	DepthFirstAlgorithm(int x = 0, int y = 0);

	bool nextMove() override;

private:
	///Selects direction for the next move
	int selectNextMove(sf::Vector2i pos) const;

	sf::RectangleShape currentPosRect;

	std::vector<sf::Vector2i> stacktrace;
	sf::Vector2i currentPos;

};
