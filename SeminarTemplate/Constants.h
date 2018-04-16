#pragma once
#include "SFML/Graphics/Color.hpp"

///Global constants
namespace Con
{
	///Width of the array
	static int width{ 30 };
	///Height of the array
	static int height{ 30 };
	///Size of one tile
	static int size{ 20 };
	///Delay between moves/rendering
	static int delay{ 20 };
	///Shortest distance delay
	static int shortDistanceDelay{ 5 };
	///Number of walls each cell has
	const int walls{ 4 };
	
	///Background color/color of tiles that are not touched
	static sf::Color backgroundColor{ sf::Color::Black};
	///Color of the grid
	static sf::Color gridColor{ sf::Color::Black };
	///Depth first
	static sf::Color DFTileColor{sf::Color::Cyan};
	
	///Color of a tile that has been stepped on
	static sf::Color steppedOnColor {sf::Color::White};
	///Thickness of the grid/walls
	static int gridThickness{ 1 };
}