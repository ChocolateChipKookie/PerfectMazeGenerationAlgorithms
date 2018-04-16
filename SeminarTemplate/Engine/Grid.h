#pragma once
#include <SFML/Graphics.hpp>
#include "../Constants.h"

typedef struct Tile {
	bool walls[Con::walls];
	bool steppedOn;
}Tile;

class Tiles
{
public:
	///Constructor
	Tiles(int width, int height);

	~Tiles();

	///Get the tile structure for a certin position
	Tile getTile(int x, int y) const;
	///Set the wall flag for a certin position
	void setWall(int x, int y, int wall, bool deleteWall);
	///Set stepped on flag for a certin position
	void setSteppedOn(int x, int y, bool steppedOn) const;

private:

	///Masks for flags
	int masks[4]{ 1, 2, 4, 8 };
	int steppedOnMask{ 16 };

	///Flag array and array dimensions
	unsigned char* arr;
	int height;
	int width;
};

class Grid
{
public:
	///Constructor
	Grid(int width, int height, int size);
	///Draw all tiles to the gridTexture
	void drawAll();

	///Draw only one tile to the gridTexture
	void drawTile(int x, int y);
	///Draw the grid texture to the renderWindow
	void draw();

	///Remove a wall on a certin position
	void removeWall(int x, int y, int wall);

	sf::RenderWindow window;

private:
	sf::RenderTexture gridTexture;

	///Rectangles used for drawing
	sf::RectangleShape freeTileRect;
	sf::RectangleShape horisontalLineRect;
	sf::RectangleShape veritcalLineRect;
	sf::RectangleShape steppedOnRect;

protected:
	///Tiles and grid dimensions
	Tiles tiles;

	int width;
	int height;
	int size;
};

