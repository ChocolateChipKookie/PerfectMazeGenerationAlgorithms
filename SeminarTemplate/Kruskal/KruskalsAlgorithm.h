#pragma once
#include "../Engine/Algorithms.h"
#include "../Engine/Grid.h"

typedef struct { int x1, y1, x2, y2; }KruskalWall;

class KruskalSet
{
public:
	///Constructor
	KruskalSet(int width, int height);
	~KruskalSet();
	///Returns true if the 2 tiles are in the same set
	bool isSameSet(KruskalWall& tempWall)const;
	///Join 2 different sets
	void joinSets(KruskalWall& tempWall)const;
	///Get the set number for a certin position
	int getSetNumber(int x, int y) const;
private:
	int *set;
	int width, height;
};

class KruskalsAlgorithm: public Grid, Algorithms
{
public:
	///Constructor
	KruskalsAlgorithm(bool numbersEnabled = false);
	///Move 1 move
	bool nextMove() override;
	
private:
	
	KruskalSet set;

	bool numbersEnabled;
	sf::Font font;
	sf::Text text;

	std::vector<KruskalWall> walls{};
};
