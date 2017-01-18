//This is a Doubly Linked List implementation

#ifndef DLinkedList_H
#define DLinkedList_H
#include"Array.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

// forward declarations of all the classes in this file
template<class DataType> class DListNode;
template<class DataType> class DLinkedList;
template<class DataType> class DListIterator;

//-----------------------------------------------------
//Name:			DListNode
//Description:	A node class 
//Arguments:	m_data - type of data that the node will contain
//				m_next - a pointer to the next node
//				m_previous - a pointer to the previous node
//-----------------------------------------------------
template<class DataType>
class DListNode
{
public:
	DataType m_data;
	DListNode<DataType>* m_next;
	DListNode<DataType>* m_previous;

	DListNode()
	{
		m_next = 0;
		m_previous=0;
	}
};

//-----------------------------------------------------
//Name:			DLinkedList
//Description:	A list that containes some data
//Arguments:	m_head - is the start of the list
//				m_tail - is the end of the list
//				m_count - keeps track on the ammount of elements in the list
//Return Val:	None
//-----------------------------------------------------
template<class DataType>
class DLinkedList
{
public:
	DLinkedList()
	{
		m_head = 0;
		m_tail = 0; 
		m_count = 0;
	}

	//~DLinkedList()
	//{
	//	//temporary node pointer
	//	DListNode<DataType>* itr = m_head;
	//	DListNode<DataType>* next;

	//	while(itr != 0)
	//	{
	//		//save the pointer to the next node
	//		next = itr->m_next;
	//		//delete the current element
	//		delete itr;
	//		//move itr on to the next element
	//		itr = next;
	//	}
	//}

//-----------------------------------------------------
//Name:			DeleteAll
//Description:	Deletes all the data from the list
//Arguments:	p_iterator - iterates through the list and deletes the data
//Return Val:	None
//-----------------------------------------------------
	void DeleteAll(DListIterator<DataType>& p_iterator)
	{
		if(m_count==0)
		{
			cout<<"THE LIST IS EMPTY!"<<endl;
			return;
		}
		
		DListNode<DataType>* itr = m_head;
		DListNode<DataType>* next;

		while(itr != 0)
		{
			//save the pointer to the next node
			next = itr->m_next;
			//delete the current element
			delete itr;
			//move itr on to the next element
			itr = next;
			m_count--;
		}

		if(m_count==0)
		{
			m_head=m_tail = new DListNode<DataType>;
		}

		cout<<"\nALL RECORDS WHERE REMOVED!"<<endl;
	}

//-----------------------------------------------------
//Name:			Append
//Description:	Puts data at the end of the list
//Arguments:	p_data - data that is going to be appended
//Return Val:	None
//-----------------------------------------------------
	void Append(DataType p_data)
	{
		//check if the list is empty
		if(m_count==0)
		{
			m_head=m_tail = new DListNode<DataType>;
			m_head->m_data=p_data;
			m_head->m_next = 0;
            m_head->m_previous = 0;
		}
		else
		{
			DListNode<DataType>* newnode = new DListNode<DataType>;//create new node
			newnode->m_data=p_data;//set data to be equal to whatever was passed in the constructor
			newnode->m_next=0;//sent next poiner point to 0 since its the end of the list

			newnode->m_previous=m_tail;//newnode->m_previous should point to the tail
			m_tail->m_next=newnode;//tail->m_next should point to the newnode
			m_tail=m_tail->m_next;//update the tail node,so taht newnode is the tail now
		}
		
		m_count++;
	}

//-----------------------------------------------------
//Name:			Prepend
//Description:	Puts data at the start of the list
//Arguments:	p_data - data to be prepended
//Return Val:	None
//-----------------------------------------------------
	void Prepend(DataType p_data)
	{
		//create the new node
		DListNode<DataType>* newnode = new DListNode<DataType>;

		newnode->m_data = p_data;
		newnode->m_previous=0;//since its the start of the list previous should point to 0

		newnode->m_next=m_head;
		m_head->m_previous=newnode;
		m_head=m_head->m_previous;//update so that newnode is the head now

		m_count++;
	}

//-----------------------------------------------------
//Name:			Remove Head
//Description:	Removes element at the start of the list
//Arguments:	None
//Return Val:	None
//-----------------------------------------------------
	void RemoveHead()
	{
		DListNode<DataType>* node = 0;
		if(m_head != 0)
		{
			//make node point to the next node
			node = m_head->m_next;
			
			//Then delete the head node
			delete m_head;
			m_head = node;

			//If there was one thing in the list and we deleted
			//it we now have nothing in the list
			if(m_head == 0)
				m_tail = 0;
			else
				m_head->m_previous=0;
		}
		m_count--;
	}

//-----------------------------------------------------
//Name:			RemoveTail
//Description:	Removes element at the end of the list
//Arguments:	None
//Return Val:	None
//-----------------------------------------------------
	void RemoveTail()
	{
		 DListNode<DataType>* node = 0;

        if( m_tail != 0 )
        {
            // make node point to the next node.
            node = m_tail->m_previous;

            // then delete the head, and make the pointer
            // point to node.
            delete m_tail;
            m_tail = node;

            // if the tail is null then we just deleted the only node in the list so we  set the head to 0.
            // if not, set the next pointer to 0.
            if( m_tail == 0 )
                m_head = 0;
            else
                m_tail->m_next = 0;

            m_count--;
        }
	}

//-----------------------------------------------------
//Name:			GetIterator
//Description:	returns the class at whihc the iterator should look at
//Arguments:	None
//Return Val:	Iterator DataType
//-----------------------------------------------------
	DListIterator<DataType> GetIterator()
	{
		return DListIterator<DataType>(this, m_head);
	}

//-----------------------------------------------------
//Name:			Insert
//Description:	Inserts the data at specific position by cheking at which position it should be inserted
//				if position is less than middle then the data will be inserted from the HEADS side,vice versa for the positon reather than middle
//Arguments:	p_iterator - iterator of specific class that iterates through its list
//				p_data - data to be inserted
//				p_position - an index where the data will be inserted in the list
//Return Val:	None
//-----------------------------------------------------
	void Insert(DListIterator<DataType>& p_iterator, DataType p_data,int p_position)
	{
		int i=0;
		int mid=m_count/2;
		DListNode<DataType>* newnode = new DListNode<DataType>;
		DListNode<DataType>* temp = new DListNode<DataType>;
		newnode->m_data=p_data;
		temp=m_head;
		p_iterator.m_list->GetIterator();
		p_iterator.Start();

		//if the iterator doesn't belong to the current list do nothing
		if(p_iterator.m_list != this)
			return;

//-------------------------------------------------------------------------------------------------------------------
		if(m_count !=0 )
		{
			if(p_position>=m_count)
			{
				Append(p_data);
				return;
			}
//-------------------------------------------------------------------------------------------------------------------
			else if(p_position<=0)
			{
				Prepend(p_data);
				return;
			}
//-------------------------------------------------------------------------------------------------------------------
			else if(p_position<mid+1)//inserts the data from the head side of the list
			{
				for(p_iterator.Start();p_iterator.Valid();p_iterator.Forth())//iterates from head to the tail
				{
					if(i==p_position)
					{
						while(temp->m_next != p_iterator.m_node)//goes next till finds node equal to p_iterators node
							temp=temp->m_next;

						newnode->m_next=p_iterator.m_node;
						p_iterator.m_node->m_previous=newnode;
						temp->m_next=newnode;
						newnode->m_previous=temp;
						//cout<<"INSERTED From Left!!!"<<endl;
						m_count++;
						return;
					}
					i++;
				}
			}
//---------------------------------------------------------------------------------------------------------------------
			else if(p_position>mid-1)//inserts the data from the tail side of the list
			{
				i=m_count;
				temp=m_tail;
				for(p_iterator.End();p_iterator.Valid();p_iterator.Previous())//iterates from tail to the head
				{
					if(i==p_position)
					{
						while(temp->m_previous != p_iterator.m_node)
							temp=temp->m_previous;

						newnode->m_previous=p_iterator.m_node;
						p_iterator.m_node->m_next=newnode;
						temp->m_previous=newnode;
						newnode->m_next=temp;						
						//cout<<"INSERTED from Right!!!"<<endl;
						m_count++;
						return;
					}
					i--;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------------------
		else
		{
			Append(p_data);
			return;
		}
	}

//-----------------------------------------------------
//Name:			Remove
//Description:	Removes element at a specific position
//Arguments:	p_iterator - an iterator that iterates through the list from lef or right
//				p_position - removes element at a specified position			 
//Return Val:	None
//-----------------------------------------------------
	void Remove(DListIterator<DataType>& p_iterator,int p_position)
	{
		if(m_count == 0)
		{
			cout<<"LIST IS EMPTY!"<<endl;
			return;
		}

		int midle=m_count/2;
		DListNode<DataType>* node = m_head;
		
		//check that we are using the right iterator 
		if(p_iterator.m_list != this)
			return;


		if(p_position<=0)
		{
			RemoveHead();
			return;
		}
//-------------------------------------------------------------------------------------------------------------------
		else if(p_position+1>=m_count)
		{
			RemoveTail();
			return;
		}
//-------------------------------------------------------------------------------------------------------------------
		else
		{
			if(p_position <midle+1)
			{
				p_iterator.Start();//restart iterator to the start of the list
				//cout<<"DELETING FROM LEFT"<<endl;
				for(int i=0;i<p_position;i++)
				{
					p_iterator.Forth();
				}

				//scan forward in the list looking for the node prior to delete node			
				while(node->m_next != p_iterator.m_node)
				{
					node = node->m_next;
				}
				p_iterator.Forth();

				delete node->m_next;

				node->m_next = p_iterator.m_node;
				p_iterator.m_node->m_previous=node;
				m_count--;
				return;
			}
//-------------------------------------------------------------------------------------------------------------------
			else if(p_position>midle-1)
			{
				node=m_tail;
				p_iterator.End();
				//cout<<"DELETING FROM RIGHT"<<endl;
				for(int i=m_count-1;i>p_position;i--)
				{
					p_iterator.Previous();
				}
				//scan backward in the list looking for the node prior to delete node
			
				while(node->m_previous != p_iterator.m_node)
				{
					node = node->m_previous;
				}
				p_iterator.Previous();

				delete node->m_previous;

				p_iterator.m_node->m_next=node;
				node->m_previous=p_iterator.m_node;
				m_count--;
				return;
			}
		}
	}

		DListNode<DataType>* m_head;
		DListNode<DataType>* m_tail;
		int m_count;
};

//-----------------------------------------------------
//Name:			DListIterator
//Description:	An Iteratot class taht allowes to iterate through dounly linked lsit 
//-----------------------------------------------------
template<class DataType>
class DListIterator
{
public:
	DListIterator(DLinkedList<DataType>* p_list = 0,DListNode<DataType>* p_node = 0)
	{
		m_list = p_list;
		m_node = p_node;
	}

	void Start()
	{
		if(m_list != 0)
			m_node = m_list->m_head;
	}

	void End()
	{
		if(m_list != 0)
			m_node = m_list->m_tail;
	}

	void Forth()
	{
		if(m_node != 0)
			m_node = m_node->m_next;
	}

	void Previous()
	{
		if(m_node != 0)
			m_node = m_node->m_previous;
	}

	DataType& Item()
	{
		return m_node->m_data;
	}

	bool Valid()
	{
		return (m_node != 0);
	}

	DListNode<DataType>* m_node;
	DLinkedList<DataType>* m_list;
};

#endif