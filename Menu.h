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
vector<menu> MenuRead(string name_file);
void InitMenu(string name_file);
vector<menu>* ActiveMenu();
menu* CurrentMenu();
void OpenMenu(int a);
void CloseMenu();
void DrawMenu(void);
vector<menu> MenuRead(string name_file);