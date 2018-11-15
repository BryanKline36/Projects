/**********************************************************************/
/*PROGRAM:		Project 11 (list2.cpp)								  */
/*																	  */
/*AUTHOR:		Bryan Kline											  */
/*																	  */				
/*DATE:			11/26/15											  */
/*																	  */
/*REVISIONS:	1													  */
/*																	  */	
/*PURPOSE:		Implementation of Node-based List class functions,    */
/*					overloaded operators, and friend function.        */
/*																	  */
/**********************************************************************/

#include <iostream>
#include <cstdlib>
#include "listN.h"

using namespace std;

//List class default constructor that takes in a char which is ignores.
List:: List(int ignore)
{
	//Both head and cursor are set to NULL as a default.
	head = NULL;
	cursor = NULL;
}	

//List class copy constructor that takes in a List by reference.
List:: List(const List &list)
{
	head = NULL;
	cursor = NULL;

	//If the List passed is not empty then an event controlled loop goes
	//through the List passed in while temp1 isn't NULL and if the head
	//of the calling List is NULL then head has memory allocated to it for
	//a Node, temporary Node pointers are moved and the cursor is set to
	//head if cursor is at head in the List passed in, otherwise temp2 has
	//a Node created for it and it's linked up to the previous Node and
	//temporary pointers are moved until temp1 hits NULL.
	if(list.empty() == false)	
	{
		Node* temp1;
		Node* temp2;

		temp1 = list.head;
		temp2 = NULL;

		while(temp1 != NULL)
		{
			if(head == NULL)
			{
				head = new Node(temp1->data, temp2);
				temp1 = temp1->next;
				temp2 = head;
				if(list.head == list.cursor)
				{
					cursor = head;
				}
			}
			else
			{
				temp2->next = new Node(temp1->data, NULL);	
				if(temp1 == list.cursor)
				{
					cursor = temp2->next;
				}
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
		}	
		temp1 = NULL;
		temp2 = NULL;
	}
}

//List class destructor.
List:: ~List()
{
	//If the List is not empty then an event controlled loop goes through
	//the List and while a temporary Node pointer is not NULL Nodes are
	//deleted and data members are set to NULL.
	if(empty() == false)
	{	
		Node* temp;
	
		temp = head;

		while(temp != NULL)
		{
			delete temp;
			temp = temp->next;
		}
		
		temp = NULL;
		head = NULL;
		cursor = NULL;
	}
}

//List class member function that moves cursor to the beginning of the List and
//returns a bool corresponding to whether or not it was successful. 
bool List:: gotoBeginning()
{
	//If the List is not empty then cursor is set to head and true is returned,
	//otherwise false is returned.
	if(empty() == false)
	{
		cursor = head;
	
		return true;	
	}
	
	return false;
}

//List class member function that moves the cursor to the end of the List and
//returns a bool corresponding to whether or not it was successful.
bool List:: gotoEnd()
{
	//If the List is not empty and cursor is not at the end already then an event
	//controlled loop moves cursor until its next data member is NULL at which
	//point it's at the end of the List and true is returned, otherwise false
	//is returned.
	if((empty() == false)&&(cursor->next != NULL))
	{
		while(cursor->next != NULL)
		{
			cursor = cursor->next;
		}

		return true;	
	}
	
	return false;
}

//List class member function that moves the cursor to the next Node in the
//List and returns a bool corresponding to whether or not it was successful.
bool List:: gotoNext()
{
	//If the List is not empty and cursor is not already at the end of the
	//List then cursor is moved down the List one and true is returned,
	//otherwise false is returned. 
	if((empty() == false)&&(cursor->next != NULL))
	{
		cursor = cursor->next;

		return true;
	}
	
	return false;
}

//List class member function that moves the cursor back towards the beginning of
//the list and returns a bool corresponding to whether or not it was successful. 
bool List:: gotoPrior()
{
	//If the List isn't empty and if there isn't only one Node in the List then
	//a temporary Node pointer is set to head then with an event controlled loop
	//moved through the List until just before cursor and then cursor is set
	//equal to temp and true is returned, otherwise false is returned.
	if((empty() == false)&&(head->next != NULL)&&(cursor != head))
	{
		Node* temp;
		
		temp = head;

		while(temp->next != cursor)
		{
			temp = temp->next;	
		}

		cursor = temp;
		temp = NULL;

		return true;
	}
	
	return false;
}

//List class member function that takes in a char and inserts it into the
//List after the cursor and returns a bool corresponding to whether or not 
//it was successful.
bool List:: insert(char letter)
{
	//If the List is not full then, if the List is empty, head has a Node
	//created for it and cursor is set to head, otherwise temp has a Node
	//created for it, its next pointer is set to the next of cursor, cursor's
	//next pointer is set to temp which links the Nodes and then cursor 
	//is set to temp and true is returned.  If the List is empty then 
	//false is returned.
	if(full() == false)
	{
		if(empty() == true)
		{
			head = new Node(letter, NULL);
			cursor = head;
		}	
		else
		{
			Node* temp = new Node(letter, cursor->next);
			cursor->next = temp;
			cursor = temp;
			temp = NULL;
		}		

		return true;
	}

	return false;
}


//List class member function that takes in a char by reference, removes an
//item from the List, sets the char equal to that item, and returns a bool
//corresponding to whether or not it was successful.
bool List:: remove(char &letter)
{
	//If the List isn't empty then letter is set to the char at the cursor
	//Node, and then if there's only one Node in the List it's simply cleared
	//otherwise a temporary pointer points to the next Node, the one at cursor
	//is deleted and the previous Node, accessed with gotoPrior, is liked to
	//the next one cursor is moved.  If the List isn't empty then true is 
	//returned, otherwise false is returned.
	if(empty() == false)
	{
		letter = cursor->data;
		
		if(head->next == NULL)
		{
			clear();
		}
		else 
		{
			if(cursor == head)
			{
				head = head->next;
				delete cursor;
				cursor = head;
			}
			else
			{
				Node* temp;

				temp = cursor;
				gotoPrior();
				cursor->next = temp->next;	
				delete temp;
				temp = NULL;
				if(cursor->next == NULL)
				{
					gotoBeginning();
				}
				else
				{
					cursor = cursor->next;	
				}
			}
		}
	
		return true;
	}

	return false;
}

//List class member function that returns a bool corresponding to whether or not the
//List is empty.
bool List:: empty() const
{
	//If head and cursor are both NULL then the list is empty and true is returned,
	//otherwise false is returned.
	if((head == NULL)&&(cursor == NULL))
	{
		return true;
	}

	return false;
}

//List class member function that returns a bool corresponding to whether or not the
//List is full.
bool List:: full() const
{
	return false;
}

//List class member function that clears the List and returns a bool corresponding
//to whether or not it was successful.
bool List:: clear()
{
	//If the List is not empty then an event controlled loop goes through
	//the List and while a temporary Node pointer is not NULL Nodes are
	//deleted and data members are set to NULL and true is returned, otherwise
	//false is returned.
	if(empty() == false)
	{
		Node* temp;
	
		temp = head;

		while(temp != NULL)
		{
			delete temp;
			temp = temp->next;
		}

		temp = NULL;
		head = NULL;
		cursor = NULL;

		return true;
	}

	return false;
}

//List class overloaded assignment operator that takes in a List and returns
//a List, both by reference, and assigns one the values of the other.
List& List:: operator = (const List &list)
{

	//If the two Lists are not the same List then the calling List calls
	//the clear function to free all memory and then if the List passed
	//in as a parameter is not empty then its items are copied into the
	//calling List.
	if(this != &list)
	{
		this->clear();
		
		if(list.empty() == false)	
		{
			Node* temp1;
			Node* temp2;

			temp1 = list.head;
			temp2 = NULL;

			//Event controlled loop that goes through the List passed in while
			//temp1 isn't NULL and if the head of the calling List is NULL then
			//head has memory allocated to it for a Node, temporary Node pointers
			//are moved and the cursor is set to head if cursor is at head in the  
			//List passed in, otherwise temp2 has a Node created for it and it's
			//linked up to the previous Node and temporary pointers are moved
			//until temp1 hits NULL.
			while(temp1 != NULL)
			{
				if(head == NULL)
				{
					head = new Node(temp1->data, temp2);
					temp1 = temp1->next;
					temp2 = head;
					if(list.head == list.cursor)
					{
						cursor = head;
					}
				}
				else
				{
					temp2->next = new Node(temp1->data, NULL);	
					if(temp1 == list.cursor)
					{
						cursor = temp2->next;
					}
					temp1 = temp1->next;
					temp2 = temp2->next;
				}
			}
			temp1 = NULL;
			temp2 = NULL;	
		}
	}

	//The calling List is returned.
	return *this;
}

//Node class default constructor that takes in a char and a Node pointer.
Node:: Node(char letter, Node* nodePtr)
{
	//The Node's data members are set to the values of the parameters	
	//passed into the constructor.
	data = letter;
	next = nodePtr;
}

//List class friend function that takes in an ostream object and List both
//by reference and returns an ostream object by reference and prints the 
//List to the screen.
ostream& operator << (ostream &out, const List &list)
{
	//If the List isn't empty then while a temporary isn't NULL, the List is moved
	//through and the chars in the List are printed to the screen, if the temporary
	//pointer is at the cursor then brackets are printed around the char.
	if(list.empty() == false)
	{
		Node* temp;
		temp = list.head;

		while(temp != NULL)
		{
			if(temp == list.cursor)
			{
				cout << "[" << temp->data << "] ";
				temp = temp->next;
			}
			else
			{	
				cout << temp->data << " ";
				temp = temp->next;
			}
		}
		cout << endl;
		temp = NULL;
	}
	else
	{
		cout << endl;
	}

	return out;
}
