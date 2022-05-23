#pragma once
#include <iostream> 
#include <string>
#include <vector>
#include "list.h"

using namespace std;

// добавлена стратегия (в конце)

// Гостиница.
// Сущности: дата, персона, ВИП-персона, комната, бронь, работник.

// дата 
class date {
private:
	int day; // день
	int month; // месяц 
	int year; // год
public:
	date() {}
	date(int d, int m, int y) {
		if ((d > 0) && (d < 32))
			day = d;
		else {
			cout << "incorrect day";
			day = 1;
		}
		if ((m > 0) && (m < 13))
			month = m;
		else {
			cout << "incorrect month";
			month = 1;
		}
		if ((y > 1800) && (y < 2200))
			year = y;
		else {
			cout << "incorrect year";
			year = 1111;
		}
	}

	void setDate(int d, int m, int y) {
		if ((d > 0) && (d < 32))
			day = d;
		else {
			cout << "incorrect day";
			day = 1;
		//	return 1;
		}
		if ((m > 0) && (m < 13))
			month = m;
		else {
			cout << "incorrect month";
			month = 1;
		//	return 1;
		}
		if ((y > 1800) && (y < 2200)){
			year = y;
		//	return 0;
		}
		else {
			cout << "incorrect year";
			year = 1111;
		//	return 1;
		}
	}

	// перегрузка оператора присваивания
	date& operator= (const date d)
	{
		if ((d.day > 0) && (d.month > 0) && (d.year > 0)) {
			day = d.day;
			month = d.month;
			year = d.year;
		}
		else cout << "Error data!!!\n";

		return *this;
	}

	bool operator < (const date& d) {
		if (year < d.year)
			return true;
		else if (year == d.year) {
			if (month < d.month) return true;
			else if (month == d.month) {
				return (day < d.day);
			}
			else return false;
		}
		else return false;

	}
	bool operator > (const date& d) {
		if (year > d.year)
			return true;
		else if (year == d.year) {
			if (month > d.month) return true;
			else if (month == d.month) {
				return (day > d.day);
			}
			else return false;
		}
		else return false;
	}
	bool operator == (const date& d) {
		return ((year == d.year) && (month == d.month) && (day == d.day));

	}

	// конструктор копирования
	date(const date& d) {
		if ((d.day > 0) && (d.month > 0) && (d.year > 0)) {
			day = d.day;
			month = d.month;
			year = d.year;
		}
		else cout << "Error data!!!\n";
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
	date birth = date(1, 1, 2001); // дата рождения
public:
	person() {}
	void setPerson(string fio) {
		FIO = fio;
	}
	void setPerson(string fio, date b) {
		FIO = fio;
		birth = b;
	}
	string getName() {
		return FIO;
	}
	void print() {
		cout << FIO << " ";
		birth.print();
	}
	bool operator !=(person r) {
		if (FIO == r.FIO)
			return 0;
		else return 1;
	}
	bool operator ==(person r) {
		if (FIO == r.FIO)
			return 1;
		else return 0;
	}
	template <class T>
	friend class employee; // дружественный шаблон работник
};

//сведения о номерах гостиницы
class room {
	friend class reservation;
private:
	int number = 0; // номер комнаты
	int price = 0; // цена номера
protected:
	bool status = 0; // свободна(0) или занята(1)

public:
	static bool all_status; // если заняты все комнаты = 1 
	room() {}
	void setRoom(int n, int p) {
		if (n >= 0)
			number = n;
		else cout << "incorrect number";
		if (p >= 0)
			price = p;
		else cout << "incorrect price";
	}
	void info() {
		cout << "Room numder: " << number << "\t" << "Price: " << price << "\t" << "Status: " << status << "\n";
	}

	bool operator ==(room r) {
		if (number == r.number)
			return 1;
		else return 0;
	}
	bool operator !=(room r) {
		if (number == r.number)
			return 0;
		else return 1;
	}
};

// бронь
class reservation {
private:
	person quest; // сведения о постояльце
	room residence; // сведения о занятом им номере
	date arrival; // дата заселения
	date exit; // дата выезда из гостиницы
	int check = 0; // общий счет за пребывание и услуги
public:

	reservation() {};
	bool setReservation(person q, vector<room>& vec_rooms, date d1, date d2) {
		int i = 1;
		while ((vec_rooms[i].status == 1) && (i < vec_rooms.size() - 1)) {
			++i;
		}
		if (vec_rooms[i].status == 0) {
			residence = vec_rooms[i];
			quest = q;
			arrival = d1;
			exit = d2;
			vec_rooms[i].status = 1;
			check = vec_rooms[i].price;
			return 0;

		}
		else {
			cout << "No vacant rooms!\n";
			return 1;
			//			vec_rooms[0].all_status = 1;
		}


	}
	void infoRoom() {
		//residence.info();
		cout << residence.number << ", " << "cost " << residence.price << " roubles" << "\n";
	}

	date getExit() {
		return exit;
	}

	string getNamePerson() {
		return quest.getName();
	}

	void freeRoom(vector<room>& vec_rooms) {
		vec_rooms[residence.number].status = 0;
		//vec_rooms[0].all_status = 0;


	}

	// по дате выезда!!
	bool operator <(reservation r) {
		return (exit < r.exit);

	}
	bool operator >(reservation r) {
		return (r.exit < exit);

	}
	bool operator ==(reservation r) {
		if (quest == r.quest)
			if (residence == r.residence)
				if (arrival == r.arrival)
					if (exit == r.exit)
						return 1;
					else return 0;
				else return 0;
			else return 0;
		else return 0;

	}
	bool operator !=(reservation r) {
		if (quest == r.quest)
			if (residence == r.residence)
				if (arrival == r.arrival)
					if (exit == r.exit)
						return 0;
					else return 1;
				else return 1;
			else return 1;
		else return 1;

	}
	void plusCheck(int c) {
		check += c;
	}
	int getCheck() {
		return check;
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

/**/
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

// стратегия
// постоялец может заказать дополнительную услугу
class service {
public:
	virtual ~service() {}
	virtual void serv(ord_list<reservation>::Iterator &per) = 0; // передаются сведения о брони клиента
};

// еда
class foodServ : public service
{
public:
	void serv(ord_list<reservation>::Iterator& per) {
		cout << "*..food..* \n";
		(*per).plusCheck(100);
	}
};

// вода
class waterServ : public service
{
public:
	void serv(ord_list<reservation>::Iterator& per) {
		cout << "*.water.* \n";
		(*per).plusCheck(10);
	}
};

// уборка
class cleanningServ : public service
{
public:
	void serv(ord_list<reservation>::Iterator& per) {
		cout << "*...cleanning...* \n";
		(*per).plusCheck(1000);
	}
};

class servant
{
private:
	service* p;
public:
	servant(service* s)  {
		p = s;
	}
	~servant() { 
		delete p; 
	}
	void serv(ord_list<reservation>::Iterator& per) {
		p->serv(per);
	}
};
