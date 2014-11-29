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
	return 0;
}

void setDefaults()
{
	// scene Information
	transX = -1.0f;
	transY = -1.0f;
	transZ = -4.0f;
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
	glClearColor(0, 0, 0, 0);
	// enable depth buffer
	glEnable(GL_DEPTH_TEST);
	// Use Point Smoothing
	glEnable(GL_POINT_SMOOTH);
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

	// hint: if DRAW_EXAMPLES is not defined, p1, p2 and p3 are initialized in the setDefaults method
#ifdef DRAW_EXAMPLES

	// Example: draw a line


	// to draw lines: specify color with glColor3f and two vertices with glVertex3f
	p2.homogenize(); // always homogenize before drawing unless you know for sure that the w component is 1 already
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glEnd();

	// Example: draw a point
	p3.x = 0.5f;
	p3.y = 0.5f;
	p3.z = 0.5f;
	p3.w = 1.0f;

	// to draw a point: specify a color with glColor3f and one vertex with glVertex3f
	glBegin(GL_POINTS);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(p3.x, p3.y, p3.z);
	glEnd();

#endif

	// TODO: generate, transform and draw objects, like detailed in exercise description
	// To generate a transformation matrix use for example: "Matrix4f trans = Matrix4f::translationMatrix(1,2,3);"
	// To concatenate two matrices use *: "Matrix4f resultMatrix = leftMatrix * rightMatrix;"
	// To transform a point use *: "Vec4f resultPoint = matrix * point;"
	// =================================================================================

	// =================================================================================
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
	// translate scene in viewing direction
	glTranslatef(transX, transY, transZ);
	// rotate scene
	glRotatef(angleX, 0.0f, 1.0f, 0.0f);
	glRotatef(angleY, 1.0f, 0.0f, 0.0f);
	// draw coordinate system without lighting
	glDisable(GL_LIGHTING);
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
		// ==========================================================================
	}
}

void mousePressed(int button, int state, int x, int y)
{
	mouseButton = button;
	mouseX = x;
	mouseY = y;
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
}