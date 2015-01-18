// ========================================================================= //
// Authors: Matthias Bein                                                    //
// mailto:matthias.bein@igd.fraunhofer.de                                    //
//                                                                           //
// GRIS - Graphisch Interaktive Systeme                                      //
// Technische Universität Darmstadt                                          //
// Fraunhoferstrasse 5                                                       //
// D-64283 Darmstadt, Germany                                                //
//                                                                           //
// Creation Date: 29.10.2013                                                 //
// Content: Simple and extendable openGL program offering                    //
//   * basic navigation and basic pipeline rendering                         //
// ========================================================================= //

#include "main.h"		// this header
#include "CurveGenerator.h"

#include <stdlib.h>		// standard library
#include <math.h>		// fmod
#include <stdio.h>		// cout
#include <iostream>		// cout

// ==============
// === BASICS ===
// ==============

int main(int argc, char** argv)
{
	// initialize openGL window
	glutInit(&argc, argv);
	glutInitWindowPosition(300, 200);
	glutInitWindowSize(600, 400);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("TU Darmstadt, MBein");
	// link functions to certain openGL events
	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshape);
	glutMouseFunc(mousePressed);
	glutMotionFunc(mouseMoved);
	glutKeyboardFunc(keyPressed);
	// further initializations
	setDefaults();
	initializeGL();
	// activate main loop
	glutMainLoop();

	if (curve != NULL)
	{
		delete curve;
		curve = NULL;
	}

	return 0;
}

void setDefaults()
{
	curveMode = false;
	curve = NULL;

	// scene Information
	transX = 0.0f;
	transY = 0.0f;
	transZ = 0.0f;
	angleX = 0.0f;
	angleY = 0.0f;
	// mouse information
	mouseX = 0;
	mouseY = 0;
	mouseButton = 0;
	mouseSensitivy = 1.0f;
	// objects
	p1.set(0.3f, 0.0f, 0.2f, 1.0f);
	p2.set(1.4f, 0.0f, 1.4f, 2.0f);
	p3.set(0.0f, 0.0f, 1.0f, 1.0f);
}

void initializeGL()
{
	// black screen
	glClearColor(1.0, 1.0, 1.0, 1.0);
	// enable depth buffer
	glEnable(GL_DEPTH_TEST);
	// Use Point Smoothing
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glPointSize(4.0f);
	glLineWidth(4.0f);
	// set shading model
	glShadeModel(GL_SMOOTH);
	// key bindings => cout
	coutHelp();
}

void reshape(GLint width, GLint height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (float)width / (float)height, 0.1f, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// =================
// === RENDERING ===
// =================

void drawCS()
{
	glBegin(GL_LINES);
	// red X
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	// green Y
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	// blue Z
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();
}

void drawObjects()
{
	//glBegin(GL_POINTS);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(0.0f, 0.0f, 0.0f);
	//glVertex3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(2.0f, 0.0f, 0.0f);
	//glVertex3f(3.0f, 0.0f, 0.0f);
	//glEnd();

	if (curve != NULL)
	{
		curve->draw();
	}
}

void rotate10AroundZ(Vec4f& v) {
	Matrix4f rot = Quaternion::rotationQuaternion(10, Vec3f(0.f, 0.f, 1.f)).getRotationMatrix();

	Quaternion q = Quaternion::rotationQuaternion(10, Vec3f(0.f, 0.f, 1.f));
	Quaternion p = Quaternion(0, v.x, v.y, v.z);
	p = (q * p) * q.conjugated();

	v.x = p.u.x;
	v.y = p.u.y;
	v.z = p.u.z;
}

void rotate10AroundY(Vec4f& v) {
	v = Matrix4f::rotateY(10) * v;
}

void translateX(Vec4f& v) {
	v = Matrix4f::translationMatrix(0.5f, 0.0f, 0.0f) * v;
}

void translateY(Vec4f& v) {
	v = Matrix4f::translationMatrix(0.0f, 0.5f, 0.0f) * v;
}

void concattedTransformation(Vec4f& v) {
	v = Matrix4f::translationMatrix(0.2f, 0.5f, 0.0f) * Matrix4f::rotateZ(-15) * Matrix4f::translationMatrix(-0.2f, 0.0f, 0.0f) * v;
}

void renderScene()
{
	// clear and set camera
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	// camera
	gluLookAt(0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glDisable(GL_LIGHTING);

	glBegin(GL_QUADS);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex3f(-100.0f, 100.0f, -.0001f);
	glVertex3f(-100.0f, -100.0f, -.0001f);
	glVertex3f(100.0f, -100.0f, -.0001f);
	glVertex3f(100.0f, 100.0f, -.0001f);
	glEnd();

	// draw coordinate system without lighting
	drawCS();
	drawObjects();
	// swap Buffers
	glFlush();
	glutSwapBuffers();
}

// =================
// === CALLBACKS ===
// =================

void keyPressed(unsigned char key, int x, int y)
{
	switch (key)
	{
		// esc => exit
	case 27:
		exit(0);
		break;
		// help file
	case 'h':
	case 'H':
		coutHelp();
		break;
		// reset view
	case 'r':
	case 'R':
		setDefaults();
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
		// TODO: place custom functions on button events here to present your results
		// ==========================================================================
	case 'x':
	case 'X':
		translateX(p1);
		translateX(p2);
		glutPostRedisplay();
		break;
	case 'y':
	case 'Y':
		rotate10AroundY(p1);
		rotate10AroundY(p2);
		glutPostRedisplay();
		break;
	case 'z':
	case 'Z':
		rotate10AroundZ(p1);
		rotate10AroundZ(p2);
		glutPostRedisplay();
		break;
	case 't':
	case 'T':
		translateY(p1);
		translateY(p2);
		glutPostRedisplay();
		break;
	case 'c':
	case 'C':
		concattedTransformation(p1);
		concattedTransformation(p2);
		glutPostRedisplay();
		break;
	case 'p':
	case 'P':
		if (!curveMode && curve != NULL)
		{
			curve = NULL;
		}
		curveMode = !curveMode;
		std::cout << "curve mode : " << curveMode << std::endl;
		break;
		// ==========================================================================
	}
}

void mousePressed(int button, int state, int x, int y)
{
	mouseButton = button;
	mouseX = x;
	mouseY = y;

	if (curveMode && state == GLUT_DOWN)
	{
		if (curve == NULL)
		{
			curve = new Curve();
		}


		Vec3d point = worldCoord(x, y);
		point.z = 0.0f;
		curve->addPoint(point);

		std::cout << "create new curve point at x=" << x << " y=" << y << " (" << point.x << ", " << point.y << ", " << point.z << ")" << std::endl;
	}
}

void mouseMoved(int x, int y)
{
	// rotate (cap angleY within [-85°, +85°])
	if (mouseButton == GLUT_LEFT_BUTTON)
	{
		angleX = fmod(angleX + (x - mouseX) * mouseSensitivy, 360.0f);
		angleY += (y - mouseY) * mouseSensitivy;
		if (angleY > 85) angleY = 85;
		if (angleY < -85) angleY = -85;
		glutPostRedisplay();
	}
	// zoom (here translation in z)
	if (mouseButton == GLUT_RIGHT_BUTTON)
	{
		transZ -= 0.2f * (y - mouseY) * mouseSensitivy;
		glutPostRedisplay();
	}
	// translation in xy
	if (mouseButton == GLUT_MIDDLE_BUTTON)
	{
		transX += 0.2f * (x - mouseX) * mouseSensitivy;
		transY -= 0.2f * (y - mouseY) * mouseSensitivy;
		glutPostRedisplay();
	}
	// update mouse for next relative movement
	mouseX = x;
	mouseY = y;
}

// ===============
// === VARIOUS ===
// ===============

// project screen coordinates into world coordinates
Vec3d worldCoord(int x, int y){
	GLint viewport[4];
	GLdouble M[16], P[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, M);
	glGetDoublev(GL_PROJECTION_MATRIX, P);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	//winZ = 0.0f;

	gluUnProject(winX, winY, winZ, M, P, viewport, &posX, &posY, &posZ);

	return Vec3d(posX, posY, posZ);
}

void coutHelp()
{
	std::cout << std::endl;
	std::cout << "====== KEY BINDINGS ======" << std::endl;
	std::cout << "ESC: exit" << std::endl;
	std::cout << "H: show this (H)elp file" << std::endl;
	std::cout << "R: (R)eset view" << std::endl;
	// TODO: update help text according to your changes
	// ================================================
	std::cout << "X: Translate line on x axis" << std::endl;
	std::cout << "Y: Rotate line around y axis" << std::endl;
	std::cout << "Z: Rotate line around z axis" << std::endl;
	std::cout << "T: Translate line on y axis" << std::endl;
	std::cout << "C: Transform line by concatted transformations" << std::endl;
	// ================================================
	std::cout << "========== INFO ==========" << std::endl;
	std::cout << "* To test incommutativity of transformations, run 'X' and 'Z' in different orders." << std::endl;
	std::cout << "* To test special case of commutativity of transformations, run 'Y' and 'T' in different orders." << std::endl;
	std::cout << std::endl;

	Vec3f P[4] = { Vec3f(0, 0, 0), Vec3f(0, 1, 0), Vec3f(1, 1, 0), Vec3f(1, 0, 0) };

	/*CurveGenerator::render(3, P, 4);*/
}