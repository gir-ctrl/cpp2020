#include <stdlib.h>
#include <math.h>
#include "glut.h"
#include <list>

using namespace std;

class Point {
private:
	float x;
	float y;
public:
	Point() { x = 0, y = 0; };
	Point(float x1, float y1) { x = x1, y = y1; };
	float Getx(void) { return x; };
	float Gety(void) { return y; };
	void NegX() { x = -x; };
	void NegY() { y = -y; };
	Point& operator += (Point dot) {
		x += dot.x;
		y += dot.y;
		return *this;
	}
	const Point operator - (Point dot) { return(Point(x - dot.x, y - dot.y)); }
	const Point operator - () { return(Point(-x, -y)); }
	const Point operator + (Point dot) { return(Point(x + dot.x, y + dot.y)); }
};
class Line {
private:
	Point a;
	Point b;
public:
	Line(Point a1, Point b1) { a = a1, b = b1; };
	Point GetA() { return a; };
	Point GetB() { return b; };
	void NegA() { a.NegX(); b.NegX(); }
	void NegB() { a.NegY(); b.NegY(); }
	Line& operator += (Line dot) {
		a += dot.a;
		b += dot.b;
		return *this;
	}
	Line& operator = (Line dot) {
		a = dot.a;
		b = dot.b;
		return *this;
	}
	const Line operator - (Line dot) { return(Line(a - dot.a, b - dot.b)); }
	const Line operator - () { return(Line(-a, -b)); }
	const Line operator + (Line dot) { return(Line(a + dot.a, b + dot.b)); }
};
void changeSize(int w, int h) {
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}
void DrawLine(Line& Myline) {
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3d(0, 1, 0);
	glVertex2d(Myline.GetA().Getx(), Myline.GetA().Gety());
	glVertex2d(Myline.GetB().Getx(), Myline.GetB().Gety());
	glEnd();
}
void DrawTrace(Line& Myline, Line& speed) {
	glLineWidth(3);
	glBegin(GL_POLYGON);
	glColor3d(1, 0, 0);
	glVertex2d(Myline.GetA().Getx(), Myline.GetA().Gety());
	glVertex2d(Myline.GetB().Getx(), Myline.GetB().Gety());
	glVertex2d(Myline.GetA().Getx() - 5 * speed.GetA().Getx(), Myline.GetA().Gety() - 5 * speed.GetA().Gety());
	glVertex2d(Myline.GetB().Getx() - 5 * speed.GetB().Getx(), Myline.GetB().Gety() - 5 * speed.GetB().Gety());
	glEnd();
}
Line Myline = Line(Point(0, 0), Point(1, 1));
Line speed = Line(Point(0.01, 0.01), Point(0.01, 0.01));
void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.1f, 0.0f);
	DrawLine(Myline);
	DrawTrace(Myline, speed);
	Myline += speed;
	if (Myline.GetA().Getx() <= -3 || Myline.GetA().Getx() >= 3 || Myline.GetB().Getx() <= -4 || Myline.GetB().Getx() >= 3) {
		speed.NegA();
	}
	else if (Myline.GetA().Gety() <= -3 || Myline.GetA().Gety() >= 3 || Myline.GetB().Gety() <= -4 || Myline.GetB().Gety() >= 3) {
		speed.NegB();
	}
	glutSwapBuffers();
}
void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
}
void processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		speed += Line(Point(-0.01, 0), Point(-0.01, 0));
		break;
	case GLUT_KEY_DOWN:
		speed += Line(Point(0, -0.01), Point(0, -0.01));
		break;
	case GLUT_KEY_RIGHT:
		speed += Line(Point(0.01, 0), Point(0.01, 0));
		break;
	case GLUT_KEY_UP:
		speed += Line(Point(0, 0.01), Point(0, 0.01));
		break;
	}
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 500);
	glutCreateWindow("Lab_2");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	glutMainLoop();

	return 1;
}