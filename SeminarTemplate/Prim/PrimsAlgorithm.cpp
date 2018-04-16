#include "stdafx.h"
#include "PrimsAlgorithm.h"

PrimsAlgorithm::PrimsAlgorithm(int x, int y)
	:Grid(Con::width, Con::height, Con::size)
{
	if (x + 1 < Con::width &&
		!tiles.getTile(x + 1, y).steppedOn) {
		walls.push_back({ x, y, 0 });
	}
	if (y + 1 < Con::height &&
		!tiles.getTile(x, y + 1).steppedOn) {
		walls.push_back({ x, y, 1 });
	}
	if (x - 1 >= 0 &&
		!tiles.getTile(x - 1, y).steppedOn) {
		walls.push_back({ x, y, 2 });
	}
	if (y - 1 >= 0 &&
		!tiles.getTile(x, y - 1).steppedOn) {
		walls.push_back({ x, y, 3 });
	}

	tiles.setSteppedOn(x, y, true);

	drawAll();
	draw();
}

bool PrimsAlgorithm::nextMove()
{
	bool returnValue{false};
	bool newTile{ false };

	while (!newTile)
	{
		if (walls.size()>0)
		{
			int number = rand() % walls.size();
			Wall wall = walls.at(number);

			newTile = processWall(wall);
			walls.erase(walls.begin() + number);

			returnValue = true;
		}
		else
		{
			returnValue = false;
			break;
		}
	}
	
	draw();
	return returnValue;
}

bool PrimsAlgorithm::processWall(Wall& wall)
{
	if (wall.x < 0 || wall.x >= Con::width || wall.y < 0 || wall.y >= Con::height)return false;
	
	bool steppedOn{ false };

	switch (wall.direction)
	{
	case 0:
		if (++wall.x >= Con::width) return false;
		if (tiles.getTile(wall.x, wall.y).steppedOn)steppedOn = true;
		break;
	case 1:
		if (++wall.y >= Con::height) return false;
		if (tiles.getTile(wall.x, wall.y).steppedOn)steppedOn = true;
		break;
	case 2:
		if (--wall.x < 0) return false;
		if (tiles.getTile(wall.x, wall.y).steppedOn)steppedOn = true;
		break;
	case 3:
		if (--wall.y < 0) return false;
		if (tiles.getTile(wall.x, wall.y).steppedOn)steppedOn = true;
	}

	if(!steppedOn)
	{
		removeWall(wall.x, wall.y, (wall.direction + 2) % Con::walls);
		tiles.setSteppedOn(wall.x, wall.y, true);
		drawTile(wall.x, wall.y);

		if (wall.x + 1 < Con::width &&
			!tiles.getTile(wall.x + 1, wall.y).steppedOn) {
			walls.push_back({ wall.x, wall.y, 0 });
		}
		if (wall.y + 1 < Con::height &&
			!tiles.getTile(wall.x, wall.y + 1).steppedOn) {
			walls.push_back({ wall.x, wall.y, 1 });
		}
		if (wall.x - 1 >= 0 &&
			!tiles.getTile(wall.x - 1, wall.y).steppedOn) {
			walls.push_back({ wall.x, wall.y, 2 });
		}
		if (wall.y - 1 >= 0 &&
			!tiles.getTile(wall.x, wall.y - 1).steppedOn) {
			walls.push_back({ wall.x, wall.y, 3 });
		}
		return true;
	}

	return false;
}
