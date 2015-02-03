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
#include <cmath>		// fmod
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
	calculatePoints();
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

	nrPoints = 10;
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
	// set lighting (white light)
	GLfloat global_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat ambientLight[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat shininess = 0.9f * 128.0f;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightf(GL_LIGHT0, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);
	GLfloat lp[] = { 10.0f, 20.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lp);
	// enable lighting by glColor
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	// key bindings => cout
	coutHelp();
}

void calculatePoints()
{
	// objects (test surface via empty constructor)
	nurbs = NURBS_Surface();
	std::cout << nurbs << std::endl;
	
	points.clear();
	points.reserve(nrPoints * nrPoints);
	normals.clear();
	normals.reserve(nrPoints * nrPoints);
	float div = (float)(nrPoints - 1);
	for (unsigned int i = 0; i < nrPoints; ++i)
	{
		float u = (float)i / div;
		for (unsigned int j = 0; j < nrPoints; ++j)
		{
			float v = (float)j / div;
			Vec4f tangentU, tangentV;
			points.push_back(nurbs.evaluteDeBoor(u, v, tangentU, tangentV));
			tangentU.homogenize();
			tangentV.homogenize();
			Vec3f tU = Vec3f(tangentU.x, tangentU.y, tangentU.z);
			Vec3f tV = Vec3f(tangentV.x, tangentV.y, tangentV.z);
			normals.push_back((tU ^ tV).normalized());
		}
	}
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
	glDisable(GL_LIGHTING);
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
	// TODO: draw nurbs surface
	// ========================
	if (points.size() > 3 && nurbs.controlPoints.size() > 1)
	{
		// draw points of the surface (homogenized)
		glColor3f(0.0f, 1.0f, 1.0f);
		glBegin(GL_POINTS);
		for (unsigned int i = 0; i < points.size(); ++i)
		{
			Vec4f p = points[i];
			p.homogenize();
			glVertex3f(p.x, p.y, p.z);
		}
		glEnd();

		// draw normals as lines
		glColor3f(0.0f, 0.7f, 0.7f);
		glBegin(GL_LINES);
		for (unsigned int i = 0; i < normals.size(); ++i)
		{
			Vec4f p = points[i];
			p.homogenize();
			glVertex3f(p.x, p.y, p.z);
			glVertex3f(p.x + normals[i].x, p.y + normals[i].y, p.z + normals[i].z);
		}
		glEnd();

		// draw control polygon (homogenized)
		glDisable(GL_LIGHTING);
		glColor3f(1.0f, 0.0f, 1.0f);
		glBegin(GL_POINTS);
		for (unsigned int i = 0; i < nurbs.controlPoints.size(); ++i)
		{
			for (unsigned int j = 0; j < nurbs.controlPoints[i].size(); ++j)
			{
				Vec4f p = nurbs.controlPoints[i][j];
				p.homogenize();
				glVertex3f(p.x, p.y, p.z);
			}
		}
		glEnd();
		glColor3f(0.7f, 0.0f, 0.7f);
		glBegin(GL_LINES);
		for (unsigned int i = 0; i < nurbs.controlPoints.size(); ++i)
		{
			for (unsigned int j = 0; j < nurbs.controlPoints[i].size(); ++j)
			{
				Vec4f p = nurbs.controlPoints[i][j];
				p.homogenize();
				if (i > 0)
				{
					Vec4f pV = nurbs.controlPoints[i - 1][j];
					pV.homogenize();
					glVertex3f(p.x, p.y, p.z);
					glVertex3f(pV.x, pV.y, pV.z);
				}
				if (j > 0)
				{
					Vec4f pU = nurbs.controlPoints[i][j - 1];
					pU.homogenize();
					glVertex3f(p.x, p.y, p.z);
					glVertex3f(pU.x, pU.y, pU.z);
				}
			}
		}
		glEnd();
		// draw surface with quads
		glEnable(GL_LIGHTING);
		glColor3f(0.99f, 0.99f, 0.99f);
		glBegin(GL_QUADS);
		for (unsigned int i = 1; i < nrPoints; ++i)
		{
			for (unsigned int j = 1; j < nrPoints; ++j)
			{
				unsigned int index;
				Vec4f& p = points.front();
				index = j*nrPoints + i;
				p = points[index];
				glNormal3f(normals[index].x, normals[index].y, normals[index].z);
				glVertex3f(p.x / p.w, p.y / p.w, p.z / p.w);
				index = (j - 1)*nrPoints + i;
				p = points[index];
				glNormal3f(normals[index].x, normals[index].y, normals[index].z);
				glVertex3f(p.x / p.w, p.y / p.w, p.z / p.w);
				index = (j - 1)*nrPoints + i - 1;
				p = points[index];
				glNormal3f(normals[index].x, normals[index].y, normals[index].z);
				glVertex3f(p.x / p.w, p.y / p.w, p.z / p.w);
				index = j*nrPoints + i - 1;
				p = points[index];
				glNormal3f(normals[index].x, normals[index].y, normals[index].z);
				glVertex3f(p.x / p.w, p.y / p.w, p.z / p.w);
			}
		}
		glEnd();
	}
	// ========================
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
	case 'm':
		nrPoints++;
		calculatePoints();
		glutPostRedisplay();
		break;
	case 'M':
		if (nrPoints > 0)
		{
			nrPoints--;
			calculatePoints();
			glutPostRedisplay();
		}
		break;
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
	std::cout << "==========================" << std::endl;
	std::cout << std::endl;
}