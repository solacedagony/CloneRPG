#pragma once
#include <vector>
using std::vector;

class CRandomizer
{
public:
	CRandomizer(void);
	~CRandomizer(void);

	static int index;
	int maxIndex;
	int randomInteger( int startingPoint, int endingPoint );

private:
	vector<int> randomList;
};

