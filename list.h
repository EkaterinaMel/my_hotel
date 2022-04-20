#pragma once
#include <stddef.h>

// двусвязный упорядоченный список
//
//

// структура двусвязного списка
template <class T>
struct list {
	list* next, *last;
	T data;
};

// класс упорядоченного списка с итератором
template <class temp>
class ord_list
{
	friend class Iterator;
protected:
	int size = 0;
	list<temp>* h, * t;

public:


	class Iterator {
		friend class ord_list<temp>;
		list<temp>* ptr;
	public:
		Iterator() {
			ptr = NULL;
		}
		Iterator(list<temp>* l) {
			ptr = l;
		}

		Iterator& operator=(const Iterator& it)
		{
			ptr = it.ptr;
			return *this;
		}
		Iterator& operator++() {
			if (ptr->next != NULL)
				ptr = ptr->next;
			return *this;
		}
		Iterator& operator--() {
			if (ptr->last != NULL)
				ptr = ptr->last;
			return *this;
		}
		temp& operator*() { return ptr->data; }
		bool operator == (const Iterator& it) 
		{
			return (ptr == it.ptr);
		}
		bool operator!=(const Iterator& it) 
		{
			return !(it.ptr == ptr);
		}

	};

	Iterator begin() { return Iterator(h); }
	Iterator end() { return Iterator(t); }
		Iterator find(temp a) {
			auto cur = h;
			while ((cur->data!=a)&&(cur->next != NULL)) {
				cur = cur->next;
		}
			return Iterator(cur);
		}


public:
	ord_list() {
		h = NULL;
		t = NULL;

	}
	~ord_list() {
		list<temp>* cur = new list<temp>;
		while (h != NULL) {
			cur = h;
			h = h->next;
			delete(cur);
		}
	}

	// добавление элемента в соответсвующем порядке
	void add(temp a) {
		list<temp>* cur = new list<temp>;
		cur->data = a;
		if (h == NULL) {
			cur->next = NULL;
			cur->last = NULL;
			h = cur; t = cur;
		}
		else {
			list<temp>* cur1 = new list<temp>;
			cur1 = h;

			while ((cur1->next != NULL) && (cur->data > cur1->data)) {
				cur1 = cur1->next;
			}

			if ((cur1->next == NULL) && (cur->data > cur1->data)) {
				cur->next = NULL;
				cur->last = cur1;
				cur->last->next = cur;
				t = cur;
				cur = h;
			}
			else {
				if (cur1->last == NULL) {
					cur->last = NULL;
					cur->next = h;
					h->last = cur;
					//cur = h;
				}
				else {
					cur->next = cur1;
					cur->last = cur1->last;
					cur->last->next = cur;
					cur->next->last = cur;
					cur = h;
				}
			}
			h = cur;

		}
		size++;

	}

	// изъять элемент с начала
	void push_front() {
		list<temp>* cur = new list<temp>;
		cur = h;
		if (h != NULL) {
			if ((cur->next == NULL) && (cur->last == NULL)) {
				delete(h);
				h = NULL;
				t = NULL;
				//cur = h;
			}
			else {
				cur->last->next = NULL;
				delete cur;
				cur = h;
				h = cur;
			}
			size--;
		}

	}

	// изъять элемент с конца
	void push_back() {
		list<temp>* cur = new list<temp>;
		cur = t;
		if (t != NULL) {
			if ((cur->next == NULL) && (cur->last == NULL)) {
				delete(t);
				h = NULL;
				t = NULL;
				//cur = h;
			}
			else {
				t = t->next;
				t->last = NULL;
				delete(cur);
				cur = NULL;
			}
			size--;
		}

	}

	// очистить список
	void clear() {
		list<temp>* cur = new list<temp>;
		while (h != NULL) {
			cur = h;
			h = h->next;
			delete(cur);
		}
		h = NULL;
		t = NULL;
		size = 0;
	}
	int get_size() {
		return size;
	}
};




