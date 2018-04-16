#include "stdafx.h"
#include "KruskalsAlgorithm.h"

KruskalSet::KruskalSet(int width, int height)
	:width(width), height(height), set(new int[width*height])
{
	//Gives every tile its own set
	for (int i = 0, m = width * height; i < m; i++)
	{
		set[i] = i;
	}
}

bool KruskalSet::isSameSet(KruskalWall& tempWall) const
{
	return set[tempWall.x1 + tempWall.y1*width] == set[tempWall.x2 + tempWall.y2*width];
}

void KruskalSet::joinSets(KruskalWall& tempWall) const
{
	int temp1{ set[tempWall.x1 + tempWall.y1*width] };
	int temp2{ set[tempWall.x2 + tempWall.y2*width] };
	for (int i = 0, m = width * height; i < m; i++)
	{
		if (set[i] == temp2) set[i] = temp1;
	}
}

int KruskalSet::getSetNumber(int x, int y) const
{
	return set[x + y * width];
}

KruskalSet::~KruskalSet()
{
	delete[]set;
}

KruskalsAlgorithm::KruskalsAlgorithm(bool numbersEnabled)
	:Grid(Con::width, Con::height, Con::size), set(Con::width, Con::height), numbersEnabled(numbersEnabled)
{
	//Adds all possible walls
	for (int i = 0; i < width; i++)
	{
		for (int j = 0, m = height - 1; j < m; j++)
		{
			walls.push_back({ i, j, i, j + 1 });
		}
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0, m = width - 1; j < m; j++)
		{
			walls.push_back({ j, i, j + 1, i });
		}
	}

	//Randomises walls
	for (int i = 0, k = walls.size(); i < k; i++)
	{
		int randomNumber{ static_cast<int>( rand() % walls.size()) };

		KruskalWall temp = walls[i];
		walls[i] = walls[randomNumber];
		walls[randomNumber] = temp;
	}

	if(numbersEnabled)
	{
		font.loadFromFile("arial.ttf");

		text = sf::Text("100", font);
		text.setCharacterSize(30);
		text.setStyle(sf::Text::Regular);
		text.setFillColor(sf::Color::Black);
	}

	drawAll();
	draw();
}

bool KruskalsAlgorithm::nextMove()
{
	while(true)
	{
		if (walls.size() == 0)
		{
			//If the set algorithm is done, it only draws the grid texture
			draw();
			return false;
		}


		//Gets and pops last wall in vector
		KruskalWall& tempWall = walls.at(walls.size() - 1);
		walls.pop_back();

		//If the wall is between 2 tiles of different sets, it breaks a wall and joins the sets
		if (!set.isSameSet(tempWall))
		{
			tiles.setSteppedOn(tempWall.x1, tempWall.y1, true);
			tiles.setSteppedOn(tempWall.x2, tempWall.y2, true);

			int direction{ 0 };
			if (tempWall.x1 == tempWall.x2)direction = 1;

			removeWall(tempWall.x1, tempWall.y1, direction);
			drawTile(tempWall.x1, tempWall.y1);
			drawTile(tempWall.x2, tempWall.y2);

			set.joinSets(tempWall);
			break;
		}
	}

	draw();

	//If this option is enabled, it draws numbers of sets for every single tile
	if(numbersEnabled)
	{
		for (int i = 0; i<Con::height; i++)
		{
			for (int j = 0; j<Con::width; j++)
			{
				text.setString(std::to_string(set.getSetNumber(j, i)));
				text.setPosition({ static_cast<float>(j*Con::size), static_cast<float>(i*Con::size) });
				window.draw(text);
			}
		}
	}

	return true;
}
