#pragma once
#include <vector>
#define N 4

using namespace std;

class TransformationMatrix
{
	private:
		static void createMIdentity(float mat[N][N]);
		static void createMRotation(float mrotation[N][N], float angle, char axis);
		static void createMTranslation(float mTraslation[N][N], float traslation[N]);
		static void createMEscalation();
		static void multMatrix(float mat1[N][N], float mat2[N][N]);
		static void printMat(float mat[N][N]);
	public:
		static void rotation(float angle, char axis, float matrix[N][N]);
		static void translation(float translation[N], float matrix[N][N]);
		static void createModelMatrix(float matrix[N][N], float PM[N]);
};

