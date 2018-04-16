#pragma once
#include <SFML/Graphics/Color.hpp>

class ColorMapper
{
public:
	static sf::Color mapColor(int start, int end, int current, sf::Color startColor, sf::Color endColor);
};
