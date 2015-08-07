#include "argraph.h"  //AttrComparator��AttrDestroyer��argraph.h��

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
		roleAttr = theRole;
	}

private:
	int roleAttr; //��ɫ����

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
	{}

	virtual bool compatible(void *nodeA, void *nodeB)
	{
		Role *a = (Role *)nodeA;
		Role *b = (Role *)nodeB;
		return a->getRoleAttr() == b->getRoleAttr();
	}
};