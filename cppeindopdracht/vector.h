#pragma once
template <class object>
class dynamicVector {
public:
	dynamicVector();
	virtual ~dynamicVector();
	virtual void add(const object&);
	virtual object & at(int index);
	virtual const object & at(int index) const;
	virtual operator=(const dynamicVector&);
	virtual operator=(dynamicVector&&);
private:
	object* m_paMember;
	int m_nSize;
	int m_nCurrent;
};

#include "vector.hpp"
