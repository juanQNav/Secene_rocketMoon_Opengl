#pragma once
#include <vector>
#define N 4
using namespace std;

class Face
{
private:
	vector<int> indexesOfVertexes;
public:
	Face();
	void addVertexIndex(int v);
	vector<int> getIndexesOfVertexes();
};

