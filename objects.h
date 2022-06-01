#pragma once
#include <iostream> 
#include <string>
#include <vector>
#include <chrono>
#include "list.h"

using namespace std;

// добавлена стратегия (в конце)

// Гостиница.
// Сущности: дата, персона, ВИП-персона, комната, бронь, работник.


// сведения о персоне
class person {
private:
	string FIO; // ФИО
//	date birth = date(1, 1, 2001); 
	chrono::year_month_day birth{ chrono::April / 1 / 2001 }; // дата рождения
public:
	person() {}
	void setPerson(string fio) {
		FIO = fio;
	}
	void setPerson(string fio, chrono::year_month_day b) {
		FIO = fio;
		birth = b;
	}
	string getName() {
		return FIO;
	}
	void print() {
		cout << FIO << " ";
		cout << birth;
	}
	bool operator !=(const person& r) {
		return !(FIO == r.FIO);
	}
	bool operator ==(const person& r) {
		return (FIO == r.FIO);
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
	bool status = false; // свободна(0) или занята(1)

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

	bool operator ==(const room& r) {
		return (number == r.number);
	}
	bool operator !=(const room& r) {
		return !((number == r.number));
	}
};

// бронь
class reservation {
private:
	person quest; // сведения о постояльце
	room residence; // сведения о занятом им номере
	chrono::year_month_day arrival; // дата заселения
	chrono::year_month_day exit; // дата выезда из гостиницы
	int check = 0; // общий счет за пребывание и услуги
public:

	reservation() {};
	bool setReservation(person q, vector<room>& vec_rooms, chrono::year_month_day d1, chrono::year_month_day d2) {
		int i = 1;
		while ((vec_rooms[i].status) && (i < vec_rooms.size() - 1)) {
			++i;
		}
		if (!(vec_rooms[i].status)) {
			residence = vec_rooms[i];
			quest = q;
			arrival = d1;
			exit = d2;
			vec_rooms[i].status = true;
			check = vec_rooms[i].price;
			return false;

		}
		else {
			cout << "No vacant rooms!\n";
			return true;
			//			vec_rooms[0].all_status = 1;
		}


	}
	void infoRoom() {
		//residence.info();
		cout << residence.number << ", " << "cost " << residence.price << " roubles" << "\n";
	}

	chrono::year_month_day getExit() {
		return exit;
	}

	string getNamePerson() {
		return quest.getName();
	}

	void freeRoom(vector<room>& vec_rooms) {
		vec_rooms[residence.number].status = false;
		//vec_rooms[0].all_status = 0;


	}

	// по дате выезда!!
	bool operator <(const reservation& r) {
		return (exit < r.exit);

	}
	bool operator >(const reservation& r) {
		return (exit > r.exit);

	}
	bool operator ==(const reservation& r) {
		return (quest == r.quest) && (residence == r.residence) && (arrival == r.arrival) && (exit == r.exit);

	}
	bool operator !=(const reservation& r) {
		return !((quest == r.quest) && (residence == r.residence) && (arrival == r.arrival) && (exit == r.exit));

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
	chrono::year_month_day start_work{ chrono::April, 1, 2001 }; // дата начала работы
	string post; // занятый пост
	T salary; // зарплата // значение любого типа
public:
	employee(chrono::year_month_day s, string p, T sal) {
		start_work = s;
		post = p;
		salary = sal;
	}

	void print() {
		cout << FIO << " " << birth;
		//birth.print();
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
