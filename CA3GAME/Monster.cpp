#include "Monster.h"
#include "Player.h"
#include "Random.h"
#include <fstream>
#include <iostream>
using namespace std;

Monster::Monster()
{
	Name = "";
	HitPoints = 0;
	Strength = 0;
	Accuracy = 0;
	ExpReward = 0;
	Armour = 0;
	mWeapon.Name = "";
	mWeapon.DamageRange.mLow = 0;
	mWeapon.DamageRange.mHigh = 0;

}

Monster::Monster(string& name,string& type,int hp,int maxHp,int str, int acc,	int xpReward, int armour, string& weaponName,int lowDamage, int highDamage)
{
	Name = name;
	mType=type;
	HitPoints = hp;
	MaxHitPoints=maxHp;
	Strength = str;
	Accuracy = acc;
	ExpReward = xpReward;
	Armour = armour;
	mWeapon.Name = weaponName;
	mWeapon.DamageRange.mLow = lowDamage;
	mWeapon.DamageRange.mHigh = highDamage;
}

bool Monster::isDead()
{
	return HitPoints <= 0;
}

int Monster::getXPReward()
{
	return ExpReward;
}

std::string Monster::getName()
{
	return Name;
}

int Monster::getArmour()
{
	return Armour;
}

void Monster::attack(Player& player)
{
	cout << "A " << Name << " attacks you with a " <<mWeapon.Name<<" ("<<mWeapon.DamageRange.mLow<<" - "<<mWeapon.DamageRange.mHigh<<")"<< endl;

	if(Random(0,player.getAccuracy()) < Accuracy)
	{
		int damage = Random(mWeapon.DamageRange)+Random(1,Strength);
		int totalDamage = damage - (player.getArmour()/2);
		if(totalDamage <= 0)
		{
			cout << "The enemies attack failed to penetrate your armour." << endl;
		}
		else
		{
			cout << "You are hit for " << totalDamage<< " damage!" << endl;
			player.takeDamage(totalDamage);
		}
	}
	else
	{
		cout << "The " << Name << "missed!" << endl;
	}
	cout << endl;
}

void Monster::takeDamage(int damage)
{
	HitPoints -= damage;
}

void Monster::displayHitPoints()
{
	cout << Name << "'s hitpoints = " << HitPoints << endl;
}
void Monster::setHP(int newHP)
{
	HitPoints=newHP;
}

void Monster::printStats()
{
	cout<<"***"<<Name<<"'s STATS***\n";
	cout<<"Name   :"<<Name<<endl;
	cout<<"Type   :"<<mType<<endl;
	cout<<"HP     :"<<HitPoints<<endl;
	cout<<"Weapon :"<<mWeapon.Name<<" ("<<mWeapon.DamageRange.mLow<<" - "<<mWeapon.DamageRange.mHigh<<")"<<endl;
	cout<<"Str    :"<<Strength<<endl;
	cout<<"Acc    :"<<Accuracy<<endl;
	cout<<"Armour :"<<Armour<<endl;
	cout<<"\n\n";
}
DLinkedList<Monster*> Monster::load(ifstream& inFile)
{
	DLinkedList<Monster*> monsters;
	
	while(inFile.good())
	{
		string garbage;
		inFile>>garbage>>Name;
		inFile>>garbage>>mType;
		inFile>>garbage>>HitPoints;
		inFile>>garbage>>MaxHitPoints;
		inFile>>garbage>>Strength;
		inFile>>garbage>>Accuracy;
		inFile>>garbage>>ExpReward;
		inFile>>garbage>>Armour;
		inFile>>garbage>>mWeapon.Name;
		inFile>>garbage>>mWeapon.DamageRange.mLow;
		inFile>>garbage>>mWeapon.DamageRange.mHigh;
		monsters.Append(new Monster(Name,mType,HitPoints,MaxHitPoints,Strength,Accuracy,ExpReward,Armour,mWeapon.Name,mWeapon.DamageRange.mLow,mWeapon.DamageRange.mHigh));
	}
	return monsters;
}