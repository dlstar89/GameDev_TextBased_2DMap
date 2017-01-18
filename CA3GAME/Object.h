#ifndef OBJECT_H
#define OBJECT_H

#include "DLinkedList.h"
#include "Array.h"
#include<iostream>
using namespace std;


class Object
{
public:
	Object();
	Object(string name,string type,int cost);
	string getName();
	string getType();
	int getCost();
	virtual void printInfo();
	
protected:
	string mName;
	string mType;
	int mCost;	
};
//-----------------------------------------------------------------------------
class Weapons:public Object
{
public:
	Weapons();
	Weapons(string name,string type,int cost,int lowDam,int highDam);
	int getLowDam();
	int getHighDam();
	void printInfo();
	Array<Weapons*> loadWeapons(ifstream& inFile);

protected:
	int mLowDam;
	int mHighDam;
};
//-----------------------------------------------------------------------------
class Misc:public Object
{
public:
	Misc();
	Misc(string name,string type,int cost,int ammount);
	int getAmmount();
	void printInfo();
	void increaseCount();
	void decreaseCount();
	Array<Misc*> loadMisc(ifstream& inFile);

protected:
	int mAmmount;
};

#endif //OBJECT_H