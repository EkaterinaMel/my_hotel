#pragma once

// двусвязный упорядоченный список
//
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
protected:
	unsigned int size = 0; 
	list<temp>* h, * t;

public:
	class Iterator {
	protected:
		friend class ord_list<temp>;
		list<temp>* ptr;
	public:
		Iterator() {
			ptr = nullptr;
		}
		~Iterator() { 
			ptr = nullptr;
		}
		Iterator(const Iterator& it) {
			ptr = it.ptr;
		}
		Iterator(list<temp>*l) {
			ptr = l;
		}

		Iterator& operator=(const Iterator& it)
		{
			ptr = it.ptr;
			return *this;
		}
		Iterator& operator++() {
			if ((ptr != nullptr)&&(ptr->next != nullptr))
				ptr = ptr->next;
			return *this;
		}
		Iterator& operator--() {
			if ((ptr != nullptr)&&(ptr->last != nullptr))
				ptr = ptr->last;
			return *this;
		}
		temp& operator*() { return ptr->data; }
		temp& operator->() { return &ptr->data; }
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
			while ((cur->data!=a)&&(cur->next != nullptr)) {
				cur = cur->next;
		}
			return Iterator(cur);
		}

		class const_Iterator : public Iterator {
		public:
			const_Iterator() {
				(*this).ptr = nullptr;
			}
			~const_Iterator() {
				(*this).ptr = nullptr;
			}
			const_Iterator(const Iterator& it) {
				(*this).ptr = it.ptr;
			}
			const_Iterator(list<temp>* l) {
				(*this).ptr = l;
			}
			const temp& operator*() { return (*this).ptr->data; }
			const temp& operator->() { return &(*this).ptr->data; }
			const_Iterator& operator=(const Iterator& it)
			{
				(*this).ptr = it.ptr;
				return *this;
			}
			const_Iterator& operator++() {
				if (((*this).ptr != nullptr) && ((*this).ptr->next != nullptr))
					(*this).ptr = (*this).ptr->next;
				return *this;
			}
			const_Iterator& operator--() {
				if (((*this).ptr != nullptr) && ((*this).ptr->last != nullptr))
					(*this).ptr = (*this).ptr->last;
				return *this;
			}

		};
		const_Iterator cbegin() { return const_Iterator(h); }
		const_Iterator cend() { return const_Iterator(t); }

public:
	ord_list() {
		h = nullptr;
		t = nullptr;

	}
	~ord_list() {
		list<temp>* cur = new list<temp>;
		while (h != nullptr) {
			cur = h;
			h = h->next;
			delete(cur);
		}
	}
	ord_list(ord_list<temp> *l) {
		h = l.h;
		t = l.t;
		size = l.size;
	}

	ord_list<temp> operator=(const ord_list<temp>* l) {
		h = l.h;
		t = l.t;
		size = l.size;
		return *this;

	}
	bool operator==(ord_list<temp>& l) {
		return ((h == l.h) && (t == l.t) && (get_size() == l.get_size()));

	}
	bool operator!=(ord_list<temp>* l) {
		return !((h == l.h) && (t == l.t) && (get_size() == l.get_size()));

	}

	int get_size() { 
		return size; 

	}
	int max_size() {
		return size;
	}

	void swap(ord_list<temp>* l1) {
		ord_list<temp>* l;
		l = l1;
		l1 = (*this);
		(*this) = l;
	}
	void swap(ord_list<temp>* l1, ord_list<temp>*l2) {
		ord_list<temp>* l;
		l = l1;
		l1 = l2;
		l2 = l;
	}

	// 1 если пусто, 0 иначе
	bool empty() { 
		return (h == t)&&(h==nullptr);
	}

	// добавление элемента в соответсвующем порядке
	void add(temp a) {
		list<temp>* cur = new list<temp>;
		cur->data = a;
		if (h == nullptr) {
			cur->next = nullptr;
			cur->last = nullptr;
			h = cur; t = cur;
		}
		else {
			list<temp>* cur1 = new list<temp>;
			cur1 = h;

			while ((cur1->next != nullptr) && (cur->data > cur1->data)) {
				cur1 = cur1->next;
			}

			if ((cur1->next == nullptr) && (cur->data > cur1->data)) {
				cur->next = nullptr;
				cur->last = cur1;
				cur->last->next = cur;
				t = cur;
				cur = h;
			}
			else {
				if (cur1->last == nullptr) {
					cur->last = nullptr;
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
	void pop_front() {
		list<temp>* cur = new list<temp>;
		cur = h;
		if (h != nullptr) {
			if ((cur->next == nullptr) && (cur->last == nullptr)) {
				delete(h);
				h = nullptr;
				t = nullptr;
				//cur = h;
			}
			else {
				h = h->next;
				h->last = nullptr;
				delete cur;
				cur = h;
				h = cur;
			}
			size--;
		}

	}

	// изъять элемент с конца
	void pop_back() {
		list<temp>* cur = new list<temp>;
		cur = t;
		if (t != nullptr) {
			if ((cur->next == nullptr) && (cur->last == nullptr)) {
				delete(t);
				h = nullptr;
				t = nullptr;
				//cur = h;
			}
			else {
				cur->last->next = nullptr;
				delete(cur);
				cur = nullptr;
			}
			size--;
		}

	}

	// очистить список
	void clear() {
		list<temp>* cur = new list<temp>;
		while (h != nullptr) {
			cur = h;
			h = h->next;
			delete(cur);
		}
		h = nullptr;
		t = nullptr;
		size = 0;
	}

};


