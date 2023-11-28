#pragma once
class Point
{
private:
	float x;
	float y;
	float z;
public:
	Point(float _x, float _y, float _z);
	void setX(float _x);
	void setY(float _y);
	void setZ(float _z);
	float getX();
	float getY();
	float getZ();
};

