//2D GAME

#include "Player.h"
#include "Monster.h"
#include "Object.h"
#include "Random.h"
#include "Map.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

static string previousLoc;
static bool login=false;

//FUNCTION PROTOTYPES
Array<Weapons*> loadWeapons(string weaponData);
Array<Misc*> loadMisc(string miscData);
DLinkedList<Monster*> loadMonster(string monsterData);
DLinkedList<Map<char>*> loadMaps(string mapFile);
Player* loadPlayer(string userName,Player* player);
void saveGame(Player* player);
void setXY(Map<char>* map,string previousloc,Player* player);
Map<char>* printMap(int x,int y,Map<char>*map,string direction,DListIterator<Map<char>*> itrmap,DListIterator<Monster*> itr,Array<Weapons*> weapons,Array<Misc*> misc,Player* player);
Map<char>* changeMap(DListIterator<Map<char>*>,Player* player);
bool goORnot(int x,int y,Map<char>* map);
string changeLocation(int x,int y,Map<char>*map,DListIterator<Map<char>*> itrmap,DListIterator<Monster*> itr,Array<Weapons*> weapons,Array<Misc*> misc,Player* player);
string fight(DListIterator<Monster*> itr,Player* player);
string openChest(Array<Weapons*> weapons,Array<Misc*> misc,Player* player);
string quest(Player* player,DListIterator<Map<char>*> maps);


void main()
{
	bool firstLog=false;
	cin.exceptions(ios::failbit);
	string input,token,words[10];
	Map<char>* currentmap;
	Player* player=new Player;

	DLinkedList<Monster*> monsters;
	DListIterator<Monster*> itr;
	itr=monsters.GetIterator();
	monsters=loadMonster("dataToLoad//monsters.txt");

	DLinkedList<Map<char>*>maps;
	DListIterator<Map<char>*> itrmap;
	itrmap=maps.GetIterator();
	maps=loadMaps("dataToLoad//rooms.txt");

	Array<Weapons*> weapons;
	weapons=loadWeapons("dataToLoad//weapons.txt");

	Array<Misc*> misc;
	misc=loadMisc("dataToLoad//misc.txt");
//----------------------------------------------------START OF LOGIN LOOP--------------------------------------------
//LOG IN
	do{
		cout<<"Type 'exit' to exit the game"<<endl;
		cout<<"To create a new account type 'register'"<<endl;
		cout<<"To login type in 'login'"<<endl;;
		cout<<"INPUT: ";
		cin>>input;
		if(input=="exit")
		{
			break;
		}
		if(input=="register")
		{
			player->createPlayer();
			saveGame(player);
			firstLog=true;
			login=true;
			break;
		}
		if(input=="login")
		{
			cout<<"Enter users name: ";
			cin>>input;
			player=loadPlayer("saveData//"+input+".txt",player);
		}
	}while(login!=true);
//-----------------------------------------------------------------------------------------------------------------------
//if player has a quest it will generate the marker randomply on the map again
	if(login == true)
	{
		bool quest=false;
		if(player->getQuestType() == "HUNT")
		{
			do{
				itrmap.Start();
				int rand=Random(0,itrmap.m_list->m_count-1);
				for(int i=0;i<rand;i++)
				{
					itrmap.Forth();
				}
				if(itrmap.Item()->getType() != "homebase")
				{
					itrmap.Item()->updateMap(itrmap.Item(),itrmap.Item()->Height()/2,itrmap.Item()->Width()/2,'H');
					quest=true;
				}
			}while(quest!=true);
		}

		if(player->getQuestType() == "ITEM")
		{
			do{
				itrmap.Start();
				int rand=Random(0,itrmap.m_list->m_count-1);
				for(int i=0;i<rand;i++)
				{
					itrmap.Forth();
				}
				if(itrmap.Item()->getType() != "homebase")
				{
					itrmap.Item()->updateMap(itrmap.Item(),itrmap.Item()->Height()/2,itrmap.Item()->Width()/2,'I');
					quest=true;
				}
			}while(quest!=true);
		}
	}
//---------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------END OF LOGIN LOOP--------------------------------------------
//----------------------------------------------------START OF THE GAME LOOP--------------------------------------------
	if(login==true)
	{
		currentmap=player->backToHomeBase(itrmap);
		currentmap->updateMap(currentmap,player->mX,player->mY,'P');
		do
		{
			try{

				if(firstLog==true)
				{
					player->rest();
					firstLog=false;
				}

			int p=0;
			bool moved=false;
			getline(cin,input);
			stringstream split(input);

			while(split>>token)
			{
				words[p]=token;
				p++;
			}

			system("cls");
			if(words[0]=="go")
			{
				if(words[1]=="north")
				{
					player->mX--;
					if(goORnot(player->mX,player->mY,currentmap)==true)
					{
						currentmap=printMap(player->mX,player->mY,currentmap,words[1],itrmap,itr,weapons,misc,player);
					}
					else
					{
						player->mX++;
						currentmap=printMap(player->mX,player->mY,currentmap,words[1],itrmap,itr,weapons,misc,player);
					}
				}
				else if(words[1]=="south")
				{
					player->mX++;
					if(goORnot(player->mX,player->mY,currentmap)==true)
					{
						currentmap=printMap(player->mX,player->mY,currentmap,words[1],itrmap,itr,weapons,misc,player);
					}
					else
					{
						player->mX--;
						currentmap=printMap(player->mX,player->mY,currentmap,words[1],itrmap,itr,weapons,misc,player);
					}
				}
				else if(words[1]=="west")
				{	
					player->mY--;
					if(goORnot(player->mX,player->mY,currentmap)==true)
					{
						currentmap=printMap(player->mX,player->mY,currentmap,words[1],itrmap,itr,weapons,misc,player);
					}
					else
					{
						player->mY++;
						currentmap=printMap(player->mX,player->mY,currentmap,words[1],itrmap,itr,weapons,misc,player);
					}
				}
				else if(words[1]=="east")
				{
					player->mY++;
					if(goORnot(player->mX,player->mY,currentmap)==true)
					{
						currentmap=printMap(player->mX,player->mY,currentmap,words[1],itrmap,itr,weapons,misc,player);
					}
					else
					{
						player->mY--;
						currentmap=printMap(player->mX,player->mY,currentmap,words[1],itrmap,itr,weapons,misc,player);
					}
				}
				else
				{
					cout<<"GO WHERE?!"<<endl;
					printMap(player->mX,player->mY,currentmap,words[1],itrmap,itr,weapons,misc,player);
				}
				moved=true;
			}
			if(words[0]=="use")
			{
				if(player->use(currentmap)=="teleport")
					{
						currentmap=player->backToHomeBase(itrmap);
						currentmap->updateMap(currentmap,player->mX,player->mY,'P');
					}
				words[0]="";
			}
			if(words[0]=="equip")
			{
				player->equip();
				words[0]="";
			}
			if(words[0]=="help")
			{
				player->printHelp();
				words[0]="";
			}
			if(words[0]=="status")
			{
				player->print();
				words[0]="";
			}
			else if(moved==false)
			{
				printMap(player->mX,player->mY,currentmap,words[1],itrmap,itr,weapons,misc,player);
			}
			//words[1]="";
			cout<<player->getName()<<"'s input: ";
		}catch(ios_base::failure &)//catches the unexpected entry
		{
			cin.clear();//clears input buffer
			system("cls");
			cout<<"BAD INPUT!!! TRY AGAIN!!!"<<endl;
			getchar();
		}
		}while(words[0]!="exit");
		saveGame(player);
	}
}
//----------------------------------------------------END OF THE GAME LOOP--------------------------------------------


//--------------------------------------------FUNCTIONS---------------------------------------------------------
Player* loadPlayer(string playerData,Player* player)
{
	bool login2=false;
	string password;
	Player* p1 = new Player;	
	ifstream inFile(playerData);
	if(inFile)
		{
			p1->load(inFile);
			cout<<"Enter Password: ";
			cin>>password;
			if(p1->getPassword() == password)
			{
				login2=true;
			}
			inFile.close();
		}
	else
	{
		system("cls");
		cout<<"Such user doesnt exists!!!"<<endl;
		return false;
	}

	if(login2==false)
	{
		system("cls");
		cout<<"Login Unsuccesfull..."<<endl;
	}
	else
	{
		cout<<"Login Successfull..."<<endl;
		player=p1;
		login=true;
		return player;
	}

	return false;
}
void saveGame(Player* player)
{
	ofstream outFile("saveData//"+player->getName()+".txt");
	if(outFile)
	{
		player->save(outFile);
		outFile.close();
	}
}
Array<Weapons*> loadWeapons(string weaponData)
{
	Weapons* weapon=new Weapons;
	Array<Weapons*> weapons;
	ifstream inFile(weaponData);
	if(inFile)
		{
			weapons=weapon->loadWeapons(inFile);
			inFile.close();
		}
	return weapons;
}

Array<Misc*> loadMisc(string miscData)
{
	Misc* misc=new Misc;
	Array<Misc*> miscelaneous;
	ifstream inFile(miscData);
	if(inFile)
		{
			miscelaneous=misc->loadMisc(inFile);
			inFile.close();
		}
	return miscelaneous;
}

DLinkedList<Monster*> loadMonster(string monsterData)
{
	Monster* monster=new Monster;
	DLinkedList<Monster*> monsters;
	ifstream inFile(monsterData);
	if(inFile)
		{
			monsters=monster->load(inFile);
			inFile.close();
		}
	return monsters;
}


DLinkedList<Map<char>*> loadMaps(string mapFile)
{
	DLinkedList<Map<char>*> maps;
	Map<char> map;
	ifstream inFile(mapFile);
	if(inFile)
		{
			maps=map.load(inFile);
			inFile.close();
		}

	return maps;
}

bool goORnot(int x,int y,Map<char>* map)
{
	int width=map->Width();
	width-=1;
	int height=map->Height();
	height-=1;
	if(x<0 || x>width || y<0 || y>height)
	{
		cout<<"CANT GO THERE!!!"<<endl;
		return false;
	}
	return true;
}

//if map has to be changed this funtion is called
Map<char>* changeMap(DListIterator<Map<char>*> itrmap,Player* player)
{
	for(itrmap.Start();itrmap.Valid();itrmap.Forth())
	{
		if(itrmap.Item()->getName() == player->getLocation())
		{
			setXY(itrmap.Item(),previousLoc,player);
			return itrmap.Item();
		}
	}
	itrmap.Start();
	return itrmap.Item();
}

//when player moves arround on the map the map is geting updated and checks if the location has to be changed
string changeLocation(int x,int y,Map<char>*map,DListIterator<Map<char>*> itrmap,DListIterator<Monster*> itr,Array<Weapons*> weapons,Array<Misc*> misc,Player* player)
{
	if(map->Get(x,y)=='N' || map->Get(x,y)=='S' || map->Get(x,y)=='W' || map->Get(x,y)=='E')
	{
		previousLoc=player->getLocation();
		if(map->Get(x,y)=='N')
		{
			map->updateMap(map,x,y-=1,'*');//left
			map->updateMap(map,x+=1,y+=1,'*');//down
			map->updateMap(map,x-=1,y+=1,'*');//right
			player->setLocation(map->getNorth());
			cout<<"GOING TO: "<<map->getNorth()<<endl;
		}
		if(map->Get(x,y)=='S')
		{
			map->updateMap(map,x,y-=1,'*');//left
			map->updateMap(map,x,y,'*');//up
			map->updateMap(map,x-=1,y+=1,'*');//right
			player->setLocation(map->getSouth());
			cout<<"GOING TO: "<<map->getSouth()<<endl;
		}
		if(map->Get(x,y)=='W')
		{
			map->updateMap(map,x+=1,y,'*');//down
			map->updateMap(map,x-=2,y,'*');//up
			map->updateMap(map,x+=1,y+=1,'*');//right
			player->setLocation(map->getWest());
			cout<<"GOING TO: "<<map->getWest()<<endl;
		}
		if(map->Get(x,y)=='E')
		{
			map->updateMap(map,x+=1,y,'*');//down
			map->updateMap(map,x-=2,y,'*');//up
			map->updateMap(map,x,y-=1,'*');//left
			player->setLocation(map->getEast());
			cout<<"GOING TO: "<<map->getEast()<<endl;
		}
		return "changeMap";
	}
//------------------------------------------------------------------
	if(map->Get(x,y)=='m')
	{
		system("cls");
		return fight(itr,player);
	}
//--------------------------------------------------------------------
	if(map->Get(x,y)=='T')
	{
		system("cls");
		return openChest(weapons,misc,player);
	}
//--------------------------------------------------------------------
	if(map->Get(x,y)=='R')
	{
		system("cls");
		return player->rest();
	}
//--------------------------------------------------------------------
	if(map->Get(x,y)=='M')
	{
		system("cls");
		return player->shop(weapons,misc,player);
	}
//--------------------------------------------------------------------
	if(map->Get(x,y)=='Q')
	{
		system("cls");
		return quest(player,itrmap);
	}
//--------------------------------------------------------------------
	if(map->Get(x,y)=='H')
	{
		system("cls");
		return fight(itr,player);
	}
//--------------------------------------------------------------------
	if(map->Get(x,y)=='I')
	{
		system("cls");
		player->setQuestUpdate(true);
		cout<<"QUEST WAS UPDATED!"<<endl;
		return "keepGoing";
	}
	return "keepGoing";
}

//prints and updates the map
Map<char>* printMap(int x,int y,Map<char>*map,string direction,DListIterator<Map<char>*> itrmap,DListIterator<Monster*> itr,Array<Weapons*> weapons,Array<Misc*> misc,Player* player)
{
	string outcome="";
	if(direction == "north")
	{
		outcome=changeLocation(x,y,map,itrmap,itr,weapons,misc,player);
		if(outcome == "keepGoing")
		{
			map->updateMap(map,x,y,'P');
			x++;
			map->updateMap(map,x,y,'*');
		}
		if (outcome == "treasure")
		{
			player->mX++;
			map->updateMap(map,x,y,'T');
		}
		if(outcome=="changeMap")
		{
			map=changeMap(itrmap,player);
			map->updateMap(map,player->mX,player->mY,'P');
		}
		if(outcome=="stay")
		{
			player->mX++;
		}
		if(outcome=="return")
		{
			map->updateMap(map,player->mX,player->mY,'*');
			map=player->backToHomeBase(itrmap);
			player->mExp=player->mExp-player->mExp/2;
			player->restoreHP();
		}
	}

	if(direction == "south")
	{
		outcome=changeLocation(x,y,map,itrmap,itr,weapons,misc,player);
		if(outcome == "keepGoing")
		{
			map->updateMap(map,x,y,'P');
			x--;
			map->updateMap(map,x,y,'*');
		}
		if (outcome == "treasure")
		{
			player->mX--;
			map->updateMap(map,x,y,'T');
		}
		if(outcome=="changeMap")
		{
			map=changeMap(itrmap,player);
			map->updateMap(map,player->mX,player->mY,'P');
		}
		if(outcome=="stay")
		{
			player->mX--;
		}
		if(outcome=="return")
		{
			player->mX--;
			map->updateMap(map,player->mX,player->mY,'*');
			map=player->backToHomeBase(itrmap);
			player->mExp=player->mExp-player->mExp/2;
			player->restoreHP();
		}
	}

	if(direction == "west")
	{
		outcome=changeLocation(x,y,map,itrmap,itr,weapons,misc,player);
		if(outcome == "keepGoing")
		{
			map->updateMap(map,x,y,'P');
			y++;
			map->updateMap(map,x,y,'*');
		}
		if (outcome == "treasure")
		{
			player->mY++;
			map->updateMap(map,x,y,'T');
		}
		if(outcome=="changeMap")
		{
			map=changeMap(itrmap,player);
			map->updateMap(map,player->mX,player->mY,'P');
		}
		if(outcome=="stay")
		{
			player->mY++;
		}
		if(outcome=="return")
		{
			player->mY++;
			map->updateMap(map,player->mX,player->mY,'*');
			map=player->backToHomeBase(itrmap);
			player->mExp=player->mExp-player->mExp/2;
			player->restoreHP();
		}
	}

	if(direction == "east")
	{
		outcome=changeLocation(x,y,map,itrmap,itr,weapons,misc,player);
		if(outcome == "keepGoing")
		{
			map->updateMap(map,x,y,'P');
			y--;
			map->updateMap(map,x,y,'*');
		}
		if (outcome == "treasure")
		{
			player->mY--;
			map->updateMap(map,x,y,'T');
		}
		if(outcome=="changeMap")
		{
			map=changeMap(itrmap,player);
			map->updateMap(map,player->mX,player->mY,'P');
		}
		if(outcome=="stay")
		{
			player->mY--;
		}
		if(outcome=="return")
		{
			player->mY--;
			map->updateMap(map,player->mX,player->mY,'*');
			map=player->backToHomeBase(itrmap);
			player->mExp=player->mExp-player->mExp/2;
			player->restoreHP();
		}
	}

	map->printMap(map);
	return map;
}

//starts the fight
string fight(DListIterator<Monster*> itr,Player* player)
{
	string outcome="";
	Monster* monster = new Monster;
	bool boss=false;
	if(player->getQuestUpdate() == true)
	{
		do{
			itr.Start();
			int rand=Random(0,itr.m_list->m_count-1);
			for(int i=0;i<rand;i++)
			{
				itr.Forth();
			}
			if(itr.Item()->mType != "Minion")
			{
				monster=itr.Item();
				boss=true;
			}
		}while(boss!=true);
	}
	else
	{
		do{
			itr.Start();
			int rand=Random(0,itr.m_list->m_count-1);
			for(int i=0;i<rand;i++)
			{
				itr.Forth();
			}
			if(itr.Item()->mType != "Boss")
			{
				monster=itr.Item();
				boss=true;
			}
		}while(boss!=true);
	}
	
	monster->MaxHitPoints=monster->MaxHitPoints*Random(1,player->mLevel);
	monster->Armour=monster->Armour*Random(1,player->mLevel);
	monster->Accuracy=monster->Accuracy*Random(1,player->mLevel);
	monster->ExpReward=monster->ExpReward*Random(1,player->mLevel);
	monster->Strength=monster->Strength*Random(1,player->mLevel);
	monster->mWeapon.DamageRange.mLow=monster->mWeapon.DamageRange.mLow*Random(1,player->mLevel);
	monster->mWeapon.DamageRange.mHigh=monster->mWeapon.DamageRange.mHigh*Random(1,player->mLevel);
	monster->HitPoints=monster->MaxHitPoints;

	bool playerDead = false;
	cout<<"\nYou where spotted by "<<monster->getName()<<endl;
	monster->printStats();
	while(true)
	{
		player->displayHitPoints();
		monster->displayHitPoints();

		bool runAway = player->attack(*monster);

		if(runAway == true)
		{
			outcome="stay";
			break;
		}

		if(monster->isDead())
		{
			player->victory(monster->getXPReward()*Random(1,player->mLevel));
			int itemDrop=Random(1,2);
			if(itemDrop == 1)
			{
				cout<<monster->getName()<<" has dropped a treasure "<<endl;
				outcome="treasure";
				cin.get();
			}
			else
			{
				cout<<"You got: "<<monster->getXPReward()/2<<" gold coins"<<endl;
				player->goldReward(monster->getXPReward()/2);
				outcome="keepGoing";
				cin.get();
			}
			if(player->getQuestUpdate() == true)
			{
				cout<<"QUEST WAS UPDATED!"<<endl;
				player->setQuestUpdate(true);
			}

			player->levelUp();
			break;			
		}

		monster->attack(*player);
		
		if(player->isDead())
		{
			cout<<"You were delivered back to the tavern being unconciuous..."<<endl;
			outcome="return";
			playerDead = true;
			break;
		}
	}
	return outcome;
}

//sets player x and y coords when the map is changed
void setXY(Map<char>* map,string previousloc,Player* player)
{
	if(map->getNorth() == previousLoc)
	{
		for(int i=0;i<map->Width();i++)
		{
			if(map->Get(0,i)=='N')
			{
				player->setX(1);
				player->setY(i);
				return;
			}
		}
	}

	if(map->getSouth() == previousLoc)
	{
		for(int i=0;i<map->Width();i++)
		{
			if(map->Get(map->Height()-1,i)=='S')
			{
				player->setX(map->Height()-2);
				player->setY(i);
				return;
			}
		}
	}

	if(map->getWest() == previousLoc)
	{
		for(int i=0;i<map->Height();i++)
		{
			if(map->Get(i,0)=='W')
			{
				player->setX(i);
				player->setY(1);
				return;
			}
		}
	}

	if(map->getEast() == previousLoc)
	{
		for(int i=0;i<map->Height();i++)
		{
			if(map->Get(i,map->Width()-1)=='E')
			{
				player->setX(i);
				player->setY(map->Width()-2);
				return;
			}
		}
	}
}

//when player steps on 'T' openChest command is triggered
string openChest(Array<Weapons*> weapons,Array<Misc*> misc,Player* player)
{
	string input;
	int rand=Random(1,2);
	int smash=Random(1,2);
	cout<<"You have encountered a TREASURE chest!!!"<<endl;
	cout<<"Do you want to 'open' or try to 'smash' it?"<<endl;

	do{
		cout<<player->getName()<<"'s input: ";
		cin>>input;
		if(input == "open")
		{
			if(player->open("Key") == true)
			{
				if(rand==1)
				{
					int randWeapon=Random(0,weapons.numOfElements()-1);
					player->mWeapons.Push(weapons[randWeapon]);
					cout<<"You found: "<<weapons[randWeapon]->getName()<<endl;
				}

				if(rand==2)
				{
					int randMisc=Random(0,misc.numOfElements()-1);
					player->check(misc[randMisc]);
					cout<<"You found: "<<misc[randMisc]->getName()<<endl;
				}
				cin.get();
				return "keepGoing";
			}
			else
			{
				cout<<"You have to use a key to open a chest!!!"<<endl;
			}
		}

		if(input == "smash")
		{
			if(smash==1)
			{

				if(rand==1)
					{
						int randWeapon=Random(0,weapons.numOfElements()-1);
						player->mWeapons.Push(weapons[randWeapon]);
						cout<<"You found: "<<weapons[randWeapon]->getName()<<endl;
					}

					if(rand==2)
					{
						int randMisc=Random(0,misc.numOfElements()-1);
						player->check(misc[randMisc]);
						cout<<"You found: "<<misc[randMisc]->getName()<<endl;
					}
					cin.get();
					return "keepGoing";
			}
			else
			{
				cout<<"Unfortunately u have hti the chest too hard and the item inside of it got broken..."<<endl;
				cin.get();
				return "keepGoing";
			}

		}


	}while(input!= "open" || input!="smash");

	return "keepGoing";
}

//when player steps on 'Q' player will be able to accept quests or get reward when its finished
string quest(Player* player,DListIterator<Map<char>*> maps)
{
	bool accepted=false;
	if(player->getQuestUpdate() == true)
	{
		if(player->getQuest(maps.Item())=="finished")
		{
			cout<<"QUEST WAS FINSIHED!"<<endl;
			player->levelUp();
			cin.get();
			return "stay";
		}
		else
		{
			return "stay";
		}
	}
	else
	{
		char choice;
		cout<<"Are you ready to accept a quest... y/n"<<endl;
		cout<<"Choice: ";
		cin>>choice;

		if(choice == 'y')
		{
			do{
				maps.Start();
				int rand=Random(0,maps.m_list->m_count-1);
				for(int i=0;i<rand;i++)
				{
					maps.Forth();
				}
				if(maps.Item()->getType() != "homebase")
				{
					accepted=true;
				}
			}while(accepted!=true);
			return player->getQuest(maps.Item());
		}
		if(choice == 'n')
		{
			cin.get();
			return "stay";
		}
	}
	return "stay";
}