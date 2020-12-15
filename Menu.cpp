#include "Menu.h"

static vector<menu> menu_cur;
static vector<menu> menu_act;
vector<menu> MenuRead(string name_file) {
	ifstream if_file(name_file);
	string line;
	vector<string> lines;
	vector<string> line_cut;
	vector<menu> menu_;
	int i = -1;
	if (if_file.is_open()) {
		while (getline(if_file, line))
			lines.push_back(line);
	}
	if_file.close();
	for (auto& line_ : lines) {
		istringstream iss(line_);
		menu present;
		while (getline(iss, line, ' '))
			line_cut.push_back(line);
		string type_{ *line_cut.begin() };
		if (type_.compare("menu:") == 0) {
			present.coordinates.x1 = stof(line_cut[1]);
			present.coordinates.y1 = stof(line_cut[2]);
			present.coordinates.x2 = stof(line_cut[3]);
			present.coordinates.y2 = stof(line_cut[4]);
			menu_.push_back(present);
			i++;
		}
		if (type_.compare("button:") == 0) {
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
void InitMenu(string name_file) {
	menu_cur = MenuRead(name_file);
}
vector<menu>* ActiveMenu() {
	return &menu_act;
}
menu* CurrentMenu() {
	return &(menu_act[menu_act.size() - 1]);
}
void OpenMenu(int a) {
	menu_act.push_back(menu_cur[a]);
}
void CloseMenu() {
	menu_act.pop_back();
}
vector<menu> MenuRead(string name_file) {
	ifstream if_file(name_file);
	string line;
	vector<string> lines;
	vector<string> line_cut;
	vector<menu> menu_;
	int i = -1;
	if (if_file.is_open()) {
		while (getline(if_file, line))
			lines.push_back(line);
	}
	if_file.close();
	for (auto& line_ : lines) {
		istringstream iss(line_);
		menu present;
		while (getline(iss, line, ' '))
			line_cut.push_back(line);
		string type_{ *line_cut.begin() };
		if (type_.compare("menu:") == 0) {
			present.coordinates.x1 = stof(line_cut[1]);
			present.coordinates.y1 = stof(line_cut[2]);
			present.coordinates.x2 = stof(line_cut[3]);
			present.coordinates.y2 = stof(line_cut[4]);
			menu_.push_back(present);
			i++;
		}
		if (type_.compare("button:") == 0) {
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
void DrawMenu(void) {
	vector<menu> menu_ = *ActiveMenu();
	for (auto& present : menu_) {
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
		for (auto& present_b : present.key) {
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