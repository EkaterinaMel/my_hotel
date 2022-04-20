#include <iostream> 
#include <string>
#include "list.h"

using namespace std;
// 

// Гостиница.
// Сущности: дата, персона, ВИП-персона, комната, бронь, работник.
//
//дальше можно не читать
//
// нужно сделать: 
// 3: Контейнер + итератор. Отдельный хедер
// 4: Внедрить стратегию или хотя бы команду
// 
// ?добавить?:
// 
// - разные работники
// - расчёт зарплаты
// - расчёт счетов за различные услуги, в сумме за всё пребывание
// - доп. услуги
// - таймер брони
// - очередь на бронирование
// - событие в номере
// 
//


// дата 
class date { 
private:
		int day; // день
		int month; // месяц 
		int year; // год
public: 
    date(int d, int m, int y) {
		if ((d > 0)&&(d<32))
			day = d;
		else {
			cout << "incorrect day";
			day = 1;
		}
		if ((m>0)&&(m<13))
			month = m;
		else {
			cout << "incorrect month";
				month = 1;
		}
		if ((y>1800)&&(y<2200))
			year = y;
		else {
			cout << "incorrect year";
				year = 1111;
		}
	}

	// перегрузка оператора присваивания
	date &operator= (const date d)
	{
		day = d.day;
		month = d.month;
		year = d.year;

		return *this;
	}

	// конструктор копирования
	date(const date& d) {
		day = d.day;
		month = d.month;
		year = d.year;
	}


	// печать
	void print() {
		if (day < 10) cout << "0";
		cout << day << ".";
		if (month < 10) cout << "0";
		cout << month << "." << year << "\n";
	}

	};

// сведения о персоне
class person {
private: 
	string FIO; // ФИО
	date birth = date( 1, 1, 2001 ); // дата рождения
public:
	void setPerson(string fio, date b) {
		FIO = fio;
		birth = b;
	}
	void print() {
		cout << FIO << " ";
		birth.print();
	}
	template <class T>
	friend class employee; // дружественный шаблон работник
};

//сведения о номерах гостиницы
class room {
private:
	int number; // номер комнаты
	int price; // цена номера
public:
	void setRoom(int n, int p) {
		if (n>0)
			number = n;
		else cout << "incorrect number";
		if (p>0) 
			price = p;
		else cout << "incorrect price";
	}
};

// бронь
class reservation {
private:
	person quest; // сведения о постояльце
	room residence; // сведения о занятом им номере
	date arrival; // дата заселения
	date exit; // дата выезда из гостиницы
public:
	void setReservation(person q, room r, date d1, date d2) {
		quest = q;
		residence = r;
		arrival = d1;
		exit = d2;
	}

};

// VIP персона
class VIP_person : public person {
private:
	int VIP_status = 1; // уровень статуса
public:
	void setStatus(int s) {
		VIP_status = s;
	}
	void printStatus() {
		cout << "VIP status = " << VIP_status << endl;
	}
};

template <class T>
//работник, также относится к персоне
class employee : public person {
private:
	date start_work = date(1, 1, 2001); // дата начала работы
	string post; // занятый пост
	T salary; // зарплата // значение любого типа
public:
	employee(date s, string p, T sal) {
		start_work = s;
		post = p;
		salary = sal;
	}

	void print() {
		//cout << start_work << endl;
		cout << FIO << " ";
		birth.print();
		cout << "Start work: ";
		start_work.print();
		cout << post << ", " << "salary: " << salary << "\n";
	}
};

int main() {
	ord_list<int> list1;
	list1.add(2);
     
	ord_list<int>::Iterator list_iter;
	list_iter = list1.begin();
	cout << *list_iter << endl;
	list1.add(1);
	--list_iter;
	cout << *list_iter << endl;
	list1.add(1);
	list1.add(0);
	list1.add(9);
	list1.add(10);
	list_iter = list1.find(9);
	cout << *list_iter << endl;
    auto iter2 = list1.begin();
	cout << *iter2 << endl;

	for (list_iter = list1.begin(); list_iter != list1.end(); ++list_iter)
	{
		cout << *list_iter << " ";
	}
	cout << endl;




/*
	date a(3, 1, 2000);
	date b(a);
	a.print(); 
	b.print();
	a = b;
	cout << "-------------\n";
	a.print();
	b.print();
	cout << "--------------------------\n";
	VIP_person Ann;
	cout << "VIP person: \n";
	Ann.setPerson("Madison Ann Rat", a);
	Ann.print();
	Ann.printStatus();
	cout << "----------------------------------\n";
	cout << "emlpoyee1: \n";
	employee<string> Ivan(a, "Cleaner", "food");
	Ivan.setPerson("Ivanov Ivan Ivanovich", a);
	Ivan.print();
	cout << "----------------------------------\n";
	cout << "emlpoyee2: \n";
	employee<double> Anton(a, "Manager", 50000.5);
	Anton.setPerson("Anton Antonov Antonovich", a);
	Anton.print();
*/

	system("pause");
}
