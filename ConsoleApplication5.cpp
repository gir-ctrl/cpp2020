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
	void DrawPoint(Point& MyPoint);
};
//void Point::DrawPoint(Point& MyPoint) {
//	glBegin(GL_POINTS);
//	glColor3d(0, 1, 0);
//	glVertex2d(MyPoint.x, MyPoint.y);
//	glEnd();
//}
class Line {
private:
	Point a;
	Point b;
public:
	Line(Point a1, Point b1) { a = a1, b = b1; };
	void NegA() { a.NegX(); b.NegX(); }
	void NegB() { a.NegY(); b.NegY(); }
	Line& operator += (Line dot) {
		a += dot.a;
		b += dot.b;
		return *this;
	}
	void DrawLine(Line& Myline);
	void DrawTrace(Line& Myline, Line& MyTrace);
	void doing(Line& Myline, Line& MyTrace);
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
void Line::DrawLine(Line& Myline) {
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3d(0, 1, 0);
	glVertex2d(Myline.a.Getx(), Myline.a.GetY());
	glVertex2d(Myline.b.GetX(), Myline.b.GetY());
	glEnd();
}
void Line::DrawTrace(Line& Myline, Line& MyTrace) {
	glLineWidth(3);
	glBegin(GL_POLYGON);
	glColor3d(1, 0, 0);
	glVertex2d(Myline.a.Getx(), Myline.a.Gety());
	glVertex2d(Myline.b.Getx(), Myline.b.Gety());
	glVertex2d(Myline.a.Getx() - 5 * MyTrace.a.Getx(), Myline.a.Gety() - 5 * MyTrace.a.Gety());
	glVertex2d(Myline.b.Getx() - 5 * MyTrace.b.Getx(), Myline.b.Gety() - 5 * MyTrace.b.Gety());
	glEnd();
}
void Line::doing(Line& Myline, Line& MyTrace) {
	if (Myline.a.Getx() <= -3 || Myline.a.Getx() >= 3 || Myline.b.Getx() <= -4 || Myline.b.Getx() >= 3) {
		MyTrace.NegA();
	}
	else if (Myline.a.Gety() <= -3 || Myline.a.Gety() >= 3 || Myline.b.Gety() <= -4 || Myline.b.Gety() >= 3) {
		MyTrace.NegB();
	}
}
Line Myline = Line(Point(0, 0), Point(1, 1));
Line MyTrace = Line(Point(0.01, 0.01), Point(0.01, 0.01));
void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.1f, 0.0f);
	Myline.DrawLine(Myline);
	Myline.DrawTrace(Myline, MyTrace);
	Myline += MyTrace;
	Myline.doing(Myline, MyTrace);
	glutSwapBuffers();
}
void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
}
void processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		MyTrace += Line(Point(-0.01, 0), Point(-0.01, 0));
		break;
	case GLUT_KEY_DOWN:
		MyTrace += Line(Point(0, -0.01), Point(0, -0.01));
		break;
	case GLUT_KEY_RIGHT:
		MyTrace += Line(Point(0.01, 0), Point(0.01, 0));
		break;
	case GLUT_KEY_UP:
		MyTrace += Line(Point(0, 0.01), Point(0, 0.01));
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
