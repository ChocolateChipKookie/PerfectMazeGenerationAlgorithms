// SeminarTemplate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <thread>
#include "Engine/Grid.h"
#include "Prim/PrimsAlgorithm.h"
#include "MsgBox.h"
#include <iostream>
#include "Kruskal/KruskalsAlgorithm.h"
#include "ShortestDistanceMaze.h"
#include "DepthFirstAlgorithm.h"

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	
	//Choose maze type
	//ShortestDistanceMaze maze(false);
	//ShortestDistanceMaze maze;
	//PrimsAlgorithm maze;
	//KruskalsAlgorithm maze;
	//KruskalsAlgorithm maze(true);
	DepthFirstAlgorithm maze;

	bool mazeRunning{ true };

	while (maze.window.isOpen())
	{
		sf::Event event;
		while (maze.window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				maze.window.close();
		}

		maze.window.clear(sf::Color::Blue);
		if (!maze.nextMove() && mazeRunning) {
			mazeRunning = false;
			MsgBox("Maze finished!", "Activity");			
		}

		maze.window.display();

		sf::sleep(sf::milliseconds(Con::delay));
	}

	return 0;
}
