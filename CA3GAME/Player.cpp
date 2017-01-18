#include "Player.h"
#include "Random.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

Player::Player(){}
Player::Player(string name,string password,string rank,int health,int maxHealth,int exp,int expNextLvl,int level,int strength,int accuracy,int armour,int rePoints,int kills,int gold,string questType,bool quest,bool finQuest,string& weapon,string location,Array<Weapons*> weapons,Array<Misc*>misc,int x,int y)
	:mName(name),mPassword(password),mRank(rank),mHealth(health),mMaxHealth(maxHealth),mExp(exp),mExpNextLvl(expNextLvl),mStrength(strength),mAccuracy(accuracy),mArmour(armour),mRePoints(rePoints),mKills(kills),mGold(gold),mQuestType(questType),mQuest(quest),mFinQuest(finQuest),mLocation(location),mWeapons(weapons),mMisc(misc),mX(x),mY(y){}

string Player::getName()
{
	return mName;
}
void Player::setName(string newName)
{
	mName=newName;
}
string Player::getPassword()
{
	return mPassword;
}
void Player::setPassword(string newPass)
{
	mPassword=newPass;
}
string Player::getLocation()
{	
	return mLocation;
}
void Player::setLocation(string newLocation)
{
	mLocation=newLocation;
}
bool Player::isDead()
{
	return mHealth <= 0;
}
int Player::getAccuracy()
{
	return mAccuracy;
}
int Player::getArmour()
{
	return mArmour;
}
int Player::getRePoints()
{
	return mRePoints;
}
void Player::takeDamage(int damage)
{
	mHealth -= damage;
}
void Player::setRePoints(int reP)
{
	mRePoints=reP;
}
bool Player::getQuestUpdate()
{
	return mQuest;
}
void Player::setQuestUpdate(bool newUpd)
{
	mFinQuest=newUpd;
}
void Player::restoreHP()
{
	mHealth=mMaxHealth;
}
void Player::goldReward(int gr)
{
	mGold+=gr;
}
void Player::xpReward(int xpr)
{
	mExp+=xpr;
}
string Player::getQuestType()
{
	return mQuestType;
}

//brings player back to its homebase
Map<char>* Player::backToHomeBase(DListIterator<Map<char>*> maps)
{
	for(maps.Start();maps.Valid();maps.Forth())
	{
		if(maps.Item()->getType() == "homebase")
		{
			mX=maps.Item()->Height()/2;
			mY=maps.Item()->Width()/2;
			mLocation=maps.Item()->getName();
			return maps.Item();
		}
	}
	return maps.Item();
}

//creates new player
void Player::createPlayer()
{
	string input;

	mRank       ="NOVICE";
	mHealth     =50;
	mMaxHealth  =50;
	mExp        =0;
	mExpNextLvl =400;
	mLevel      =1;
	mStrength   =1;
	mAccuracy   =1;
	mArmour     =1;
	mRePoints   =18;
	mKills      =0;
	mGold		=1000;
	mQuestType  ="none";
	mQuest      =false;
	mFinQuest   =false;
	mWeapon.Name="Fists";
	mWeapon.DamageRange.mLow=1;
	mWeapon.DamageRange.mHigh=5;
	mLocation    ="Tavern";
	mX=2;
	mY=2;
	
	cout<<"Enter new users name: ";
	cin>>input;
	mName=input;
	cout<<"Enter new password: ";
	cin>>input;
	mPassword=input;

	cout<<"NEW PLAYER WAS SUCCESFULLY CREATED..."<<endl;
	cout<<"\n\nTHIS ARE VERY DARK TIMES..."<<endl;
	cout<<"Before you will head out slaying all the monsters wisit our 'M' merchant to buy some equipment!"<<endl;
	cout<<"TYPE IN 'help' if you will be ever lost in the commands"<<endl;
	cin.get();

}

void Player::setX(int newX)
{
	mX=newX;
}
void Player::setY(int newY)
{
	mY=newY;
}

//if player wins a battle he/she will be rewarded with xp
void Player::victory(int xp)
{
	cout << "You won the battle" << endl;
	cout << "You gained " << xp << " experience points" << endl;
	mExp += xp;
	mKills+=1;

	if(mKills >= 3)
	{
		mRank="SKILLED_KILLER";
		mRePoints+=2;
	}
	if(mKills >= 6)
	{
		mRank="THIRSTY_FOR_BLOOD";
		mRePoints+=3;
	}
	if(mKills >= 10)
	{
		mRank="NEW_CHIEF_IN_TOWN";
		mRePoints+=5;
	}
	if(mKills >= 15)
	{
		mRank="F_PSYCHO!!!";
		mRePoints+=7;
	}
}

//when player reaches new level redistribution points will be added
void Player::levelUp()
{
	if(mExp >= mExpNextLvl)
	{
		cout << "\nYou gained a level!\nFind a resting place to redistribute your status points!" << endl;
		mLevel++;
		mRePoints+=5;
		mExpNextLvl = mLevel*mLevel*100;
		mHealth = mMaxHealth;
		mExp=0;
	}
}

//possible outcomes when player attacks
bool Player::attack(Monster& monster)
{
	string selection;
	cout << "Attack OR Run\nChoice: ";
	cin >> selection;
	cout << endl;

	if(selection == "attack" || selection == "Attack")
	{
		cout << "You attack an " << monster.getName()<<" with a "<<mWeapon.Name<<" ("<<mWeapon.DamageRange.mLow<<" - "<<mWeapon.DamageRange.mHigh<<")"<<endl;

		if(Random(0,monster.Accuracy) < mAccuracy)
		{
			int damage = Random(mWeapon.DamageRange)+Random(1,mStrength);
			int totalDamage = damage - (monster.getArmour()/2);

			if(totalDamage <= 0)
			{
				cout<<"Your attack was absorbed by the enemies armour!"<<endl;
			}
			else
			{
				cout <<"You attack for "<< totalDamage<<" damage!" << endl;
				monster.takeDamage(totalDamage);
			}
		}
		else
		{
			cout << "You miss!" << endl;
		}
	}
	if(selection == "run" || selection == "Run")
	{
		int roll = Random(1,4);
		if(roll == 1)
		{
			cout << "You escaped the fight!" << endl;
			return true;
		}
		else
		{
			cout << "You could not escape the fight!" << endl;
			
		}
	}
	return false;
}

void Player::weapons()
{
	cout<<"\n***WEAPONS***\n";
	for(int i=0;i<mWeapons.numOfElements();i++)
	{
		cout<<i+1<<")";mWeapons[i]->printInfo();
	}
}
void Player::misc()
{
	cout<<"\n***MISC ITEMS***\n";
	for(int i=0;i<mMisc.numOfElements();i++)
	{
		cout<<i+1<<")";mMisc[i]->printInfo();
	}
}

//prints players inventory
void Player::inventory()
{
	cout<<"\n==="<<mName<<"'s INVENTORY===\n";
	weapons();
	misc();
	
}

//this function is called when player steps on 'T' whic is treasure chest and player wants to open it
bool Player::open(string type)
{
	int input;
	misc();
	cout<<"Which item to use: ";
	cin>>input;
	if(input > mMisc.numOfElements() || input<=0)
	{
		cout<<"No such item in the inventory"<<endl;
		return false;
	}
	else if(mMisc[input-1]->getAmmount() >0 && type==mMisc[input-1]->getType())
	{
		mMisc[input-1]->decreaseCount();
		if(mMisc[input-1]->getAmmount() == 0)
		{
			mMisc.Remove(input-1);
		}
		return true;
	}
	return false;
}

//if player picks up a MISC item it has to be checked if it just should increase the count of it if it allready exists in player inventory or it has to be added to the inventory
void Player::check(Misc* misc)
{
	for(int i=0;i<mMisc.numOfElements();i++)
	{
		if(misc->getName() == mMisc[i]->getName())
		{
			mMisc[i]->increaseCount();
			return;
		}
	}
	mMisc.Push(misc);
}

//allows player to use MISC items
string Player::use(Map<char>* map)
{
	int input=0;
	int restoreHP=mMaxHealth;	
	if(mMisc.numOfElements()==0)
	{
		cout<<"YOUR MISC INVENTORY IS EMPTY!"<<endl;
		cin.get();
		return"a";
	}
	misc();
	cout<<"Which item to use: ";
	cin>>input;
	if(input > mMisc.numOfElements() || input<=0)
	{
		cout<<"No such item in the inventory"<<endl;
		return"a";
	}
	else if(mMisc[input-1]->getAmmount() >0 )
	{		
		if(mMisc[input-1]->getType()=="SHP" || mMisc[input-1]->getType()=="MHP" || mMisc[input-1]->getType()=="BHP")
		{
			mMisc[input-1]->decreaseCount();
			if(mMisc[input-1]->getType()=="SHP")
			{
				restoreHP=(restoreHP*20)/100;
				mHealth=mHealth+restoreHP;
				cout<<restoreHP<<" HP RESTORED"<<endl;
			}
			else if(mMisc[input-1]->getType()=="MHP")
			{
				restoreHP=(restoreHP*50)/100;
				mHealth=mHealth+restoreHP;
				cout<<restoreHP<<" HP RESTORED"<<endl;
			}
			else if(mMisc[input-1]->getType()=="BHP")
			{
				restoreHP=(restoreHP*90)/100;
				mHealth=mHealth+restoreHP;
				cout<<restoreHP<<" HP RESTORED"<<endl;
			}
			if(mHealth>mMaxHealth)
			{
				mHealth=mMaxHealth;
			}
			if(mMisc[input-1]->getAmmount() == 0)
			{
				mMisc.Remove(input-1);
			}
			cin.get();
			return"a";
		}

		if(mMisc[input-1]->getType()=="Portal")
		{
			mMisc[input-1]->decreaseCount();
			map->updateMap(map,mX,mY,'*');
			if(mMisc[input-1]->getAmmount() == 0)
			{
				mMisc.Remove(input-1);
			}
			cout<<"You have been transported back to the homebase"<<endl;
			cin.get();
			return"teleport";
		}
	}
return "a";
}

//allows player to equip WEAPONS
void Player::equip()
{
	int input=0;	
	if(mWeapons.numOfElements()==0 )
	{
		cout<<"YOUR WEAPONS INVENTORY IS EMPTY!"<<endl;
		cin.get();
		return;
	}
	weapons();
	cout<<"Which item to use: ";	
	cin>>input;
	if(input > mWeapons.numOfElements() || input<=0 )
	{
		cout<<"No such item in the inventory"<<endl;
		cin.get();
		return;
	}
	else
	{
		mWeapon.Name=mWeapons[input-1]->getName();
		mWeapon.DamageRange.mLow=mWeapons[input-1]->getLowDam();
		mWeapon.DamageRange.mHigh=mWeapons[input-1]->getHighDam();
		cout<<"You have equiped: "<<mWeapons[input-1]->getName()<<endl;
		cin.get();
	}
}

//when player steps on 'M' this function is triggered to
string Player::shop(Array<Weapons*> weapons,Array<Misc*>misc,Player* player)
{
	string input,sell,buy;
	bool exit=false;
	do
	{
		cout<<"***WELCOME TO THE SHOP***"<<endl;
		cout<<"would you like to 'buy' OR 'sell' items?...or 'exit'"<<endl;
		cout<<mName<<"'s choice: ";
		cin>>input;

		if(input == "sell")
		{
			cout<<"\nWhat would you liek to sell: 'weapons' OR 'misc' items?"<<endl;
			cout<<mName<<"'s choice: ";
			cin>>sell;
			player->sell(sell);
		}
		if(input == "buy")
		{
			cout<<"\nWhat would you liek to buy: 'weapons' OR 'misc' items?"<<endl;
			cout<<mName<<"'s choice: ";
			cin>>buy;
			player->buy(weapons,misc,buy);
		}
	}while(input!="exit");



	return "stay";
}

//allows player to sell items
string Player::sell(string sell)
{
	int choice=0;
	if(sell =="weapons")
	{
		do{
			weapons();
			cout<<endl;
			cout<<mName<<"'s Gold: "<<mGold<<endl;
			cout<<"Which weapon would you like to sell?";
			cin>>choice;
			if(choice == 0)
			{
			}
			else if(choice>mWeapons.numOfElements() || choice<0)
			{
				cout<<"INVALID CHOICE!!!"<<endl;
			}
			else
			{
				if(mWeapons[choice-1]->getName()==mWeapon.Name)
				{
					mWeapon.Name="Fists";
					mWeapon.DamageRange.mLow=1;
					mWeapon.DamageRange.mHigh=5;
				}
				mGold=mGold+mWeapons[choice-1]->getCost();
				mWeapons.Remove(choice-1);
			}
		}while(choice!=0);
	}

	if(sell =="misc")
	{
		do{
			misc();
			cout<<endl;
			cout<<mName<<"'s Gold: "<<mGold<<endl;
			cout<<"Which misc item would you like to sell?";
			cin>>choice;
			if(choice == 0)
			{
			}
			else if(choice>mMisc.numOfElements() || choice<=0)
			{
				cout<<"INVALID CHOICE!!!"<<endl;;
			}
			else
			{
				if(mMisc[choice-1]->getAmmount() > 0)
				{
					mGold=mGold+mMisc[choice-1]->getCost();
					mMisc[choice-1]->decreaseCount();
					if(mMisc[choice-1]->getAmmount() == 0)
					{
						mMisc.Remove(choice-1);
					}
				}
				
			}
		}while(choice!=0);
	}
	return "stay";
}

//allows player to buy items
string Player::buy(Array<Weapons*> weapons,Array<Misc*> misc,string buy)
{
	int choice=0;
	if(buy =="weapons")
	{
		do{
			for(int i=0;i<weapons.numOfElements();i++)
			{
				cout<<i+1<<") ";weapons[i]->printInfo();
			}
			cout<<endl;
			cout<<mName<<"'s Gold: "<<mGold<<endl;
			cout<<"Which weapon would you like to buy?";
			cin>>choice;
			if(choice == 0)
			{
			}
			else if(choice>weapons.numOfElements() || choice<=0)
			{
				cout<<"INVALID CHOICE!!!"<<endl;
			}
			else
			{
				if(weapons[choice-1]->getCost()<=mGold)
				{
					mWeapons.Push(weapons[choice-1]);
					mGold=mGold-weapons[choice-1]->getCost();
				}
				else
				{
					cout<<"\nYou dont have enough gold\n"<<endl;
				}
			}
		}while(choice!=0);
	}

	if(buy =="misc")
	{
		do{
			for(int i=0;i<misc.numOfElements();i++)
			{
				cout<<i+1<<") ";misc[i]->printInfo();
			}
			cout<<endl;
			cout<<mName<<"'s Gold: "<<mGold<<endl;
			cout<<"Which weapon would you like to buy?";
			cin>>choice;
			if(choice == 0)
			{
			}
			else if(choice>misc.numOfElements() || choice<=0)
			{
				cout<<"INVALID CHOICE!!!"<<endl;
			}
			else
			{
				if(misc[choice-1]->getCost()<=mGold)
				{
					check(misc[choice-1]);
					mGold=mGold-misc[choice-1]->getCost();
				}
				else
				{
					cout<<"\nYou dont have enough gold!!!\n"<<endl;
				}
			}
		}while(choice!=0);
	}
	return "exit";
}

//allows to accept quest and give rewards
string Player::getQuest(Map<char>* questMap)
{
	string choice;	
	
	if(mQuest==true && mFinQuest==true)
	{
		if(mQuestType=="HUNT")
		{
			cout<<"YOU REWARD IS: 1000 XP POINTS & 1000 GOLD COINS!"<<endl;
			mExp+=1000;
			mGold+=1000;
		}
		else
		{
			cout<<"YOU REWARD IS: 500 XP POINTS & 500 GOLD COINS!"<<endl;
			mExp+=500;
			mGold+=500;
		}
		mQuestType="none";
		mQuest=false;
		mFinQuest=false;
		return "finished";
	}
	else if(mQuest == true && mFinQuest ==false)
	{
		cout<<"YOU HAVENT FINISHED YOUR QUEST YET"<<endl;
		cin.get();
		return "stay";
	}
		do{
			cout<<"QUEST MASTER welcomes you traveler!"<<endl;
			cout<<"What type of quest would you like to take?"<<endl;
			cout<<"HUNT A MONSTER 'hunt' OR BRING AN ITEM BACK 'item'"<<endl;
			cout<<"Chocie: ";
			cin>>choice;

			if(choice == "hunt")
			{
				questMap->updateMap(questMap,questMap->Height()/2,questMap->Width()/2,'H');
				mQuest=true;
				mQuestType="HUNT";
				return "stay";
			}

			if(choice == "item")
			{
				questMap->updateMap(questMap,questMap->Height()/2,questMap->Width()/2,'I');
				mQuest=true;
				mQuestType="ITEM";
				return "stay";
			}

	}while(choice!= "hunt" ||choice!= "item"); 



	return "stay";
}

//allows to redistribute player lvl up points and get special weapon
string Player::rest()
{
	cout << "Resting...\nHealth was fully restored!" << endl;
	mHealth = mMaxHealth;
	if(mRePoints > 0)
	{
		int statChoice;
		char choice;
		cout<<"\nWould you like to redestribute your status points? y/n\nChoice: ";
		
		do{
		cin>>choice;		
		switch(choice)
		{
		case 'y':			
				do
				{
					cout<<"\nWhich stats would you like to improve:\n";
					cout<<"1)MaxHp    (Increases maximum HP points!)\n";
					cout<<"2)Strength (Grants extra damage done with your weapon)\n";
					cout<<"3)Accuracy (Increases your chance to strike an enemy,or dogde)\n";
					cout<<"4)Armour   (Reduces ammount of damage enemy does to you)\n";
					cout<<"5)Exit     (Leave this menu!)\n";
					cout<<"\n*Redistribution points left: "<<mRePoints<<"*"<<endl;
					cout<<"\n=== "<<mName<<"'s CURRENT STATS ===\n";
					cout<<"MaxHp    :"<<mMaxHealth<<endl;
					cout<<"Strength :"<<mStrength<<endl;
					cout<<"Accuracy :"<<mAccuracy<<endl;
					cout<<"Armour   :"<<mArmour<<endl;
					cout<<"\nChoice:";
					cin>>statChoice;
					switch(statChoice)
					{
					case 1:
						mMaxHealth += Random(3,6);
						mRePoints--;
						break;
					
					case 2:
						mStrength += Random(1,5);
						mRePoints--;
						break;

					case 3:
						mAccuracy += Random(1,3);
						mRePoints--;
						break;

					case 4:
						mArmour += Random(1,3);
						mRePoints--;
						break;
						
					case 5:
						break;

					default:
						cout<<"\nINVALID CHOICE!\n";
					}
				}while(mRePoints != 0 && statChoice != 5);
			break;

		case 'n':
			break;

		default:
			cout<<"Invalid Choice!";

		}
		}while(choice != 'y' && choice != 'n' && mRePoints != 0 && statChoice != 5);
		cout<<"\n=== "<<mName<<"'s CURRENT STATS ===\n";
		cout<<"MaxHp    :"<<mMaxHealth<<endl;
		cout<<"Strength :"<<mStrength<<endl;
		cout<<"Accuracy :"<<mAccuracy<<endl;
		cout<<"Armour   :"<<mArmour<<endl;
		mHealth=mMaxHealth;
	}

		char spChoice;
		if(mKills > 6)
		{
			do{
				cout<<"\nDo you want to exchange your KILL points for special weapon? y/n\nChoice:";
				cin>>spChoice;

				switch(spChoice)
				{
				case 'y':
					cout<<"\n!!!YOU GOT A BOMB!!!\n";
					mWeapon.Name="BOMB";
					mWeapon.DamageRange.mLow=Random(1,10)*mLevel;
					mWeapon.DamageRange.mHigh=Random(1,10)*mLevel;
					mKills=0;
					mRank="NOVICE";
					break;

				case 'n':
					break;

				default:
					cout<<"\nINVALID CHOICE!\n";
				}
			}while(spChoice != 'y' && spChoice != 'n' && mKills != 0);
		}

		return "stay";
}

//saves player with all the items in .txt file
void Player::save(ofstream& outFile)
{
	outFile<<"Name: "<<mName<<endl;
	outFile<<"Password: "<<mPassword<<endl;
	outFile<<"Rank: "<<mRank<<endl;
	outFile<<"Health: "<<mHealth<<endl;
	outFile<<"MaxHealth: "<<mMaxHealth<<endl;
	outFile<<"Exp: "<<mExp<<endl;
	outFile<<"ExpNxtLvl: "<<mExpNextLvl<<endl;
	outFile<<"Level: "<<mLevel<<endl;
	outFile<<"Strength: "<<mStrength<<endl;
	outFile<<"Accuracy: "<<mAccuracy<<endl;
	outFile<<"Armour: "<<mArmour<<endl;
	outFile<<"RePoints: "<<mRePoints<<endl;
	outFile<<"Kills: "<<mKills<<endl;
	outFile<<"Gold: "<<mGold<<endl;
	outFile<<"QuestType: "<<mQuestType<<endl;
	outFile<<"Quest: "<<mQuest<<endl;
	outFile<<"FinQuest: "<<mFinQuest<<endl;
	outFile<<"Weapon: "<<mWeapon.Name<<endl;
	outFile<<"LowDamage: "<<mWeapon.DamageRange.mLow<<endl;
	outFile<<"HighDamage: "<<mWeapon.DamageRange.mHigh<<endl;
	outFile<<"Location: "<<"Tavern"<<endl;
	outFile<<"xCord: "<<"2"<<endl;
	outFile<<"yCord: "<<"2"<<endl;
	//outFile<<"-------------------------------------"<<endl;
	outFile<<"NoOfWeapons: "<<mWeapons.numOfElements()<<endl;
	for(int i=0;i<mWeapons.numOfElements();i++)
		{
			outFile<<"Name: "<<mWeapons[i]->getName()<<endl;
			outFile<<"Cost: "<<mWeapons[i]->getCost()<<endl;
			outFile<<"Ldam: "<<mWeapons[i]->getLowDam()<<endl;
			outFile<<"Hdam: "<<mWeapons[i]->getHighDam()<<endl;
		}
	//outFile<<"-------------------------------------"<<endl;
	outFile<<"NoOfMisc: "<<mMisc.numOfElements()<<endl;
	for(int i=0;i<mMisc.numOfElements();i++)
		{
			outFile<<"Name: "<<mMisc[i]->getName()<<endl;
			outFile<<"Type: "<<mMisc[i]->getType()<<endl;
			outFile<<"Cost: "<<mMisc[i]->getCost()<<endl;
			outFile<<"Ammount: "<<mMisc[i]->getAmmount()<<endl;
		}
}

//loads all players stst and items from a .txt file
void Player::load(ifstream& inFile)
{
	string garbage;
	string itemName,typeName;
	int cost,lDam,hDam,ammount;
	int nWep,nMisc;

	inFile>>garbage>>mName;
	inFile>>garbage>>mPassword;
	inFile>>garbage>>mRank;
	inFile>>garbage>>mHealth;
	inFile>>garbage>>mMaxHealth;
	inFile>>garbage>>mExp;
	inFile>>garbage>>mExpNextLvl;
	inFile>>garbage>>mLevel;
	inFile>>garbage>>mStrength;
	inFile>>garbage>>mAccuracy;
	inFile>>garbage>>mArmour;
	inFile>>garbage>>mRePoints;
	inFile>>garbage>>mKills;
	inFile>>garbage>>mGold;
	inFile>>garbage>>mQuestType;
	inFile>>garbage>>mQuest;
	inFile>>garbage>>mFinQuest;
	inFile>>garbage>>mWeapon.Name;
	inFile>>garbage>>mWeapon.DamageRange.mLow;
	inFile>>garbage>>mWeapon.DamageRange.mHigh;
	inFile>>garbage>>mLocation;
	inFile>>garbage>>mX;
	inFile>>garbage>>mY;
	//inFile>>garbage>>garbage;
	inFile>>garbage>>nWep;
	for(int i=0;i<nWep;i++)
		{
			inFile>>garbage>>itemName;
			inFile>>garbage>>cost;
			inFile>>garbage>>lDam;
			inFile>>garbage>>hDam;
			mWeapons.Push(new Weapons(itemName,"Weapon",cost,lDam,hDam));
		}
	//inFile>>garbage>>garbage;
	inFile>>garbage>>nMisc;
	for(int i=0;i<nMisc;i++)
		{
			inFile>>garbage>>itemName;
			inFile>>garbage>>typeName;
			inFile>>garbage>>cost;
			inFile>>garbage>>ammount;
			mMisc.Push(new Misc(itemName,typeName,cost,ammount));
		}
}

void Player::displayHitPoints()
{
	cout << mName << "'s hitpoints = " << mHealth << endl;
}

//prints out help about the COMMANDS and MAP markers
void Player::printHelp()
{
	cout<<"\n============= HELPFUL COMMANDS =============\n"<<endl;
	cout<<"help       - shows help menu\n";
	cout<<"go         - allows player to change location\n";
	cout<<"inventory  - allows player to check his inventory\n";
	cout<<"status     - allows player to check his/her status\n";
	cout<<"exit       - exits the game!\n";
	cout<<"\n============================================\n"<<endl;
	cout<<"\n============== MAP MARKERS =================\n"<<endl;
	cout<<"'N'S'W'E'    - Possible exits on the map\n";
	cout<<"'P'          - Players position\n";
	cout<<"'M'          - Merchat(can trade here)\n";
	cout<<"'R'          - Resting location\n";
	cout<<"'Q'          - Quest Master\n";
	cout<<"'T'          - Treasure chest\n";
	cout<<"'H'          - Monster Hunt Quest\n";
	cout<<"'I'          - Item Quest\n";
	cout<<"'m'          - Monster location\n";
	cout<<"'*'          - Ground to walk around\n";
	cout<<"\n============================================\n"<<endl;
}

//prints out players satus and inventory
void Player::print()
{
	cout<<"\n==========STATUS==========\n";
	cout<<"Name     :"<<mName<<endl;
	cout<<"Rank     :"<<mRank<<endl;
	cout<<"HP       :"<<mHealth<<endl;
	cout<<"MaxHP    :"<<mMaxHealth<<endl;
	cout<<"Level    :"<<mLevel<<endl;
	cout<<"Exp      :"<<mExp<<endl;
	cout<<"NxtLvl   :"<<mExpNextLvl<<endl;
	cout<<"Weapon   :"<<mWeapon.Name<<" ("<<mWeapon.DamageRange.mLow<<" - "<<mWeapon.DamageRange.mHigh<<")"<<endl;
	cout<<"STR      :"<<mStrength<<endl;
	cout<<"ACC      :"<<mAccuracy<<endl;
	cout<<"Armour   :"<<mArmour<<endl;
	cout<<"RePoints :"<<mRePoints<<endl;
	cout<<"Kills    :"<<mKills<<endl;
	cout<<"Gold     :"<<mGold<<endl;
	cout<<"QType    :"<<mQuestType<<endl;
	cout<<"Quest    :"<<mQuest<<endl;
	cout<<"FinQuest :"<<mFinQuest<<endl;
	cout<<"Location :"<<mLocation<<endl;
	cout<<"X-coord  :"<<mX<<endl;
	cout<<"Y-coord  :"<<mY<<endl;
	inventory();
	cout<<"==========================\n";
}