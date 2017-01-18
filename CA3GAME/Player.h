#ifndef PLAYER_H
#define PLAYER_H

#include "Weapon.h"
#include "Monster.h"
#include "Array.h"
#include "Object.h"
#include "DLinkedList.h"
#include "Map.h"
#include<iostream>
#include<vector>
using namespace std;

class Player
{
public:
	Player();
	Player(string name,string password,string rank,int health,int maxHealth,int exp,int expNextLvl,int level,int strength,int accuracy,int armour,int rePoints,int kills,int gold,string questType,bool quest,bool finQuest,string& weapon,string location,Array<Weapons*> weapons,Array<Misc*>misc,int x,int y);
	void inventory();//prints out players inventory
	void weapons();
	void misc();
	void setLocation(string newLocation);
	void save(ofstream& outFile);
	void load(ifstream& inFile);
	void printHelp();
	bool open(string type);
	void check(Misc* misc);
	string use(Map<char>* map);
	void equip();
	string shop(Array<Weapons*> itrweapons,Array<Misc*>itrmisc,Player* player);
	string sell(string sell);
	string buy(Array<Weapons*> itrweapons,Array<Misc*>itrmisc,string buy);
	string getQuest(Map<char>* questMap);
	bool getQuestUpdate();
	void setQuestUpdate(bool newUpd);
	string getQuestType();
	void restoreHP();
	Map<char>* backToHomeBase(DListIterator<Map<char>*> maps);
	void goldReward(int goldr);
	void xpReward(int xpre);
	string getLocation();
	string getName();
	string getPassword();
	void setName(string newName);
	void setPassword(string newPass);
	void setRePoints(int reP);
	void print();	
	bool isDead();
	void createPlayer();
	void takeDamage(int damage);
	int getAccuracy();
	int getArmour();
	int getRePoints();
	bool attack(Monster& monster);
	void levelUp();
	string rest();
	void victory(int xp);
	void displayHitPoints();
	Weapon mWeapon;
	int mExp;
	int mLevel;
	int mX;
	void setX(int newX);
	int mY;
	void setY(int newY);
	Array<Weapons*> mWeapons;
	Array<Misc*> mMisc;

private:
	string mName;
	string mPassword;
	string mRank;
	string mLocation;	
	string mQuestType;
	int mHealth;
	int mMaxHealth;	
	int mExpNextLvl;
	int mStrength;
	int mAccuracy;
	int mArmour;
	int mRePoints;
	int mKills;
	int mGold;
	bool mQuest;
	bool mFinQuest;
};

#endif