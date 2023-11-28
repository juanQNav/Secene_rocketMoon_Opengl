#include "Vertex.h"

Vertex::Vertex(){
	x = 0;
	y = 0;
	z = 0;
}
void Vertex::setX(float _x)
{
	x = _x;
}
void Vertex::setY(float _y)
{
	y = _y;
}
void Vertex::setZ(float _z)
{
	z = _z;
}
float Vertex::getX()
{
	return x;
}
float Vertex::getY()
{
	return y;
}
float Vertex::getZ()
{
	return z;
}