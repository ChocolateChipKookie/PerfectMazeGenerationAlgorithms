#include "stdafx.h"
#include "ShortestDistanceMaze.h"
#include <iostream>
#include <valarray>

ShortestDistanceMaze::ShortestDistanceMaze(bool showFinding, int x, int y)
	:Grid(Con::width, Con::height, Con::size), searchRect({ static_cast<float>(Con::size - 2 * Con::gridThickness), static_cast<float>(Con::size - 2 * Con::gridThickness) }),  tilesLeft(width*height - 1), showFinding(showFinding)
{
	tiles.setSteppedOn(x, y, true);
	searchRect.setFillColor(sf::Color::Magenta);

	drawAll();
	draw();
}

bool ShortestDistanceMaze::nextMove()
{
	//Draw finished maze if there are no free tiles left
	if (tilesLeft == 0)
	{
		draw();
		return false;
	}

	//Choosing a random tile
	int finalTileNumber{ rand() % tilesLeft };

	for(int i = 0 ; i <= finalTileNumber; i++)
	{
		const Tile tempTile = tiles.getTile(i%width, i/ width);
		if(tempTile.steppedOn)
		{
			finalTileNumber++;
		}
	}

	sf::Vector2i currentPosition(finalTileNumber % width, finalTileNumber / width);
	std::vector<sf::Vector2i> closestPoints;

	const int maxDistance{std::max(abs(width-currentPosition.x), currentPosition.x) + std::max(abs(height - currentPosition.y), currentPosition.y) };
	int distance{ 1 };

	//Finding closest active tiles to the selected
	while(closestPoints.empty() && distance <= maxDistance)
	{	
		if(showFinding)
		{
			window.clear();
			draw();
		}

		for(int i = 0; i< distance; i++)
		{
			if (currentPosition.x + distance - i < width && currentPosition.y + i<height)
			{
				Tile tempTile = tiles.getTile(currentPosition.x + distance - i, currentPosition.y + i);
				if(showFinding)
				{
					searchRect.setPosition(static_cast<float>((currentPosition.x + distance - i)*size + Con::gridThickness), static_cast<float>((currentPosition.y + i)*size + Con::gridThickness));
					window.draw(searchRect);
				}
				if (tempTile.steppedOn)closestPoints.push_back({ currentPosition.x + distance - i, currentPosition.y + i });
			}
			if (currentPosition.x - i >= 0 && currentPosition.y + distance - i <height)
			{
				Tile tempTile = tiles.getTile(currentPosition.x - i, currentPosition.y + distance - i);
				if (showFinding)
				{
					searchRect.setPosition(static_cast<float>((currentPosition.x - i)*size + Con::gridThickness), static_cast<float>((currentPosition.y + distance - i)*size + Con::gridThickness));
					window.draw(searchRect);
				}
				if (tempTile.steppedOn)closestPoints.push_back({ currentPosition.x - i, currentPosition.y + distance - i });
			}
			if (currentPosition.x - distance + i >= 0 && currentPosition.y - i >= 0)
			{
				Tile tempTile = tiles.getTile(currentPosition.x - distance + i, currentPosition.y - i);
				if (showFinding)
				{
					searchRect.setPosition(static_cast<float>((currentPosition.x - distance + i)*size + Con::gridThickness), static_cast<float>((currentPosition.y - i)*size + Con::gridThickness));
					window.draw(searchRect);
				}
				if (tempTile.steppedOn)closestPoints.push_back({ currentPosition.x - distance + i, currentPosition.y - i });
			}
			if (currentPosition.x + i < width && currentPosition.y - distance + i >= 0)
			{
				Tile tempTile = tiles.getTile(currentPosition.x + i, currentPosition.y - distance + i);
				if (showFinding)
				{
					searchRect.setPosition(static_cast<float>((currentPosition.x + i)*size + Con::gridThickness), static_cast<float>((currentPosition.y - distance + i)*size + Con::gridThickness));
					window.draw(searchRect);
				}
				if (tempTile.steppedOn)closestPoints.push_back({ currentPosition.x + i, currentPosition.y - distance + i });
			}
		}

		if(showFinding)
		{
			window.display();
			sf::sleep(sf::milliseconds(Con::shortDistanceDelay));
		}
		distance++;
	}

	//Prepare for moves vector
	const sf::Vector2i connectTile = closestPoints.at(rand()%closestPoints.size());
	int xMove;
	int yMove;

	if (connectTile.x > currentPosition.x) xMove = 0;
	else xMove = 2;
	if (connectTile.y > currentPosition.y) yMove = 1;
	else yMove = 3;

	//Add the needed moves to a vector
	std::vector<int> moves;
	for (int i = 0, k = std::abs(connectTile.x - currentPosition.x); i < k; i++)moves.push_back(xMove);
	for (int i = 0, k = std::abs(connectTile.y - currentPosition.y); i < k; i++)moves.push_back(yMove);

	//Randomise the moves
	const int movesSize{ static_cast<const int>(moves.size()) };
	for (int i = 0; i < movesSize; i++)
	{
		const int randomIndex{ rand() % movesSize };
		const int temp = moves[i];
		moves[i] = moves[randomIndex];
		moves[randomIndex] = temp;
	}

	while(!moves.empty())
	{
		if(showFinding)
		{
			window.clear();	
			draw();
		}

		const int direction{ moves.back() };
		moves.pop_back();
		tilesLeft--;

		tiles.setSteppedOn(currentPosition.x, currentPosition.y, true);
		removeWall(currentPosition.x, currentPosition.y, direction);
		drawTile(currentPosition.x, currentPosition.y);

		switch (direction)
		{
		case 0:
			currentPosition.x++;
			break;
		case 1:
			currentPosition.y++;
			break;
		case 2:
			currentPosition.x--;
			break;
		case 3:
			currentPosition.y--;
		}

		if(showFinding)
		{
			window.display();
			sf::sleep(sf::milliseconds(Con::shortDistanceDelay));
		}
	}

	drawTile(currentPosition.x, currentPosition.y);
	draw();
	return true;
}


