#include <iostream> 
#include <string>
#include <vector>
#include "windows.h"

#include "list.h"
#include "objects.h"

using namespace std;

void makeButtons() {
	//cout << "\n";
	cout << "* * * * * *  " << "* * * * * *  " << "* * * * * * *\n";
	cout << "*  Water  *  " << "*  Food   *  " << "* Cleanning *\n";
	cout << "*   10 r  *  " << "*  100 r  *  " << "*   1000 r  *\n";
	cout << "* * * * * *  " << "* * * * * *  " << "* * * * * * *\n";

}

void button(ord_list<reservation>::Iterator& per) {
	HANDLE hin = GetStdHandle(STD_INPUT_HANDLE); // получаем дескриптор
	INPUT_RECORD InputRecord; // используется для возвращения информации о входных сообщениях в консольном входном буфере
	DWORD Events; // unsigned long
	COORD coord; // для координат X, Y

	/*Запретить выделение консоли*/
	DWORD prev_mode;
	GetConsoleMode(hin, &prev_mode);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));

	SetConsoleMode(hin, ENABLE_MOUSE_INPUT); // разрешаем обработку мыши

	makeButtons();

	while (true)
	{
		ReadConsoleInput(hin, &InputRecord, 1, &Events); // считывание 
		int x0 = 0, y0 = 0, x1 = 10, y1 = 2;
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) // левая кнопка
		{
			coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
			coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			//cout << "left - X = " << coord.X << ", Y = " << coord.Y << endl;
			if ((coord.X >= x0) && (coord.X <= x1)) {
				servant water(new waterServ);
				water.serv(per);
			}
			else if ((coord.X >= x0 + 3) && (coord.X <= x1 + 13)) {
				servant food(new foodServ);
				food.serv(per);
			}
			else if ((coord.X >= x0 + 16) && (coord.X <= x1 + 28)) {
				servant cleanning(new cleanningServ);
				cleanning.serv(per);
			}
			break;
			}
		}
		SetConsoleMode(hin, prev_mode);
	}
