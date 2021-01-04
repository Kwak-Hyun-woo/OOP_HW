////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 3: Source file
// 1. Complete the implementation of Ordered
// 2. Add a new class, OrderedSet, using class inheritance
////////////////////////////////////////////////////////////////////////////////
#include "hw3.h"

#include <iostream>
#include <limits>

Ordered::Ordered() {
	max_size = 5;
	order_arr = new int[max_size];
}

Ordered::~Ordered() {
	delete[] order_arr;
}

void Ordered::add(int v) {
    int check = 0;

    if ((m_size + 1) == max_size) {
        update();
    }
    if (m_size == 0) {
        order_arr[0] = v;
    }
    else {
        for (int i = 0; i < m_size; i++) {
            if (order_arr[i] >= v) {
                add_move(order_arr, i);
                order_arr[i] = v;
                break;
            }
            check += 1;
        }
        if (check == m_size) {
            order_arr[m_size] = v;
        }
    }
    m_size += 1;
}

void Ordered::remove(int index) {
    for (int i = index; i < m_size - 1; i++) {
        order_arr[i] = order_arr[i + 1];
    }
    order_arr[m_size] = NULL;
    m_size -= 1;
}

void Ordered::add(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        add(arr[i]);
    }
}

int Ordered::operator[](int index) {
    if (index < m_size) {
        return order_arr[index];
    }
    else {
        return std::numeric_limits<int>::min();
    }
}

bool Ordered::operator>>(int v) {
    for (int i = 0; i < m_size; ++i) {
        if (order_arr[i] == v) {
            return true;
        }
    }
	return false;
}

void Ordered::update() {
    max_size *= 2;

    int* temp_order_arr = new int[m_size];

    for (int i = 0; i < m_size; ++i) {
        temp_order_arr[i] = order_arr[i];
    }
    delete[] order_arr;

    order_arr = new int[max_size];

    for (int i = 0; i < m_size; ++i) {
        order_arr[i] = temp_order_arr[i];
    }
    delete[] temp_order_arr;
}

void Ordered::add_move(int* arr, int idx) {
    for (int i = m_size; i > idx; i--) {
        arr[i] = arr[i - 1];
    }
    arr[idx] = NULL;
}

void OrderedSet::add(int v) {
    int check = 0;

    if ((m_size + 1) == max_size) {
        update();
    }
    if (m_size == 0) {
        order_arr[0] = v;
    }
    else {
        for (int i = 0; i < m_size; i++) {
            if (order_arr[i] > v) {
                add_move(order_arr, i);
                order_arr[i] = v;
                break;
            }
            if (order_arr[i] == v) {

                return;
            }
            check += 1;
        }
        if (check == m_size) {
            order_arr[m_size] = v;
        }
    }
    m_size += 1;
}
void OrderedSet::add(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        add(arr[i]);
    }
}