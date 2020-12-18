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
		while (getline(iss, line, ' '))
			line_cut.push_back(line);
		string type_{ *line_cut.begin() };
		if (type_.compare("menu:") == 0) {
			menu_.push_back(menu(stof(line_cut[1]), stof(line_cut[2]), stof(line_cut[3]), stof(line_cut[4])));
			i++;
		}
		if (type_.compare("button:") == 0) 
			menu_[i].addition(stof(line_cut[1]), stof(line_cut[2]), stof(line_cut[3]), stof(line_cut[4]), line_cut[5]);
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
void DrawMenu(void) {
	vector<menu> menu_ = *ActiveMenu();
	for (auto& present : menu_)
		present.menuDraw();
}
