#include "ofMain.h"
#include "ofApp.h"

inline void floorMesh(GLint nRows, GLint nColumns) {
	GLfloat xStart = - nColumns / 2.0;
	GLfloat yStart = - nRows / 2.0;

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	for (int i = 0; i < nColumns; i++) {
		for (int j = 0; j < nRows; j++) {
			glVertex2d(i + xStart, j + yStart);
			glVertex2d(i + xStart, (j + 1) + yStart);
			glVertex2d((i + 1) + xStart, (j + 1) + yStart);
			glVertex2d((i + 1) + xStart, j + yStart);
		}
	}
	glEnd();
}

inline void buildingMesh(GLfloat width, GLfloat height) {
	GLint xDiv = 4;
	GLint yDiv = 4;
	GLfloat xStart = -width / 2;
	GLfloat yStart = -height / 2;
	GLfloat xStep = width / xDiv;
	GLfloat yStep = height / yDiv;

	glBegin(GL_QUADS);
	for (int i = 0; i < yDiv; i++) {
		for (int j = 0; j < xDiv; j++) {
			glVertex2d(i * xStep + xStart, j * yStep + yStart);
			glVertex2d(i * xStep + xStart, (j + 1) * yStep + yStart);
			glVertex2d((i + 1) * xStep + xStart, (j + 1) * yStep + yStart);
			glVertex2d((i + 1) * xStep + xStart, j * yStep + yStart);
		}
	}
	glEnd();
}

inline void rectangleUnit() {
	glPushMatrix();

	//top
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glTranslatef(0, 0, 1);
	buildingMesh(1, 1);
	glPopMatrix();

	//front
	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslatef(0, 0.5, 0.5);
	glRotated(90, 1, 0, 0);
	buildingMesh(1, 1);
	glPopMatrix();

	//back
	glPushMatrix();
	glTranslatef(0, -0.5, 0.5);
	glRotated(90, 1, 0, 0);
	buildingMesh(1, 1);
	glPopMatrix();

	//left
	glPushMatrix();
	glColor3f(0.6, 0.6, 0.6);
	glTranslatef(-0.5, 0, 0.5);
	glRotated(90, 0, 1, 0);
	buildingMesh(1, 1);
	glPopMatrix();

	//right
	glPushMatrix();
	glTranslatef(0.5, 0, 0.5);
	glRotated(90, 0, 1, 0);
	buildingMesh(1, 1);
	glPopMatrix();

	glPopMatrix();
}

inline void cylinderUnit(GLfloat radius, GLfloat height, GLint segments) {
	glPushMatrix();
	glRotated(90, 1, 0, 0);

	//sides
	glBegin(GL_QUAD_STRIP);

	glColor3f(0.8, 0.8, 0.8);
	for (int i = 0; i <= segments; i++) {
		float theta = (2.0 * PI * i) / segments;
		float x = radius * cos(theta);
		float z = radius * sin(theta);

		glVertex3f(x, height / 2, z);
		glVertex3f(x, -height / 2, z);
	}
	glEnd();

	//top
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(0, height / 2, 0);
	for (int i = 0; i <= segments; i++) {
		float theta = (2.0 * PI * i) / segments;
		float x = radius * cos(theta);
		float z = radius * sin(theta);
		glVertex3f(x, height / 2, z);
	}
	glEnd();

	//bottom
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, -height / 2, 0);
	for (int i = 0; i <= segments; i++) {
		float theta = (2.0 * PI * i) / segments;
		float x = radius * cos(theta);
		float z = radius * sin(theta);
		glVertex3f(x, -height / 2, z);
	}
	glEnd();

	glPopMatrix();
}

inline void building1(GLint nFloors, GLfloat x, GLfloat y, GLfloat width, GLfloat length, GLfloat height) {
	GLfloat h = 0;
	for (int i = 0; i < nFloors; i++) {
		glPushMatrix();
		glTranslatef(x, y, h);
		glScalef(width / (1 + i), length / (1 + i), height / 3);
		rectangleUnit();
		glPopMatrix();

		h += height / 3;
	}
}

inline void building2(GLint nFloors, GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
	glPushMatrix();
	glTranslatef(x, y, height / 2);
	cylinderUnit(width / 2, height, 20);
	glPopMatrix();
}

inline void specialBuilding(GLfloat x, GLfloat y, GLfloat heightB2, GLfloat rotationB2) {
	glPushMatrix();
	glTranslatef(x, y, 0);

	glPushMatrix();
	glTranslatef(0, 0, 5 / 2.0);
	cylinderUnit(0.1, 5, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.3 / 2.0 + heightB2);
	glRotated(rotationB2, 0, 0, 1);
	cylinderUnit(0.3, 0.3, 6);
	glPopMatrix();

	glPopMatrix();

}