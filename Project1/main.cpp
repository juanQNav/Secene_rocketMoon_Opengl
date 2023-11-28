#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Model3D.h"
#include "Vertex.h"
#include "Face.h"
#include "TransformationMatrix.h"
#include <fstream>
#include <string>
#include "BezierCurves.h"
#include "Point.h"
#include <math.h>

#define N 4
#define MY_PI 3.14159265358979323846
#define NCURVES 3
#define CURVE_N1 0
#define CURVE_N2 1
#define CURVE_N3 2
#define T_INCREMENTS 0.00455

using namespace std;

//funciton prototypes 
void init(void);
void display(void);
void readObj(Model3D& model,string phat);
void printModel3D(Model3D model);
void transformVertex(float matrixModel[N][N], float vertexToTrasnform[N], float vertexToPlot[N]);
void drawScene();
void driverKeyboard(unsigned char key, int x, int y);
void mouseWheel(int wheel, int direction, int x, int y);

// movement camera
const float value_movement = 0.5;

//models
vector <Model3D> models;

//colors
float colorsCohete[][3] = {
	{0.9, 0.0, 0.0}, 
	{0.8, 0.2, 0.2}, 
	{0.7, 0.4, 0.4}, 
	{0.6, 0.3, 0.3}, 
	{0.5, 0.2, 0.3}, 
	{1.4, 0.1, 0.2}  
};

float colors2[][3] = {
	{0.0, 0.0, 1.0}, 
	{0.2, 0.5, 0.9}, 
	{0.2, 0.3, 0.4}  
};

//ligth
float ambientIntensity = 0.3;
float diffuseIntensity = 0.09;
float ambient[] = {1, 1, 1 };

float lightDirection[] = { -8, 3, -4};

//rotate
float rotationAngle = 0.0f;  // Initial rotation angle
float rotationAngleC = 0.0f;  // Initial rotation angle
float rotationAngleC2 = 0.0f;  // Initial rotation angle
const int rotationInterval = 15;  // Rotation interval in milliseconds
int lastRotationTime = 0;  // Last time the rotation was updated

//bezier
Point PA(-15, 2, 0), PB(0, -4, 15), PC(18, -5, 0), PD(-10, 0, -15), PE(-25, 5, -30), PF(0, 10,-45), PG(13, -2, -30), PH(10,0,-15), Pend(0, 0, 0);
float t = 0;
BezierCurves curve;
int curveCount = 0;
int curves[] = { 0,1,2 };


//interactivity
bool pause = false;
float eye_x = -12.0, eye_y = 0.0, eye_z = 18.0, center_x = 1.6, center_y = 0.0, center_z = 1.0;

/*
 *  Declare initial window size, position, and display mode
 *  (single buffer and RGBA).  Open window with "hello"
 *  in its title bar.  Call initialization routines.
 *  Register callback function to display graphics.
 *  Enter main loop and process events.
 */


int main(int argc, char** argv)
{	
	int numModels;
	char resp;
	
	cout << "ingresara rutas? (s/n): ";
	cin >> resp;

	if (resp == 's')
	{
		cout << "Ingrese la cantidad de modelos a generar: ";
		cin >> numModels;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		for (int i = 0; i < numModels; i++)
		{
			Model3D modelaux;
			readObj(modelaux, "");
			models.push_back(modelaux);
		}
	}
	else
	{	
			Model3D modelaux;
			readObj(modelaux, "C:/Users/juanq/Documents/UASLP/S5/Graficacion_por_Computadora/Proyecto_Graficacion/models/rocket/rocket.obj");
			models.push_back(modelaux);
			Model3D modelaux2;
			readObj(modelaux2, "C:/Users/juanq/Documents/UASLP/S5/Graficacion_por_Computadora/Proyecto_Graficacion/models/moon2/moon2.obj");
			models.push_back(modelaux2);
			Model3D modelaux3;
			readObj(modelaux3, "C:/Users/juanq/Documents/UASLP/S5/Graficacion_por_Computadora/Proyecto_Graficacion/models/moon2/moon2.obj");
			models.push_back(modelaux3);
	}
	
	//printModel3D(models[0]);

	for (Model3D model : models)
		model.calculatePM();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("MODEL V2");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(driverKeyboard);
	glutMouseWheelFunc(mouseWheel);
	glutIdleFunc(display);
	
	glutMainLoop();

	return 0;   /* ISO C requires main to return int. */
}

//functionss5fxtvc
void init(void)
{
	/*  select clearing (background) color       */
	glClearColor(0.02f, 0.06f, 0.1f, 1.0f);

	/*  initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		eye_x, eye_y, eye_z, center_x, center_y, center_z,
		0.0, 1.0, 0.0
	);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);
}
void display(void)
{
	if (!pause) {
		// Calculate the time difference since the last rotation update
		int currentTime = glutGet(GLUT_ELAPSED_TIME);
		int deltaTime = currentTime - lastRotationTime;

		// Check if it's time to update the rotation
		if (deltaTime >= rotationInterval)
		{
			rotationAngle += 2.0f;
			t += T_INCREMENTS;

			switch (curveCount)
			{
			case CURVE_N1:
				rotationAngleC += 130/(1/T_INCREMENTS);
				break;
			case CURVE_N2:
				rotationAngleC -= 230/(1/T_INCREMENTS);
				break;
			case CURVE_N3:
				if(t < 0.55)
					rotationAngleC -= 40 / (1 / T_INCREMENTS);
				else
					rotationAngleC += 270 / (1 / T_INCREMENTS);
				break;
			default:
				break;
			}

			if (rotationAngle > 360.0f)
				rotationAngle = 0.0f;
			if (rotationAngleC > 360.0f) {
				rotationAngleC = 0.0f;
			}
			if (t > 1)
			{
				t = 0;
				curveCount = (curveCount + 1) % NCURVES;
			}

			lastRotationTime = currentTime;
		}

		/* Limpiar todos los píxeles */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
		//lookat
		gluLookAt(
			eye_x, eye_y, eye_z, 
			center_x + eye_x, center_y + eye_y, eye_z -4,
			0.0, 1.0, 0.0
		);
		

		//create model matrix
		for (int i = 0; i < models.size(); i++)
		{
			models[i].createModelMatrix();
		}

		//bezier curve

		switch (curveCount)
		{
			case CURVE_N1:
				curve.cubicBezier(t, PA, PB, PC, PD, &Pend);
				break;
			case CURVE_N2:
				curve.cubicBezier(t, PD, PE, PF, PG, &Pend);
				break;
			case CURVE_N3:
				curve.cubicBezier(t, PG, PH, PD, PA, &Pend);
				break;
			default:
				break;
		}
		float Tpo1[N] = { Pend.getX(), Pend.getY(), Pend.getZ(), 1 };
		models[0].translate(Tpo1);


		// Apply the rotation
		
		//Cohete
		models[0].rotate(rotationAngleC, 'y');
		models[0].rotate(rotationAngle, 'x');
		
		//moon1
		models[1].rotate(rotationAngle, 'y');
		//models[1].rotate(rotationAngle, 'x');

		//moon2
		float Tpo2[N] = {-1, 2, -30, 1 };
		models[2].translate(Tpo2);
		models[2].rotate(rotationAngle, 'y');
		models[2].rotate(rotationAngle, 'x');

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		drawScene();

		glutSwapBuffers();
		glFlush();
	}else{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
		//lookat
		gluLookAt(
			eye_x, eye_y, eye_z,
			center_x + eye_x, center_y + eye_y, eye_z - 4,
			0.0, 1.0, 0.0
		);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		drawScene();

		glutSwapBuffers();
		glFlush();
	}
}
void readObj(Model3D& model, string phat)
{
	ifstream file;
	string  fileName, line;
	char detonation;

	if (phat.empty()) 
	{
		cout << "Ingrese la ruta: ";
		getline(cin, fileName);
	}
	else
		fileName = phat;
	
	file.open(fileName, ios::in);

	if (file.fail())
	{
		cout << "Error al abrir el archivo";
		exit(1);
	}

	while (!file.eof())
	{
		getline(file, line);
		detonation = line[0];

		if (detonation == 'v')
		{
			float x, y, z;
			if (sscanf_s(line.c_str(), "v %f %f %f", &x, &y, &z) == 3)
			{
				Vertex vertex;
				vertex.setX(x);
				vertex.setY(y);
				vertex.setZ(z);
				model.addVertex(vertex);
			}
		}
		else if (detonation == 'f')
		{
			Face face;
			int v1, v2, v3;
			if (sscanf_s(line.c_str(), "f %d %d %d", &v1, &v2, &v3) == 3)
			{
				face.addVertexIndex(v1);
				face.addVertexIndex(v2);
				face.addVertexIndex(v3);
				model.addFace(face);
			}
		}
	}

	file.close();
}
void printModel3D(Model3D model)
{
	vector<Vertex> vertexes = model.getVertexes();
	vector<Face> faces = model.getFaces();

	//vertex
	for (int i = 0; i < vertexes.size(); i++)
	{
		cout << "v " << vertexes[i].getX() << " " << vertexes[i].getY() << " " << vertexes[i].getZ() << endl;
	}

	//faces
	for (int i = 0; i < faces.size(); i++)
	{
		cout << "f " << faces[i].getIndexesOfVertexes()[0] << " " << faces[i].getIndexesOfVertexes()[1] << " " << faces[i].getIndexesOfVertexes()[2] << endl;
	}
	
	//face and vertex
	for (int i = 0; i < faces.size(); i++)
	{
		cout << "Face " << i << ": ";
		for (int j = 0; j < 3; j++)
		{
			cout << "[" << vertexes[faces[i].getIndexesOfVertexes()[j] - 1].getX() << " " << vertexes[faces[i].getIndexesOfVertexes()[j] - 1].getY() << " " << vertexes[faces[i].getIndexesOfVertexes()[j] - 1].getZ() << "]";
		}
		cout << endl;
	}
}
void transformVertex(float matrixModel[N][N], float vertexToTrasnform[N], float vertexToPlot[N])
{
	for (int i = 0; i < N; i++)
	{
		vertexToPlot[i] = 0;
		for (int j = 0; j < N; j++)
		{
			vertexToPlot[i] += matrixModel[i][j] * vertexToTrasnform[j];
		}
	}
}
void drawScene()
{
	int i = 0;
	for (Model3D model : models)
	{	
		vector<Vertex> vertexes = model.getVertexes();
		vector<Face> faces = model.getFaces();
		int j = 0;
		for (Face face: faces)
		{
			vector<Vertex> aux;
			for (int j = 0; j < face.getIndexesOfVertexes().size(); j++)
			{
				Vertex currentVertex = vertexes[face.getIndexesOfVertexes()[j] - 1];

				float vertexToTrasnform[N]{ currentVertex.getX(), currentVertex.getY(), currentVertex.getZ(), 1 };
				float vertexToPlot[N];

				transformVertex(model.matrix, vertexToTrasnform, vertexToPlot);

				currentVertex.setX(vertexToPlot[0]);
				currentVertex.setY(vertexToPlot[1]);
				currentVertex.setZ(vertexToPlot[2]);

				aux.push_back(currentVertex);
			}
			float vector1[] = { aux[1].getX() - aux[0].getX(), aux[1].getY() - aux[0].getY(), aux[1].getZ() - aux[0].getZ()};
			float vector2[] = { aux[2].getX() - aux[0].getX(), aux[2].getY() - aux[0].getY(), aux[2].getZ() - aux[0].getZ()};

			float normal[] = {
			vector1[1] * vector2[2] - vector1[2] * vector2[1],
			vector1[2] * vector2[0] - vector1[0] * vector2[2],
			vector1[0] * vector2[1] - vector1[1] * vector2[0]
			};

			float length = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
			normal[0] /= length;
			normal[1] /= length;
			normal[2] /= length;

			// Calculate the intensity of ambient and diffuse lighting
			float ambientComponent = ambientIntensity;

			// Calculate the diffuse lighting intensity using the light direction
			float diffuseComponent = diffuseIntensity * (
				normal[0] * lightDirection[0] +
				normal[1] * lightDirection[1] +
				normal[2] * lightDirection[2]
				);

			// Clamp diffuseComponent to [0, 1]
			diffuseComponent = max(0.0f, min(1.0f, diffuseComponent));

			// Calculate the final color with lighting
			float finalColor[3];
			for (int c = 0; c < 3; c++) {
				switch (i)
				{
				case 0:
					finalColor[c] = ambientComponent * colorsCohete[j%6][c] + diffuseComponent;
					break;
				case 1:
					finalColor[c] = ambientComponent * colors2[2][c] + diffuseComponent;
					break;
				case 2:
					finalColor[c] = ambientComponent * colors2[1][c] + diffuseComponent;
					break;
				}
			}

			// Drawing the face with the calculated color
			glColor3fv(finalColor);

			// Drawing the face
			glBegin(GL_TRIANGLES);
			for (int j = 0; j < 3; j++)
			{
				glVertex3f(aux[j].getX(), aux[j].getY(), aux[j].getZ());
			}
			glEnd();

			// Draw the line representing the normal of the face
			/*
			glBegin(GL_LINES);
			float centerX = (aux[0].getX() + aux[1].getX() + aux[2].getX()) / 3.0;
			float centerY = (aux[0].getY() + aux[1].getY() + aux[2].getY()) / 3.0;
			float centerZ = (aux[0].getZ() + aux[1].getZ() + aux[2].getZ()) / 3.0;

			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(centerX, centerY, centerZ);
			glVertex3f(centerX + normal[0], centerY + normal[1], centerZ + normal[2]);
			glEnd();//*/

			// Draw light
			/*
			glPushMatrix();
			//glTranslatef(lightDirection[0], lightDirection[1], lightDirection[2]);
			//glColor3f(1.0, 1.0, 0.0);
			glutSolidSphere(0.2, 20, 20);  
			glPopMatrix();
			//*/
			j++;
		}
		i++;
	}
}
void driverKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'v':
			pause = !pause;
		break;
	case 's':
		eye_z = eye_z + value_movement;
		break;
	case 'w':
		eye_z = eye_z - value_movement;
		break;
	case 'a':
		eye_x = eye_x - value_movement;
		break;
	case 'd':
		eye_x = eye_x + value_movement;
		break;
	case 'c':
		eye_y = eye_y + value_movement;
		break;
	case 'n':
		if (center_x >= -5)
		eye_y = eye_y - value_movement;
		break;
	case 'j':
		center_x = center_x - value_movement;
		break;
	case 'l':
		if(center_x <= 5)
			center_x = center_x + value_movement;
		break;
	case 'i':
		if (center_y <= 5)
		center_y = center_y + value_movement;
		break;
	case 'k':
		if (center_y >= -5)
		center_y = center_y - value_movement;
		break;
	default:
		cout << "tecla no reconocida"<<endl;
	}
}
void mouseWheel(int wheel, int direction, int x, int y) {
	if (direction > 0) {
		// Zoom in
		eye_z -= 1.0;
	}
	else {
		// Zoom out
		eye_z += 1.0;
	}

	glutPostRedisplay();
}




