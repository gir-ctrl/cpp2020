#include "pch.h"
#include <windows.h>
#include "glut.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

struct rectangle {
	double x1, y1, x2, y2;
};
struct button {
	rectangle coords;
	string text;
};
struct menu {
	rectangle coordinates;
	vector<button> key;
	int active;
};
static vector<menu> menu_cur;
static vector<menu> menu_act;
vector<menu>* ActiveMenu(){
	return &menu_act;
}
menu* CurrentMenu(){
	return &(menu_act[menu_act.size() - 1]);
}
void OpenMenu(int a){
	menu_act.push_back(menu_cur[a]);
}
void CloseMenu(){
	menu_act.pop_back();
}
vector<menu> MenuRead(string name_file){
	ifstream if_file(name_file);
	string line;
	vector<string> lines;
	vector<string> line_cut;
	vector<menu> menu_;
	int i = -1;
	if (if_file.is_open()){
		while (getline(if_file, line))
			lines.push_back(line);
	}
	if_file.close();
	for (auto& line_ : lines){
		istringstream iss(line_);
		menu present;
		while (getline(iss, line, ' '))
			line_cut.push_back(line);
		string type_{ *line_cut.begin()};
		if (type_.compare("menu:") == 0){
			present.coordinates.x1 = stof(line_cut[1]);
			present.coordinates.y1 = stof(line_cut[2]);
			present.coordinates.x2 = stof(line_cut[3]);
			present.coordinates.y2 = stof(line_cut[4]);
			menu_.push_back(present);
			i++;
		}
		if (type_.compare("button:") == 0){
			button cur_b;
			cur_b.coords.x1 = stof(line_cut[1]);
			cur_b.coords.y1 = stof(line_cut[2]);
			cur_b.coords.x2 = stof(line_cut[3]);
			cur_b.coords.y2 = stof(line_cut[4]);
			cur_b.text = line_cut[5];
			menu_[i].key.push_back(cur_b);
		}
		present.active = 0;
		line_cut.clear();
	}
	return menu_;
}
void InitMenu(string name_file){
	menu_cur = MenuRead(name_file);
}
void DrawMenu(void){
	vector<menu> menu_ = *ActiveMenu();
	for (auto& present : menu_){
		glBegin(GL_QUADS);
		glColor3f(0.9f, 0.9f, 0.9f);
		glVertex2f(present.coordinates.x1, present.coordinates.y1);
		glVertex2f(present.coordinates.x2, present.coordinates.y1);
		glVertex2f(present.coordinates.x2, present.coordinates.y2);
		glVertex2f(present.coordinates.x1, present.coordinates.y2);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(present.coordinates.x1, present.coordinates.y1);
		glVertex2f(present.coordinates.x2, present.coordinates.y1);
		glVertex2f(present.coordinates.x2, present.coordinates.y2);
		glVertex2f(present.coordinates.x1, present.coordinates.y2);
		glVertex2f(present.coordinates.x1, present.coordinates.y1);
		glEnd();
		int i = 0;
		for (auto& present_b : present.key){
			glBegin(GL_QUADS);
			if (i == present.active)
				glColor3f(0.4f, 0.4f, 0.4f);
			else
				glColor3f(0.66f, 0.66f, 0.66f);
			glVertex2f(present_b.coords.x1, present_b.coords.y1);
			glVertex2f(present_b.coords.x2, present_b.coords.y1);
			glVertex2f(present_b.coords.x2, present_b.coords.y2);
			glVertex2f(present_b.coords.x1, present_b.coords.y2);
			glEnd();
			glBegin(GL_LINE_STRIP);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex2f(present_b.coords.x1, present_b.coords.y1);
			glVertex2f(present_b.coords.x2, present_b.coords.y1);
			glVertex2f(present_b.coords.x2, present_b.coords.y2);
			glVertex2f(present_b.coords.x1, present_b.coords.y2);
			glVertex2f(present_b.coords.x1, present_b.coords.y1);
			glEnd();
			i++;
		}
	}
}
void RenderWindow(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawMenu();
	glutSwapBuffers();
}
bool CheckIfInteger(const string& str)
{
	if (str.empty() || ((!isdigit(str[0])) && (str[0] != '-') && (str[0] != '+'))) return false;
	char* p;
	strtol(str.c_str(), &p, 10);
	return (*p == 0);
}
void ProcessSpecialKeys(int key, int x, int y) {
	menu* current_menu = CurrentMenu();
	switch (key) {
	case GLUT_KEY_DOWN:
		if (current_menu->active < current_menu->key.size() - 1)
			current_menu->active++;
		break;
	case GLUT_KEY_UP:
		if (current_menu->active > 0)
			current_menu->active--;
		break;
	}
}
void ProcessNormalKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
	break;
	case 13:{
		menu* current_menu = CurrentMenu();
		button cur = current_menu->key[current_menu->active];
		if (CheckIfInteger(cur.text)){
			OpenMenu(stoi(cur.text));
			return;
		}
		else{
			if (cur.text.compare("close") == 0){
				CloseMenu();
				return;
			}
		}
	}
	break;
	}
}
void main(int argc, char** argv)
{
	vector<menu> menu_;
	InitMenu("menu.txt");
	OpenMenu(0);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("lab_3");
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);

	glutKeyboardFunc(ProcessNormalKeys);
	glutSpecialFunc(ProcessSpecialKeys);

	glutDisplayFunc(RenderWindow);
	glutIdleFunc(RenderWindow);

	glutMainLoop();
}
