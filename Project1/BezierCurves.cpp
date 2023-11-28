#include "BezierCurves.h"
#include <iostream>
#include "Point.h"
#include <cmath>

using namespace std;

void BezierCurves::cubicBezier(float t, Point P0, Point P1, Point P2, Point P3, Point* Pend)
{
	Pend->setX(pow(1 - t, 3) * P0.getX() + 3 * t * pow(1 - t, 2) * P1.getX() + 3 * pow(t, 2) * (1 - t) * P2.getX() + pow(t, 3) * P3.getX() );
	Pend->setY(pow(1 - t, 3) * P0.getY() + 3 * t * pow(1 - t, 2) * P1.getY() + 3 * pow(t, 2) * (1 - t) * P2.getY() + pow(t, 3) * P3.getY());
	Pend->setZ(pow(1 - t, 3) * P0.getZ() + 3 * t * pow(1 - t, 2) * P1.getZ() + 3 * pow(t, 2) * (1 - t) * P2.getZ() + pow(t, 3) * P3.getZ());
}