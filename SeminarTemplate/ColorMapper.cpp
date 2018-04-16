#include "stdafx.h"
#include "ColorMapper.h"
#include <cstdint>

sf::Color ColorMapper::mapColor(int start, int end, int current, sf::Color startColor, sf::Color endColor)
{
	int range{ end - start };

	double multiplier = static_cast<double>(current) / static_cast<double>(range);

	int8_t r = static_cast<int8_t>(static_cast<double>(static_cast<int8_t>(endColor.r) - static_cast<int8_t>(startColor.r))*multiplier);
	int8_t g = static_cast<int8_t>(static_cast<double>(static_cast<int8_t>(endColor.g) - static_cast<int8_t>(startColor.g))*multiplier);
	int8_t b = static_cast<int8_t>(static_cast<double>(static_cast<int8_t>(endColor.b) - static_cast<int8_t>(startColor.b))*multiplier);

	return {	static_cast<uint8_t>(static_cast<int8_t>(startColor.r) + r),
				static_cast<uint8_t>(static_cast<int8_t>(startColor.g) + g),
				static_cast<uint8_t>(static_cast<int8_t>(startColor.b) + b)};
}
