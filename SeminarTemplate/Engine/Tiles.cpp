#include "stdafx.h"
#include "Tiles.h"
#include <exception>

Tiles::Tiles(int width, int height)
	:width(width), height(height)
{
	arr = new unsigned char[width*height];

	for (int i = 0, k = width * height; i < k; i++)
	{
		arr[i] = static_cast<unsigned char>(15);
	}
}

Tile Tiles::getTile(int x, int y) const
{
	if (x < 0 || x >= width || y < 0 || y >= height)throw std::exception("Coordinates out of bounds!");

	const unsigned char temp = arr[y*width + x];
	Tile returnTile;
	int mask = 1;

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
	if (x < 0 || x >= width || y < 0 || y >= height)throw std::exception("Coordinates out of bounds!");

	if (wall < 0 || wall>3)return;

	unsigned char temp = arr[y*width + x];
	unsigned char mask = masks[wall];

	if(wallValue)
	{
		temp = temp | mask;
	}
	else
	{
		mask = ~mask;
		temp = temp & mask;
	}

	arr[y*width + x] = temp;
}

void Tiles::setSteppedOn(int x, int y, bool steppedOn) const
{
	if (x < 0 || x >= width || y < 0 || y >= height)throw std::exception("Coordinates out of bounds!");

	unsigned char temp = arr[y*width + x];
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

	arr[y*width + x] = temp;
}
