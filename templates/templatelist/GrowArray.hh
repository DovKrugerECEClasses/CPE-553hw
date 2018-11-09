#pragma once

#include <iostream>

template<typename T>
class GrowArray {
private:
	int used;
	int capacity;
	T* data;
	void checkGrow() {
		if (  )
			return; // don't grow unless you have to
		T* old = data;

		//TODO: every time the list grows, double it!!!
		data = new T[used+1]; // calls T::T()
		for (int i = 0; i < used; i++)
			data[i] = old[i];
		used++;
	}
public:
	GrowArray() : used(0), capacity(0), data(nullptr) {}
	GrowArray(int  initialCapacity)
		: used(0), capacity(initialCapacity), data( ) //TODO: fix! {
			}
	
	//TODO: add destructor, copy constructor, operator =
	void addEnd(const T& v) {
		checkGrow();
		data[length-1] = v;
	}

	T removeEnd() {
    length--;
		return data[length];
	}
	T operator [](int i) const {
		return data[i];
	}

	T& operator [](int i) {
		return data[i];
	}

	friend std::ostream& operator <<(std::ostream& s, const GrowArray<T>& list) {
    for (int i = 0; i < list.length; i++)
			s << list[i] << ' ';
		return s;
	}
};
