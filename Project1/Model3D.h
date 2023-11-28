#pragma once
#include "Vertex.h"
#include "Face.h"
#include "TransformationMatrix.h"
#define N 4
using namespace std;

class Model3D
{
private:
	vector<Vertex> vertexes;
	vector<Face> faces;
	float midPointModel[N];
	TransformationMatrix transform;
public:
	float matrix[N][N];
	void addVertex(const Vertex& vertex);
	void addFace(const Face& face);
	vector<Vertex> getVertexes();
	vector<Face> getFaces();
	void calculatePM();
	void createModelMatrix();
	void rotate(float angle, char axis);
	void translate(float traslation[N]);
	void rotateAndTranslate(float angle, char axis, float traslation[N]);
};

