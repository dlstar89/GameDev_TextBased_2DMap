//This 2D array class which is used to make a game map

#ifndef Map_H
#define Map_H

#include "DLinkedList.h"
#include "Random.h"
#include <fstream>
#include <iostream>
using namespace std;

template<class DataType>
class Map
{
public:
	Map(){};
	Map(int p_width, int p_height,string p_name,string p_type,string p_north,string p_south,string p_west,string p_east)
	{
		m_array=new DataType[p_width*p_height];
		m_width=p_width;
		m_height=p_height;
		m_name=p_name;
		m_type=p_type;
		m_north=p_north;
		m_south=p_south;
		m_west=p_west;
		m_east=p_east;
	}

	//~Map()
	//{
	//	if(m_array != 0)
	//	{
	//		delete[]m_array;
	//	}
	//	m_array=0;
	//}

	DataType& Get(int p_x,int p_y)
	{
		return m_array[p_y*m_width+p_x];
	}

	void Resize(int p_width,int p_height)
	{
		DataType* newarray = new DataType[p_width*p_height];

		if(newarray == 0)
		{
			return;
		}

		int x,y,t1,t2;

		int minx = (p_width < m_width ? p_width:m_width);
		int miny = (p_height < m_height ? p_height:m_height);

		for(y=0;y<miny;y++)
		{
			//Optimisation: precalculate t1 and t2 the standard algorithm to calculate the position in a 2D array
			//(y*width+x) since y*width doesnt change inside the inner loop it is a lot faster to calculate once outside the loop
			t1=y*p_width;
			t2=y*m_width;
			
			for(x=0;x<minx;x++)
			{
				//move data from old array to new array
				newarray[t1+x]=m_array[t2+x];
			}
		}

		if(m_array!=0)
			delete[]m_array;

		//set the old array to point at the newarray
		m_array=newarray;
		m_width=p_width;
		m_height=p_height;		
	}

	string getName()
	{
		return m_name;
	}
	int Size()
	{
		return m_width*m_height;
	}

	//Return the width
	int Width()
	{
		return m_width;
	}

	int Height()
	{
		return m_height;
	}

	void setWidth(int newWidth)
	{
		m_width=newWidth;
	}
	void setHeigth(int newHeight)
	{
		m_heigth=newHeight;
	}

	string getNorth()
	{
		return m_north;
	}
	string getSouth()
	{
		return m_south;
	}
	string getWest()
	{
		return m_west;
	}
	string getEast()
	{
		return m_east;
	}
	string getType()
	{
		return m_type;
	}

//sets all the markers on the map
void setMap(Map<char>* map,string north,string south,string west,string east,string type)
{
	for(int i=0;i<map->Width();i++)
	{
		for(int j=0;j<map->Height();j++)
		{
			map->Get(i,j)='*';
			if(type != "homebase")
			{
				int r=Random(1,10);
				if(r==5)
				{
					map->Get(i,j)='m';
				}
			}
		}
	}

	if(north != "na")
	map->Get(0,m_width/2)='N';

	if(south != "na")
	map->Get(m_height-1,m_width/2)='S';

	if(west != "na")
	map->Get(m_height/2,0)='W';

	if(east != "na")
	map->Get(m_width/2,m_height-1)='E';

	if(type=="homebase")
	{
		map->Get(0,0)='M';
		map->Get(0,m_width-1)='R';
		map->Get(0,m_width/2)='Q';
	}
}

//updates the map with specified markers on specifi location
void updateMap(Map<char>* map,int x,int y,char upd)
{
	map->Get(x,y)=upd;
}

void printMap(Map<char>* map)
{
	cout<<"\n***LOCATION: "<<m_name<<" ***"<<endl;
	if(m_type == "homebase")
	cout<<"TYPE: HOME BASE"<<endl;
	else
	cout<<"TYPE: DANGER ZONE"<<endl;
	cout<<"=============================="<<endl;
	if(m_north != "na")
	cout<<"NORTH EXIT: "<<m_north<<endl;
	if(m_south != "na")
	cout<<"SOUTH EXIT: "<<m_south<<endl;
	if(m_west!= "na")
	cout<<"WEST EXIT: "<<m_west<<endl;
	if(m_east != "na")
	cout<<"EAST EXIT: "<<m_east<<endl;
	cout<<"=============================="<<endl;
	for(int i=0;i<m_width;i++)
	{
		for(int j=0;j<m_height;j++)
		{
			cout<<" "<<map->Get(i,j);
		}
		cout<<"\n"<<endl;
	}
	cout<<"=============================="<<endl;

}

DLinkedList<Map*> load(ifstream& inFile)
{
	DLinkedList<Map*> maps;	
	
	while(inFile.good())
	{
		string garbage;
		inFile>>garbage>>m_name;
		inFile>>garbage>>m_type;
		inFile>>garbage>>m_width;
		inFile>>garbage>>m_height;
		inFile>>garbage>>m_north;
		inFile>>garbage>>m_south;
		inFile>>garbage>>m_west;
		inFile>>garbage>>m_east;
		Map* map=new Map(m_width,m_height,m_name,m_type,m_north,m_south,m_west,m_east);
		setMap(map,m_north,m_south,m_west,m_east,m_type);
		maps.Append(map);
	}
	
	return maps;
}

private:
	DataType* m_array;
	int m_width;
	int m_height;
	string m_name;
	string m_type;
	string m_north;
	string m_south;
	string m_west;
	string m_east;
};

#endif Map_H