#include <iostream>
#include "Model3D.h"
#include <vector>
#include "Vertex.h"
#include "Face.h"

#define N 4

using namespace std;

void Model3D::addVertex(const Vertex& vertex)
{
	vertexes.push_back(vertex);
}

void Model3D::addFace(const Face& face)
{
	faces.push_back(face);
}
vector<Vertex> Model3D::getVertexes()
{
	return vertexes;
}
vector<Face> Model3D::getFaces()
{
	return faces;
}

void Model3D::calculatePM()
{
	for (int i = 0; i < vertexes.size(); i++)
	{
		midPointModel[0] += vertexes[i].getX();
		midPointModel[1] += vertexes[i].getY();
		midPointModel[2] += vertexes[i].getZ();
	}

	midPointModel[0] = midPointModel[0] / (vertexes.size());
	midPointModel[1] = midPointModel[1] / (vertexes.size());
	midPointModel[2] = midPointModel[2] / (vertexes.size());

	midPointModel[3] = 1;

	//cout << "PM" << endl;
	//cout << "(" << midPointModel[0] << ", " << midPointModel[1] << ", " << midPointModel[2] << ")"<<endl;
}
void Model3D::createModelMatrix()
{
	transform.createModelMatrix(matrix, midPointModel);
}
void Model3D::rotate(float angle, char axis)
{
	transform.rotation(angle, axis, matrix);
}
void Model3D::translate(float traslation[N])
{
	transform.translation(traslation, matrix);
}
void Model3D::rotateAndTranslate(float angle, char axis, float traslation[N])
{
	transform.translation(traslation, matrix);
}
