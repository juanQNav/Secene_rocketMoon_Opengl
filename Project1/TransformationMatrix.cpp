#include <iostream>
#include "TransformationMatrix.h"
#include <cmath>
#include <vector>
#define N 4
#define MY_PI 3.14159265358979323846
using namespace std;

void TransformationMatrix::rotation(float angle, char axis, float modelMatrix[N][N])
{
	float mrot[N][N];
	createMRotation(mrot, angle, axis);
    //cout << endl << "Matrix Rotation in angle " << angle << " and axis " << axis << endl;
    //printMat(mrot);
    //cout << endl;
	multMatrix(modelMatrix, mrot);
}
void TransformationMatrix::translation(float traslation[N], float modelMatrix[N][N])
{
    float mTraslation[N][N];
    createMTranslation(mTraslation, traslation);
    //cout << endl << "Matrix Traslation x = "<<traslation[0]<<" y = "<< traslation[1]<<" z = " << traslation[2] << endl;
    //printMat(mTraslation);
    multMatrix(modelMatrix, mTraslation);
}
void TransformationMatrix::createModelMatrix(float matrix[N][N], float PM[N])
{
    createMIdentity(matrix);

    matrix[0][3] = PM[0];
    matrix[1][3] = PM[1];
    matrix[2][3] = PM[2];
    matrix[3][3] = PM[3];

}
void TransformationMatrix::createMIdentity(float mat[N][N])
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (i == j)
                mat[i][j] = 1;
            else
                mat[i][j] = 0;
}
void TransformationMatrix::createMRotation(float mrotation[N][N], float angle, char axis)
{
    angle = angle * (MY_PI / 180.0);  // Convierte el ángulo a radianes

    switch (axis) {
    case 'x':
        mrotation[0][0] = 1;
        mrotation[0][1] = 0;
        mrotation[0][2] = 0;
        mrotation[0][3] = 0;
        mrotation[1][0] = 0;
        mrotation[1][1] = cos(angle);
        mrotation[1][2] = -sin(angle);
        mrotation[1][3] = 0;
        mrotation[2][0] = 0;
        mrotation[2][1] = sin(angle);
        mrotation[2][2] = cos(angle);
        mrotation[2][3] = 0;
        mrotation[3][0] = 0;
        mrotation[3][1] = 0;
        mrotation[3][2] = 0;
        mrotation[3][3] = 1;
        break;
    case 'y':
        mrotation[0][0] = cos(angle);
        mrotation[0][1] = 0;
        mrotation[0][2] = sin(angle);
        mrotation[0][3] = 0;
        mrotation[1][0] = 0;
        mrotation[1][1] = 1;
        mrotation[1][2] = 0;
        mrotation[1][3] = 0;
        mrotation[2][0] = -sin(angle);
        mrotation[2][1] = 0;
        mrotation[2][2] = cos(angle);
        mrotation[2][3] = 0;
        mrotation[3][0] = 0;
        mrotation[3][1] = 0;
        mrotation[3][2] = 0;
        mrotation[3][3] = 1;
        break;
    case 'z':
        mrotation[0][0] = cos(angle);
        mrotation[0][1] = -sin(angle);
        mrotation[0][2] = 0;
        mrotation[0][3] = 0;
        mrotation[1][0] = sin(angle);
        mrotation[1][1] = cos(angle);
        mrotation[1][2] = 0;
        mrotation[1][3] = 0;
        mrotation[2][0] = 0;
        mrotation[2][1] = 0;
        mrotation[2][2] = 1;
        mrotation[2][3] = 0;
        mrotation[3][0] = 0;
        mrotation[3][1] = 0;
        mrotation[3][2] = 0;
        mrotation[3][3] = 1;
        break;
    default:
        cout << "Unrecognized axis error";
        break;
    }
}

void TransformationMatrix::createMTranslation(float mTraslation[N][N], float traslation[N])
{
    createMIdentity(mTraslation);
    
    mTraslation[0][3] = traslation[0];
    mTraslation[1][3] = traslation[1];
    mTraslation[2][3] = traslation[2];
}
void TransformationMatrix::createMEscalation()
{
    //coming soon
}
void TransformationMatrix::multMatrix(float mat1[N][N], float mat2[N][N])
{
	float res[N][N];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			res[i][j] = 0;
			for (int k = 0; k < N; k++)
 				res[i][j] += mat1[i][k] * mat2[k][j];
        }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mat1[i][j] = res[i][j];


    //cout << "Result of multiplication"<<endl;
	//printMat(mat1);
}

void TransformationMatrix::printMat(float mat[N][N])
{
	for (int i = 0; i < N; i++)
	{
        cout << "(";
		for (int j = 0; j < N; j++)
		{
			if(j == 3)
                cout << mat[i][j];
			else
                cout << mat[i][j]<<", ";
		}
        cout << ")" << endl;
	}
}
