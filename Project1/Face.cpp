#include <iostream>
#include "Face.h"
#include <vector>
#define N 3

using namespace std;

Face::Face() {}
vector<int> Face::getIndexesOfVertexes()
{
	return indexesOfVertexes;
}
void Face::addVertexIndex(int v)
{
	indexesOfVertexes.push_back(v);
}
