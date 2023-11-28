#pragma once
#include <stdio.h>
#include "Matrix.h"

using namespace std;


class Rotation : public Matrix
{
	public:
		void transformation() override;
};

