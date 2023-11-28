#pragma once
#include <vector>

using namespace std;

class Matrix
{
	protected: 
		float matrix[4][4];
	public:
		virtual void transformation();
};

