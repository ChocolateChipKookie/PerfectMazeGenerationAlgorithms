#include "stdafx.h"
#include "DepthFirstAlgorithm.h"

DepthFirstAlgorithm::DepthFirstAlgorithm(int x, int y)
	:Grid(Con::width, Con::height, Con::size), currentPos({ x, y })
{
	currentPosRect.setSize({ static_cast<float>(Con::size - Con::gridThickness * 2), static_cast<float>(Con::size - Con::gridThickness * 2) });
	currentPosRect.setFillColor(Con::DFTileColor);

	stacktrace.push_back({ x, y });
	drawAll();
	draw();
}


bool DepthFirstAlgorithm::nextMove()
{
	if (stacktrace.size() <= 0)
	{
		draw();
		return false;
	}

	//Set direction
	int direction{ selectNextMove(currentPos) };

	//If there is a possible move, move, if not, go a step back
	if (direction != -1)
	{
		stacktrace.push_back(currentPos);
		removeWall(currentPos.x, currentPos.y, direction);
		tiles.setSteppedOn(currentPos.x, currentPos.y, true);
		drawTile(currentPos.x, currentPos.y);

		switch (direction)
		{
		case 0:
			currentPos.x++;
			break;
		case 1:
			currentPos.y++;
			break;
		case 2:
			currentPos.x--;
			break;
		case 3:
			currentPos.y--;
		}

		tiles.setSteppedOn(currentPos.x, currentPos.y, true);
		drawTile(currentPos.x, currentPos.y);
	} else
	{
		currentPos = stacktrace.back();
		stacktrace.pop_back();
	}

	draw();

	//Draw
	currentPosRect.setPosition(static_cast<float>(currentPos.x*size + Con::gridThickness), static_cast<float>(currentPos.y*size + Con::gridThickness));
	window.draw(currentPosRect);
	return true;
}

int DepthFirstAlgorithm::selectNextMove(sf::Vector2i pos) const
{
	//Select direction of the next move
	int tries = 4;
	bool checked[4]{};
	bool notOutOfBounds = true;

	while (tries>0)
	{
		int result = rand() % tries;
		tries--;
		Tile tempTile;

		while (checked[result])
		{
			result = (result + 1) % 4;
		}

		switch (result)
		{
		case 0:
			if (pos.x + 1 >= width)
			{
				notOutOfBounds = false;
				break;
			}
			tempTile = tiles.getTile(pos.x + 1, pos.y);
			break;
		case 1:
			if (pos.y + 1 >= height)
			{
				notOutOfBounds = false;
				break;
			}
			tempTile = tiles.getTile(pos.x, pos.y + 1);
			break;
		case 2:
			if (pos.x - 1 < 0)
			{
				notOutOfBounds = false;
				break;
			}
			tempTile = tiles.getTile(pos.x - 1, pos.y);
			break;
		case 3:
			if (pos.y - 1 < 0)
			{
				notOutOfBounds = false;
				break;
			}
			tempTile = tiles.getTile(pos.x, pos.y - 1);
		}

		if (notOutOfBounds && !tempTile.steppedOn)return result;

		notOutOfBounds = true;
		checked[result] = true;
	}

	return -1;
}
