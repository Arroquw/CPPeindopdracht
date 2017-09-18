#pragma once
#include "vector.h"

template<class object>
dynamicVector<object>::dynamicVector() {
	m_nSize = 10;
	m_paMember = new object[m_nSize];
	m_nCurrent = 0;
}

template<class object>
dynamicVector<object>::~dynamicVector() {
	delete[] m_paMember;
}

template<class object>
void dynamicVector<object>::add(const object &cObject) {
	{
		this->m_paMember = new object[m_nSize *= 2];
		for (int i = 0; i < cObject.m_nSize; i++) {
			this->m_paMember[i] = cObject[i];
		}
		delete[] cObject;
		// grootte verdubbelen
		// array element voor element copieren
		// oude array weggooien
	}
	m_paMember[m_nCurrent++] = cObject;
}

template<class object>
object & dynamicVector<object>::at(int index) {
	return m_paMember[index];
	// TODO: insert return statement here
}

template<class object>
const object & dynamicVector<object>::at(int index) const {
	return m_paMember[index];
	// TODO: insert return statement here
}

template<class object>
dynamicVector<object>::operator=(const dynamicVector &other) {
	if (this != &other)
	{
		delete[] this->m_paMember;
		this->m_paMember = other.m_paMember;
		this->m_nCurrent = other.m_nCurrent;
		this->m_nSize = other.m_nSize;
	}
	return *this;
}

template<class object>
dynamicVector<object>::operator=(dynamicVector &&other) {
	m_paMember = other.m_paMember
	other.m_paMember = nullptr;
	this->m_nCurrent = other.m_nCurrent;
	this->m_nSize = other.m_nSize;
	return *this;
}

