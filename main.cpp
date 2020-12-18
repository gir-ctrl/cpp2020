#include "Menu.h"

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
	menu *current_menu = CurrentMenu();
	switch (key) {
	case GLUT_KEY_DOWN:
		current_menu->move(down);
		break;
	case GLUT_KEY_UP:
		current_menu->move(up);
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
		string action = current_menu->menuAction();
		if (CheckIfInteger(action)){
			OpenMenu(stoi(action));
			return;
		}
		else{
			if (action.compare("close") == 0){
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
	glClearColor(1.0f, 1.f, 0.6f, 0.6f);

	glutKeyboardFunc(ProcessNormalKeys);
	glutSpecialFunc(ProcessSpecialKeys);

	glutDisplayFunc(RenderWindow);
	glutIdleFunc(RenderWindow);

	glutMainLoop();
}
