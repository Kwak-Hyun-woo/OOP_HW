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
}
VariableList::VariableList(const int* initialArray, const int size) {
    // IMPLEMENT HERE
}
VariableList::VariableList(const float* initialArray, const int size) {
    // IMPLEMENT HERE
}
VariableList::VariableList(const std::string* initialArray, const int size) {
    // IMPLEMENT HERE
}

// Destructor
// Note: Please delete(free) the memory you allocated 
VariableList::~VariableList() {
    // IMPLEMENT HERE
}

// Member functions
// add: Add the value at the end of the list
void VariableList::add(const int val) {
    // IMPLEMENT HERE
}
void VariableList::add(const float val) {
    // IMPLEMENT HERE
}
void VariableList::add(const std::string& val) {
    // IMPLEMENT HERE
}

// append: Copy all values of varList and append them at the end of the list
void VariableList::append(const VariableList& varList) {
    // IMPLEMENT HERE
}

// replace: replace the value at the given index in the list
bool VariableList::replace(const int idx, const int val) {
    // IMPLEMENT HERE
    return false; // CHANGE HERE
}
bool VariableList::replace(const int idx, const float val) {
    // IMPLEMENT HERE
    return false; // CHANGE HERE
}
bool VariableList::replace(const int idx, const std::string& val) {
    // IMPLEMENT HERE
    return false; // CHANGE HERE
}

// remove: remove the item at the given index in the list
bool VariableList::remove(const int idx) {
    // IMPLEMENT HERE
    return false; // CHANGE HERE
}

// getSize: return the number of elements of the List
unsigned int VariableList::getSize() const {
    // IMPLEMENT HERE
    return 0; // CHANGE HERE
}

// getType: return the data type for the value at the given index
DataType VariableList::getType(const int idx) const {
    // IMPLEMENT HERE
    return DataType::NotAvailable; // CHANGE HERE
}

// getValue: copy the value to the variable
bool VariableList::getValue(const int idx, int& val) const {
    // IMPLEMENT HERE
    return false; // CHANGE HERE
}
bool VariableList::getValue(const int idx, float& val) const {
    // IMPLEMENT HERE
    return false; // CHANGE HERE
}
bool VariableList::getValue(const int idx, std::string& val) const {
    // IMPLEMENT HERE
    return false; // CHANGE HERE
}

////////////////////////////////////////////////////////////////////////////////
// You may also want to implement additional, private member functions here
// NOTE: DO NOT USE global, static variables
//
// IMPLEMENT HERE
//
////////////////////////////////////////////////////////////////////////////////
