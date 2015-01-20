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

#include <GL/glut.h>	// openGL helper

#include "Vec4.h"		// homogene vector (4 elements)
#include "Matrix4.h"	// homogene matrix (4x4 elements)
#include "Curve.h"

// ===================
// === GLOBAL DATA ===
// ===================

// TODO: define global variables here to present the exercises
// ===========================================================

// use this define, to draw an example line and point
#define DRAW_EXAMPLES

const int POINT_MOVE_UPDATE_RATE = 5;

// some points used for drawing point & line example
Vec4f p1, p2, p3;

Curve *curve;

// ===========================================================

// do not modify data below unless you know what you do
// camera Information
float transX, transY, transZ;
float angleX, angleY;
// mouse information
int mouseX, mouseY, mouseButton;
float mouseSensitivy;

bool curveMode;
bool bPointSelectionMode;
int selectedPointIndex;
int pointMoveTick;

// ==============
// === BASICS ===
// ==============

int main(int argc, char **argv);

void setDefaults();

void initializeGL();

void reshape(GLint width, GLint height);

// =================
// === RENDERING ===
// =================

void drawCS();

void drawObjects();

void renderScene(void);

// =================
// === CALLBACKS ===
// =================

void keyPressed(unsigned char key, int x, int y);

void mousePressed(int button, int state, int x, int y);

void mouseMoved(int x, int y);

// ===============
// === VARIOUS ===
// ===============

Vec3d worldCoord(int x, int y);

void coutHelp();
