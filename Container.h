#pragma once
#include <cstdint>
#include <exception>

template <typename T> class Container {
private:
	uint32_t m_size;
	struct Element {
		T data;
		Element* prev;
		Element* next;
	};
	Element* m_first;
	Element* m_last;
public:
	Container() {
		m_first = NULL;
		m_last = NULL;
		m_size = 0;
	}

	~Container() {
		clear();
	}

	void insert_front(T a) {
		Element* el = new Element;
		el->data = a;
		el->prev = NULL;
		el->next = m_first;

		if ( m_first != NULL ) { 
			m_first->prev = el; 
			m_first = el;
		}

		if ( m_size == 0 ) { 
			m_last = el; 
			m_first = el; 
		}
		++m_size;
	}

	void insert_back(T a) {
		Element* el = new Element;
		el->data = a;
		el->next = NULL;
		el->prev = m_last;

		if ( m_last != NULL ) m_last->next = el;
		if ( m_size == 0 ) {
			m_first = el;
			m_last = el;
		}
		else m_last = el;

		++m_size;
	}

	void delete_first() {
		if ( m_size == 1 ) {
			m_first = NULL;
			m_last = NULL;
			--m_size;
		}
		else if ( m_size == 0 ) throw std::exception("Empty list");
		else { 
			m_first = m_first->next; 
			m_first->prev = NULL;
			--m_size; 
		}

	}

	void delete_last() {
		if ( m_size == 1 ) {
			m_first = NULL;
			m_last = NULL;
		}
		else if ( m_size = 0 ) throw std::exception("Empty list");
		else { 
			m_last = m_last->prev; 
			m_last->next = NULL;
			--m_size; 
		}
	}

	T get_last() {
		if ( m_last != NULL ) return m_last->data;
		else throw std::exception("Empty list");
	}

	T get_first() {
		if ( m_first != NULL ) return m_first->data;
		else throw std::exception("Empty list");
	}

	int size() const{
		return m_size;
	}

	bool is_empty() {
		if ( m_size == 0 ) return true;
		else return false;
	}

	void swap(Container* cont) {
		uint32_t cont_size = cont->m_size;
		cont->m_size = m_size;
		m_size = cont_size;
		Element* slave = cont->m_first;
		cont->m_first = m_first;
		m_first = slave;
		slave = cont->m_last;
		cont->m_last = m_last;
		m_last = slave;
	}

	void reverse() {
		Element* slave = m_first;
		for ( uint32_t i = 0; i < m_size; ++i ) {
			Element* slave2 = slave->next;
			slave->next = slave->prev;
			slave->prev = slave2;
			slave = slave2;
		}
		slave = m_first;
		m_first = m_last;
		m_last = slave;
	}

	void clear() {
		while ( m_first != NULL ) {
			Element* slave = m_first;
			m_first = m_first->next;
			delete slave;
		}
		m_last = NULL;
		m_size = 0;
	}

	class Iterator {
	private:
		Element* curr;
	public:
		Iterator(Element* p){
			curr = p;
		};

		Iterator operator++(int) {
			if ( curr != NULL ) curr = curr->next;
			return *this;
		}

		Iterator operator--(int) {
			if ( curr != NULL ) curr = curr->prev;
			return *this;
		}

		bool operator==(const Iterator& iter) {
			if ( curr == iter.curr ) return true;
			else return false;
		}

		bool operator!=(const Iterator& iter) {
			if ( curr != iter.curr ) return true;
			else return false;
		}

		Element* get_element() const {
			return curr;
		}
	};

	Iterator begin() {
		return Iterator(m_first);
	}

	Iterator end() {
		return Iterator(m_last);
	}
};