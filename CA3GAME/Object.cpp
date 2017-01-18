#include "Object.h"
#include <iostream>
#include<string>
#include <fstream>
using namespace std;

Object::Object(){}
Object::Object(string name,string type,int cost)
		:mName(name),mType(type),mCost(cost){}

string Object::getName()
{
	return mName;
}

string Object::getType()
{
	return mType;
}

int Object::getCost()
{
	return mCost;
}

void Object::printInfo()
{
	cout<<mName<<"\tCost: "<<mCost;
}
//--------------------------------------------------------------------------------------------------
Weapons::Weapons(){}
Weapons::Weapons(string name,string type,int cost,int lowDam,int highDam)
		:Object(name,type,cost),mLowDam(lowDam),mHighDam(highDam){}

int Weapons::getLowDam()
{
	return mLowDam;
}

int Weapons::getHighDam()
{
	return mHighDam;
}

void Weapons::printInfo()
{
	Object::printInfo();
	cout<<"\tLowDam: "<<mLowDam<<"\tHighDam: "<<mHighDam<<endl;
}

Array<Weapons*> Weapons::loadWeapons(ifstream& inFile)
{
	Array<Weapons*> weapons(10);
	while(inFile.good())
	{
		string garbage;
		inFile>>garbage>>mName;
		inFile>>garbage>>mCost;
		inFile>>garbage>>mLowDam;
		inFile>>garbage>>mHighDam;
		weapons.Push(new Weapons(mName,"Weapon",mCost,mLowDam,mHighDam));
	}
	return weapons;
}

//--------------------------------------------------------------------------------------------------
Misc::Misc(){}
Misc::Misc(string name,string type,int cost,int ammount)
	 :Object(name,type,cost),mAmmount(ammount){}

int Misc::getAmmount()
{
	return mAmmount;
}

void Misc::printInfo()
{
	Object::printInfo();
	cout<<"\tAmmount: "<<mAmmount<<endl;
}

void Misc::increaseCount()
{
	mAmmount++;
}
void Misc::decreaseCount()
{
	mAmmount--;
}

Array<Misc*> Misc::loadMisc(ifstream& inFile)
{
	Array<Misc*> misc(5);
	while(inFile.good())
	{
		string garbage;
		inFile>>garbage>>mName;
		inFile>>garbage>>mType;
		inFile>>garbage>>mCost;
		misc.Push(new Misc(mName,mType,mCost,1));
	}
	return misc;
}