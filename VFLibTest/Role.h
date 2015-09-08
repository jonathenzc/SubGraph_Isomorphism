#include "argraph.h"  //AttrComparator和AttrDestroyer在argraph.h中
#include <iostream>

using namespace std;

class Role
{
public:
	Role(int theRole) :roleAttr(theRole)
	{}

	int getRoleAttr()
	{
		return roleAttr;
	}

	void setRoleAttr(int theRole)
	{
		this->roleAttr = theRole;
	}

private:
	int roleAttr; //角色属性

};

class RoleDestroyer : public AttrDestroyer
{
public:
	virtual void destroy(void *p)
	{
		delete p;
	}
};

class RoleComparator : public AttrComparator
{
public:
	RoleComparator()
	{
	}

	virtual bool compatible(void *nodeA, void *nodeB)
	{
		Role *a = (Role *)nodeA;
		Role *b = (Role *)nodeB;
		//cout << a->getRoleAttr() << " a b " << b->getRoleAttr();
		return a->getRoleAttr() == b->getRoleAttr();
	}
};