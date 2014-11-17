// ========================================================================= //
// Authors: Matthias Bein                                                    //
// mailto:matthias.bein@igd.fraunhofer.de                                    //
//                                                                           //
// GRIS - Graphisch Interaktive Systeme                                      //
// Technische Universit�t Darmstadt                                          //
// Fraunhoferstrasse 5                                                       //
// D-64283 Darmstadt, Germany                                                //
//                                                                           //
// Creation Date: 29.10.2013                                                 //
// Content: Simple and extendable openGL program offering                    //
//   * basic navigation and basic pipeline rendering                         //
// ========================================================================= //

#include <GL/glut.h>	// openGL helper
#include <vector>

#include "Vec4.h"		// homogene vector (4 elements)
#include "Matrix4.h"	// homogene matrix (4x4 elements)
#include "Point.h"

// ===================
// === GLOBAL DATA ===
// ===================

// TODO: define global variables here to present the exercises
// ===========================================================

// use this define, to draw an example line and point
#define DRAW_EXAMPLES

// some points used for drawing point & line example
Vec4f p1, p2, p3;

Point point;

std::vector<IDrawable*> drawableObjects;

// ===========================================================

// do not modify data below unless you know what you do
// camera Information
float transX, transY, transZ;
float angleX, angleY;
// mouse information
int mouseX, mouseY, mouseButton;
float mouseSensitivy;

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

void coutHelp();
