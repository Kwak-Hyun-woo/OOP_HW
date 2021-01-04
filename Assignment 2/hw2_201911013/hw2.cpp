////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 2: Source file
// 1. Complete the implementation of VariableList
// 2. You can add your implementation only in "IMPLEMENT HERE" & "CHANGE HERE"
//    Do not touch other lines; but you can change main() for testing
////////////////////////////////////////////////////////////////////////////////
#include "hw2.h"

#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// You may also want to have additional functions, 
// e.g., static functions or forward declaration of functions, Then
//
// IMPLEMENT HERE
//
// NOTE: DO NOT USE global, static variables
////////////////////////////////////////////////////////////////////////////////

// Constructors
VariableList::VariableList() {
    // IMPLEMENT HERE
    vint_arr = new int[10];
    vfloat_arr = new float[10];
    vstring_arr = new std::string[10];
    idxarr = new int[10];

    pre_size = 0;
    max_size = 10;
}
VariableList::VariableList(const int* initialArray, const int size) {
    // IMPLEMENT HERE
    vint_arr = new int[size*2];
    vfloat_arr = new float[size*2];
    vstring_arr = new std::string[size*2];
    idxarr = new int[size*2];

    for (int i = 0; i < size; ++i) {
        vint_arr[i] = initialArray[i];
        idxarr[i] = 0;
    }

    pre_size = size;
    max_size = size * 2;
}
VariableList::VariableList(const float* initialArray, const int size) {
    // IMPLEMENT HERE
    vint_arr = new int[size*2];
    vfloat_arr = new float[size*2];
    vstring_arr = new std::string[size*2];
    idxarr = new int[size*2];

    for (int i = 0; i < size; ++i) {
        vfloat_arr[i] = initialArray[i];
        idxarr[i] = 1;
    }

    pre_size = size;
    max_size = size * 2;
}
VariableList::VariableList(const std::string* initialArray, const int size) {
    // IMPLEMENT HERE
    vint_arr = new int[size*2];
    vfloat_arr = new float[size*2];
    vstring_arr = new std::string[size*2];
    idxarr = new int[size*2];

    for (int i = 0; i < size; ++i) {
        vstring_arr[i] = initialArray[i];
        idxarr[i] = 2;
    }

    pre_size = size;
    max_size = size * 2;
}

// Destructor
// Note: Please delete(free) the memory you allocated 
VariableList::~VariableList() {
    // IMPLEMENT HERE
    delete[] vint_arr;
    delete[] vfloat_arr;
    delete[] vstring_arr;
    delete[] idxarr;
}

// Member functions
// add: Add the value at the end of the list
void VariableList::add(const int val) {
    // IMPLEMENT HERE
    if (pre_size == max_size) {
        update();
    }
    idxarr[pre_size] = 0;
    vint_arr[pre_size] = val;
    vfloat_arr[pre_size] = 0;
    vstring_arr[pre_size] = "";
    pre_size += 1;
}
void VariableList::add(const float val) {
    // IMPLEMENT HERE
    if (pre_size == max_size) {
        update();
    }
    idxarr[pre_size] = 1;
    vfloat_arr[pre_size] = val;
    vint_arr[pre_size] = 0;
    vstring_arr[pre_size] = "";
    pre_size += 1;
}
void VariableList::add(const std::string& val) {
    // IMPLEMENT HERE
    if (pre_size == max_size) {
        update();
    }
    idxarr[pre_size] = 2;
    vstring_arr[pre_size] = val;
    vint_arr[pre_size] = 0;
    vfloat_arr[pre_size] = 0;
    pre_size += 1;
}

// append: Copy all values of varList and append them at the end of the list
void VariableList::append(const VariableList& varList) {
    // IMPLEMENT HERE
    for (int i = 0; i < varList.pre_size; ++i) {
        switch (varList.idxarr[i]) {
            case 0:
                add(varList.vint_arr[i]);
                break;
            case 1:
                add(varList.vfloat_arr[i]);
                break;
            case 2:
                add(varList.vstring_arr[i]);
        }
    }
}

// replace: replace the value at the given index in the list
bool VariableList::replace(const int idx, const int val) {
    // IMPLEMENT HERE
    if (idx >= pre_size) {
        return false;
    }
    else {
        switch (idxarr[idx])
        {
        case 1:
            vfloat_arr[idx] = 0;
            break;
        default:
            vstring_arr[idx] = "";
        }

        vint_arr[idx] = val;
        idxarr[idx] = 0;
        return true;
    }
}
bool VariableList::replace(const int idx, const float val) {
    // IMPLEMENT HERE
    if (idx >= pre_size) {
        return false;
    }
    else {
        switch (idxarr[idx])
        {
        case 2:
            vstring_arr[idx] = "";
            break;
        default:
            vint_arr[idx] = 0;
        }

        vfloat_arr[idx] = val;
        idxarr[idx] = 1;
        return true;
    }
}
bool VariableList::replace(const int idx, const std::string& val) {
    // IMPLEMENT HERE
    if (idx >= pre_size) {
        return false;
    }
    else {
        switch (idxarr[idx])
        {
        case 0:
            vint_arr[idx] = 0;
            break;
        default:
            vfloat_arr[idx] = 0;
        }

        vstring_arr[idx] = val;
        idxarr[idx] = 2;
        return true;
    }
}

// remove: remove the item at the given index in the list
bool VariableList::remove(const int idx) {
    // IMPLEMENT HERE
    if (idx >= pre_size) {
        return false;
    }
    else {
        for (int i = idx + 1; i < pre_size; ++i) {
            idxarr[i - 1] = idxarr[i];
            vint_arr[i - 1] = vint_arr[i];
            vfloat_arr[i - 1] = vfloat_arr[i];
            vstring_arr[i - 1] = vstring_arr[i];
        }
        idxarr[pre_size - 1 ] = 0;
        vint_arr[pre_size - 1] = 0;
        vfloat_arr[pre_size - 1] = 0;
        vstring_arr[pre_size - 1] = "";
        pre_size -= 1;
        return true;
    }
}

// getSize: return the number of elements of the List
unsigned int VariableList::getSize() const {
    // IMPLEMENT HERE
    return pre_size; // CHANGE HERE
}

// getType: return the data type for the value at the given index
DataType VariableList::getType(const int idx) const {
    // IMPLEMENT HERE
    switch (idxarr[idx]) {
    case 0:
        return DataType::Integer;
        break;
    case 1:
        return DataType::Float;
        break;
    case 2:
        return DataType::Str;
        break;
    default:
        return DataType::NotAvailable;
    }
}

// getValue: copy the value to the variable
bool VariableList::getValue(const int idx, int& val) const {
    // IMPLEMENT HERE
    if (idxarr[idx] != 0 || idx >= pre_size) {
        return false;
    }
    else {
        val =  vint_arr[idx];
        return true;
    }
}
bool VariableList::getValue(const int idx, float& val) const {
    // IMPLEMENT HERE
    if (idxarr[idx] != 1 || idx >= pre_size) {
        return false;
    }
    else {
        val = vfloat_arr[idx];
        return true;
    }
}
bool VariableList::getValue(const int idx, std::string& val) const {
    // IMPLEMENT HERE
    if (idxarr[idx] != 2 || idx >= pre_size) {
        return false;
    }
    else {
        val = vstring_arr[idx];
        return true;
    }
}

////////////////////////////////////////////////////////////////////////////////
// You may also want to implement additional, private member functions here
// NOTE: DO NOT USE global, static variables
//
void VariableList::update() {
    max_size *= 2;

    int* temp_int = new int[pre_size];
    float* temp_float = new float[pre_size];
    std::string* temp_string = new std::string[pre_size];
    int* temp_idx = new int[pre_size];

    for (int i = 0; i < pre_size; ++i) {
        temp_int[i] = vint_arr[i];
        temp_float[i] = vfloat_arr[i];
        temp_string[i] = vstring_arr[i];
        temp_idx[i] = idxarr[i];
    }
    delete[] vint_arr;
    delete[] vfloat_arr;
    delete[] vstring_arr;
    delete[] idxarr;

    vint_arr = new int[max_size];
    vfloat_arr = new float[max_size];
    vstring_arr = new std::string[max_size];
    idxarr = new int[max_size];

    for (int i = 0; i < pre_size; ++i) {
        vint_arr[i] = temp_int[i];
        vfloat_arr[i] = temp_float[i];
        vstring_arr[i] = temp_string[i];
        idxarr[i] = temp_idx[i];
    }

    delete[] temp_int;
    delete[] temp_float;
    delete[] temp_string;
    delete[] temp_idx;
}
//
////////////////////////////////////////////////////////////////////////////////
