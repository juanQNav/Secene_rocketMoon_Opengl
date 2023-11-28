#pragma once
#include "Point.h"


class BezierCurves
{
	public:
		static void cubicBezier(float t,Point P0, Point P1, Point P2, Point P3, Point* Pend);
};

