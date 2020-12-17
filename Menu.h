#pragma once
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

class rectangle {
private:
	double x1, y1, x2, y2;
public:
	rectangle(){ x1 = 0; y1 = 0; x2 = 0; y2 = 0; }
	rectangle(double a1, double b1, double a2, double b2){
		x1 = a1; y1 = b1;
		x2 = a2; y2 = b2;
	}
	void rectDraw(float r, float g, float b){
		glBegin(GL_QUADS);
		glColor3f(r, g, b);
		glVertex2f(x1, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y2);
		glVertex2f(x1, y2);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(x1, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y2);
		glVertex2f(x1, y2);
		glVertex2f(x1, y1);
		glEnd();
	};
};
class button {
private:
	rectangle coords;
	string text;
public:
	button(double a1, double b1, double a2, double b2, string text_){
		coords = rectangle(a1, b1, a2, b2);
		text = text_;
	}
	void butDraw(bool act){
		if (act == true)
			coords.rectDraw(0.5, 0.7, 0.4);
		else
			coords.rectDraw(0.5, 0.3, 0.7);
	}
	string get_text(){ return text; };
};
typedef enum { up, down } direction;
class menu {
private:
	rectangle coordinates;
	vector<button> key;
	int active;
public:
	menu(double a1, double b1, double a2, double b2){
		coordinates = rectangle(a1, b1, a2, b2);
		active = 0;
	};
	void addition(double a1, double b1, double a2, double b2, string text_){
		key.push_back(button(a1, b1, a2, b2, text_));
	}
	void menuDraw(){
		coordinates.rectDraw(0.4, 0.9, 0.8);
		int i = 0;
		for (auto& cur_b : key){
			if (i == active)
				cur_b.butDraw(true);
			else
				cur_b.butDraw(false);
			i++;
		}
	};
	string menuAction(){ return key[active].get_text(); };
	void move(direction dir){
		if ((dir == down) && (active < key.size() - 1))
			active++;
		if ((dir == up) && (active > 0))
			active--;
	}
};
vector<menu> MenuRead(string name_file);
void InitMenu(string name_file);
vector<menu>* ActiveMenu();
menu* CurrentMenu();
void OpenMenu(int a);
void CloseMenu();
void DrawMenu(void);
