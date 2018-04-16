#include "stdafx.h"
#include "Grid.h"
#include <SFML/Graphics.hpp>
#include "../Constants.h"

Tiles::Tiles(int width, int height)
	:width(width), height(height)
{
	//Allocating new array and setting the initial values
	arr = new unsigned char[width*height];

	for (int i = 0, k = width * height; i < k; i++)
	{
		arr[i] = static_cast<unsigned char>(15);
	}
}

Tile Tiles::getTile(int x, int y) const
{
	//Throw exception if out of bounds
	if (x < 0 || x >= width || y < 0 || y >= height)throw std::exception("Coordinates out of bounds!");

	//Get flags for the position
	const unsigned char temp = arr[y*width + x];
	Tile returnTile;
	int mask = 1;

	//Copy flags to returnTile
	for (bool& wall : returnTile.walls)
	{
		wall = temp & mask;
		mask = mask << 1;
	}

	returnTile.steppedOn = temp & mask;

	return returnTile;
}

void Tiles::setWall(int x, int y, int wall, bool wallValue)
{
	//Throw exception if out of bounds
	if (x < 0 || x >= width || y < 0 || y >= height)throw std::exception("Coordinates out of bounds!");
	//Return if invalid wall direction
	if (wall < 0 || wall>3)return;

	//Load mask and reference
	unsigned char& temp = arr[y*width + x];
	unsigned char mask = masks[wall];

	//Set flag
	if (wallValue)
	{
		temp = temp | mask;
	}
	else
	{
		mask = ~mask;
		temp = temp & mask;
	}
}

void Tiles::setSteppedOn(int x, int y, bool steppedOn) const
{
	//Throw exception if out of bounds
	if (x < 0 || x >= width || y < 0 || y >= height)throw std::exception("Coordinates out of bounds!");

	//Load mask and set reference
	unsigned char& temp = arr[y*width + x];
	unsigned char mask = steppedOnMask;

	if (steppedOn)
	{
		temp = temp | mask;
	}
	else
	{
		mask = ~mask;
		temp = temp & mask;
	}
}

Tiles::~Tiles() {
	delete[]arr;
}

Grid::Grid(int width, int height, int size)
	: width(width), height(height), size(size), tiles(Tiles(width, height))
{
	//Create all needed resources for drawing grid
	window.create(sf::VideoMode(width*size, height*size), "Grid window");
	gridTexture.create(width*size, height*size);

	freeTileRect.setSize({ static_cast<float>(size - 2 * Con::gridThickness), static_cast<float>(size - 2 * Con::gridThickness) });
	freeTileRect.setFillColor(Con::backgroundColor);
	freeTileRect.setOutlineThickness(static_cast<float>(Con::gridThickness));
	freeTileRect.setOutlineColor(Con::gridColor);

	horisontalLineRect.setSize({ static_cast<float>(size), static_cast<float>(Con::gridThickness) });
	horisontalLineRect.setFillColor(Con::gridColor);

	veritcalLineRect.setSize({ static_cast<float>(Con::gridThickness), static_cast<float>(size) });
	veritcalLineRect.setFillColor(Con::gridColor);

	steppedOnRect.setSize({ static_cast<float>(size), static_cast<float>(size) });
	steppedOnRect.setFillColor(Con::steppedOnColor);
}

void Grid::drawAll()
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			drawTile(j, i);
		}
	}
}

void Grid::draw()
{
	//Display the gridTexture and copy it to a sprite which is drawn to the window
	gridTexture.display();
	sf::Sprite temp = sf::Sprite(gridTexture.getTexture());
	window.draw(temp);
}

void Grid::drawTile(int x, int y)
{
	Tile tempTile = tiles.getTile(x, y);

	if (!tempTile.steppedOn) {
		//Draw not stepped on rect
		freeTileRect.setPosition({ static_cast<float>(x*size + Con::gridThickness), static_cast<float>(y*size + Con::gridThickness) });
		gridTexture.draw(freeTileRect);
	}
	else {
		//Draw stepped on rect
		steppedOnRect.setPosition({ static_cast<float>(x*size), static_cast<float>(y*size) });
		gridTexture.draw(steppedOnRect);

		if (tempTile.walls[0]) {
			veritcalLineRect.setPosition({ static_cast<float>((x + 1)*size - Con::gridThickness), static_cast<float>(y*size) });
			gridTexture.draw(veritcalLineRect);
		}
		if (tempTile.walls[1]) {
			horisontalLineRect.setPosition({ static_cast<float>(x*size), static_cast<float>((y + 1)*size - Con::gridThickness) });
			gridTexture.draw(horisontalLineRect);
		}
		if (tempTile.walls[2]) {
			veritcalLineRect.setPosition({ static_cast<float>(x*size), static_cast<float>(y*size) });
			gridTexture.draw(veritcalLineRect);
		}
		if (tempTile.walls[3]) {
			horisontalLineRect.setPosition({ static_cast<float>(x*size), static_cast<float>(y*size) });
			gridTexture.draw(horisontalLineRect);
		}
	}
}

void Grid::removeWall(int x, int y, int wall)
{
	//Remove a wall between 2 tiles
	tiles.setWall(x, y, wall, false);
	drawTile(x, y);

	switch(wall)
	{
	case 0:
		x++;
		break;
	case 1:
		y++;
		break;
	case 2:
		x--;
		break;
	case 3:
		y--;
	}

	if( x >= 0 && x < width && 
		y >= 0 && y < height)
	{
		tiles.setWall(x, y, (wall + 2) % Con::walls, false);
	}

	drawTile(x, y);
	Tile tile = tiles.getTile(x, y);

}
