#pragma once
#include <cstdint>
#include "../Constants.h"

typedef struct Tile {
	bool walls[Con::walls];
	bool steppedOn;
}Tile;

class Tiles
{
public:
	Tiles(int width, int height);

	Tile getTile(int x, int y) const;
	void setWall(int x, int y, int wall, bool deleteWall);
	void setSteppedOn(int x, int y, bool steppedOn) const;

private:

	int masks[4]{ 1, 2, 4, 8 };
	int steppedOnMask{ 16 };

	unsigned char* arr;
	int height;
	int width;
};
