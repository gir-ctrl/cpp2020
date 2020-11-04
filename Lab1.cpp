// Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <cstdlib>
#include <windows.h>

using namespace std;


void ChangeText(vector<string> text, int length){
	int len, spaces;
	string str, textC;
	vector<string> strC;
	vector<vector<string>> words;
	for (auto& str_ : text){
		istringstream iss(str_);
		while (getline(iss, str, ' '))
			strC.push_back(str);
		words.push_back(strC);
		strC.clear();
	}
	for (auto& lineB : words){
		if (lineB.size() == 0)
			cout << endl;
		else{
			len = -1;
			for (auto linecut : lineB){
				len = len + linecut.length() + 1;
				if (len > length){
					spaces = length - (len - linecut.length());
					if (textC.size() != 0){
						if (spaces > 0){
							textC.insert(textC.begin(), spaces / 2, ' ');
							textC.insert(textC.end(), spaces / 2, ' ');
						}
						cout << textC << endl;
					}
					textC.erase();
					len = linecut.length();
					while (len > length){
						cout << linecut.substr(0, length) << endl;
						linecut.erase(0, length);
						len = len - length;
					}
				}
				textC.append(linecut);
				textC.append(" ");
			}
			spaces = length - (textC.length());
			if (spaces > 0){
				textC.insert(textC.begin(), spaces / 2, ' ');
				textC.insert(textC.end(), spaces / 2, ' ');
			}
			cout << textC << endl;
			textC.erase();
		}
	}
}
int main(int argv, char** argc)
{
	int length;
	string file, str;
	vector<string> text;
	cout << "File name: ";
	cin >> file;
	ifstream fin("text.txt");
    if (!fin.is_open()) {
        cout << "Файл не может быть открыт!\n";
        system("pause");
    }
	while (getline(fin, str))
		text.push_back(str);
	fin.close();
	cout << "File length: ";
    cin >> length;
	ChangeText(text, length);
	return 0;
}
