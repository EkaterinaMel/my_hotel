#include <iostream> 
#include <string>
#include <vector>
#include <chrono>
#include <list>
#include "windows.h"

#include "list.h" // в этом файле находится реализация двусвязного упорядоченного списка
#include "objects.h" // в этом файле находятся все объекты предметной области и их функции, включая стратегию
#include "release.h" // в файле release.ccp находятся функции, нужные для реализации интерфейса

using namespace std;


// Гостиница.
// Сущности: дата, персона, ВИП-персона, комната, бронь, работник.
// 
// дальше можно не читать
//  
// нужно сделать: 
// 3: Контейнер + итератор. Отдельный хедер
// 4: Внедрить стратегию или хотя бы команду
// 
// ?добавить?:
// 
// - расчёт счетов за различные услуги, в сумме за всё пребывание +
// - доп. услуги +
// - таймер брони +-
// - очередь на бронирование + 
// 
// ?как внедрить мой список?:
// - список броней, расположены по порядку в соответствии с тем, 
// какая бронь заканчивается раньше, т.к. её мы будем удалять первой,
// т.е. отсортированы по дате выезда
// также у нас есть определенное кол-во комнат. они будут где-то храниться
// когда человек приходит, для него ищется подходящая комната(свободная)
// создаётся бронь с этой комнатой, она занята пока бронь не закончится. 
// если комнат подходящих нет, бронь не создаётся, чел уходит
// 
//


int main() {

	room rooms; rooms.setRoom(0, 0);
	vector<room> vec_rooms;
	vec_rooms.push_back(rooms);

	for (int i = 1; i < 5; ++i) {
		rooms.setRoom(i, 1000);
		vec_rooms.push_back(rooms);
	}

	person per1;
	chrono::year_month_day d1{ chrono::May/ 1/ 2022 };
	chrono::year_month_day d2{ chrono::May/ 1/ 2022 };
	per1.setPerson("Ivanov Billy Billivich");
	ord_list<reservation> reservations;
	reservation res1;
	ord_list<reservation>::Iterator list_iter = reservations.begin();

	string name = "";
	int i = 0;
	unsigned int d = 1, days;
	while (i < 11) {
		
		d1 = chrono::year_month_day{ chrono::May / (d+i) / 2022 };
		cout << "Today date: " << d1<<"\n";
		cout << "Welcome! Please enter your name: ";
		cin >> name;
		if (name == "0") break;
		cout << "How long days do you want to stay here? ";
		cin >> days;
		if ((!cin) || (days <= 0)) break;


		if (d + i + days > 30) {
			d2 = chrono::year_month_day{chrono::May/((d + i + days) - 30 * ((d + i + days) / 30))/2022};
			d2 += chrono::months{ ((d + i + days) / 30) }; 
		}
		else 
			d2 = chrono::year_month_day{ chrono::May / (d + i + days)  / 2022 }; 
		
		per1.setPerson(name);
		bool b = res1.setReservation(per1, vec_rooms, d1, d2);
		if (!b) {
			cout << "Thanks! Your room is ";
			res1.infoRoom();
			reservations.add(res1);
			cout << "\nDo you want something else?\n";
			list_iter = reservations.find(res1);
			button(list_iter);	
		}

		list_iter = reservations.begin();
		while ((*list_iter).getExit() == d1) {
			(*list_iter).freeRoom(vec_rooms);
			cout << (*list_iter).getNamePerson() << ", thanks for the stay, total check is " << (*list_iter).getCheck() <<" roubles. Goodbye!\n";
			reservations.pop_front();
			list_iter = reservations.begin();
		}

		Sleep(100);
		cout << " . ";
		Sleep(100);
		cout << " . ";
		Sleep(100);
		cout << " . \n\n";
		i++;
	}
	cout << "Thanks for living here, but we are closed!\n";

system("pause");
}
