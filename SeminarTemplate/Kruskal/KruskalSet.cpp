#include "stdafx.h"
#include "KruskalSet.h"

KruskalSet::KruskalSet(int width, int height)
	:width(width), height(height), set(new int[width*height])
{
	for (int i = 0, m = width * height; i < m; i++)
	{
		set[i] = i;
	}
}

bool KruskalSet::isSameSet(KruskalWall& tempWall) const
{
	return set[tempWall.x1 + tempWall.y1*width]==set[tempWall.x2 + tempWall.y2*width];
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

int KruskalSet::getSetNumber(int x, int y)
{
	return set[x + y * width];
}


KruskalSet::~KruskalSet()
{
	delete[]set;
}
