#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

template<class DataType>
class Array
{
public:
	Array()
	{
		m_array = new DataType[5];
		size=5;
		num_elements=0;
		grow_size=5;
	}
	Array(int p_size)
	{
		m_array = new DataType[p_size];
		size=p_size;
		num_elements=0;
		grow_size=5;
	}

	/*~Array()
	{
		if(m_array != 0)
		{
			delete[]m_array;
		}
		m_array = 0;
	}*/

	void Resize()
	{
		int p_size=size+grow_size;
		DataType* newarray= new DataType[p_size];

		if(newarray == 0)
			return;

		int min;
		if(p_size<size)
			min=num_elements-1;//sets num_elements-1 for The POP() function to remove last element from the array
		else
			min=num_elements;

		for(int i=0;i<min;i++)
		{
			newarray[i]=m_array[i];
		}

		size=p_size;

		if(m_array != 0)
			delete[]m_array;

		m_array=newarray;
		newarray = 0;
	}

	void Insert(DataType p_item, int p_index)
	{
		//Copies everything over by one cell from right side until the specified position
		for(int i=num_elements;i>p_index;i--)
		{
			m_array[i]=m_array[i-1];
		}

		m_array[p_index]=p_item;
		num_elements++;
	}

	void InsertLocation(DataType p_item)
	{
		//devides the number of elements in half and checks from which side the element should be inserted
		int mid=num_elements/2;
		//cout<<"mid is: "<<mid<<endl;

		if(num_elements == 0)
		{
			//cout<<"Inserting on top..."<<endl;
			m_array[0]=p_item;
			num_elements++;
			return;
		}

		else if(p_item==m_array[mid])
		{
			//cout<<"Inserting in the middle..."<<endl;
			Insert(p_item,mid);
			return;
		}

		else if(p_item<=m_array[mid])
		{
			//cout<<"Searching from top..."<<endl;
			for(int i=0;i<mid+1;i++)
			{
				if(p_item<=m_array[i])
				{
					Insert(p_item,i);
					return;
				}
			}
		}

		else
		{
			//cout<<"Searching from bottom..."<<endl;
			for(int i=num_elements;i>0;i--)
			{
				if(p_item>=m_array[i-1])
				{
					Insert(p_item,i);
					return;
				}
			}
		}
	}

	void Push(DataType p_item)
	{
		if(num_elements == size)
		{
			//cout<<"RESIZING..."<<endl;
			Resize();
		}

		InsertLocation(p_item);		
	}
	
	void Pop()
	{
		if(num_elements==0)
		{
			cout<<"\nTHERE ARE NO ELEMENTS IN THE ARRAY TO REMOVE!..."<<endl;
			return;
		}
		else
		{
			int temp=grow_size;
			grow_size=-1;
			Resize();
			num_elements--;
			grow_size=temp;
		}
	}

	void Remove( int p_index )
    {
		if(num_elements == 0)
		{
			cout<<"\nTHERE ARE NO ELEMENTS IN THE ARRAY TO REMOVE!..."<<endl;
			return;
		}
		else
		{
			for(int index=p_index+1;index<num_elements;index++)
				{
					m_array[index - 1] = m_array[index];
				}
			num_elements--;
		}
    }

	int BinarySearch(DataType data)
	{
		int mid;
		int low=0;
		int high=num_elements;
		
		while(low<=high)
		{
			mid=(high+low)/2;

			if(m_array[mid]==data)
				{
					return mid;
				}
			else if(m_array[mid]<data)
				{
					low=mid+1;
				}
			else
				{
					high=mid-1;
				}
		}

		return-1;
	}

	void Clear(DataType p_item)
	{
		if(num_elements == 0)
		{
			cout<<"ARRAYS CONTAINS NO ELEMENTS..."<<endl;
			return;
		}
		else
		{
			for(int i=0;i<size;i++)
			{
				m_array[i]=p_item;
			}
			num_elements=0;
			cout<<"ARRAY IS CLEARED..."<<endl;
		}
	}	

	void Writeordered(ofstream& outFile)
	{
		for(int i=0;i<num_elements;i++)
		{
			outFile<<m_array[i];	

			if(i<num_elements-1)
			{
				outFile<<endl;
			}
			else
			{
				cout<<"Sorted file is saved..."<<endl;
				return;
			}
		}		
	}

	void Readunordered(ifstream& inFile)
	{
		DataType data;
		while(inFile.good())
			{
				inFile>>data;
				Push(data);				
			}
		cout<<"File succesfully loaded..."<<endl;
	}

	int Size()
		{
			return size;
		}

	int numOfElements()
		{
			return num_elements;
		}

	DataType& operator[](int p_index)
		{
			return m_array[p_index];
		}

	operator DataType*()
		{
			return m_array;
		}

	void Print()
	{
		for(int i=0;i<num_elements;i++)
		{
			cout<<m_array[i]<<endl;
		}
	}
	void Print2()
	{
		for(int i=0;i<size;i++)
		{
			cout<<m_array[i]<<endl;
		}
	}

private:
	int size;
	int grow_size;
	int num_elements;
	DataType* m_array;
};

#endif ARRAY_H