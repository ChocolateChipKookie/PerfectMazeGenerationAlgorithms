#pragma once

typedef struct {int x1, y1, x2, y2;}KruskalWall;

class KruskalSet
{
public:
	KruskalSet(int width, int height);

	bool isSameSet(KruskalWall& tempWall)const;
	void joinSets(KruskalWall& tempWall)const;
	int getSetNumber(int x, int y);

	~KruskalSet();

private:
	int *set;
	int width, height;
};
