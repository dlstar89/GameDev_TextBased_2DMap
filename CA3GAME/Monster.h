#ifndef MONSTER_H
#define MONSTER_H

#include "Weapon.h"
#include "DLinkedList.h"

using namespace std;

class Player;

class Monster
{
public:
	Monster();
	Monster(string& name,string& type,int hp,int maxHp,int str, int acc,int xpReward,int armour,string& weaponName,int lowDamage,int highDamage);
	bool isDead();
	int getXPReward();
	string getName();
	int getArmour();
	void attack(Player& player);
	void takeDamage(int damage);
	void displayHitPoints();
	void setHP(int newHP);
	DLinkedList<Monster*> load(ifstream& inFile);
	void printStats();

	string mType;
	Weapon mWeapon;
	int HitPoints;
	int MaxHitPoints;
	int Accuracy;
	int Strength;
	int ExpReward;
	int Armour;

private:
	string Name;		
};

#endif //MONSTER_H