/**********************************************************************/
/*PROGRAM:		Project 11 (list1.cpp)								  */
/*																	  */
/*AUTHOR:		Bryan Kline											  */
/*																	  */				
/*DATE:			11/26/15											  */
/*																	  */
/*REVISIONS:	1													  */
/*																	  */	
/*PURPOSE:		Implementation of array-based List class		      */
/*				functions, overloaded operators, and friend function. */
/*																	  */
/**********************************************************************/

#include <iostream>
#include <cstdlib>
#include "listA.h"

using namespace std;

//List class default constructor.
List:: List(int arraySize)
{
	//If the parameter passed in greater than zero then memory is allocated
	//of that size, otherwise data is set to NULL, and size is set to that
	//value and cursor and actual are set to -1.
	if(arraySize > 0)
	{
		data = new char[arraySize];
	
		size = arraySize;
	}
	else
	{
		data = NULL;

		size = 0;
	}
		
	cursor = -1;
	actual = -1;
}

//List class copy constructor.
List:: List(const List &list)
{
	int i;

	//Memory is allocated of the size of the List passed in and a counter
	//controlled loop goes through that List and copies its values into the
	//calling List and its data members are set to the values of the other List.
	data = new char[list.size];

	for(i = 0; i <= list.actual; i++)
	{
		data[i] = list.data[i];
	}

	size = list.size;
	actual = list.actual;
	cursor = list.cursor;
}

//List class destructor.
List:: ~List()
{
	//If data is not NULL then the memory it points to is freed and set to NULL,
	//and the other data members are set to default values.
	if(data != NULL)
	{
		delete data;
		data = NULL;
	}
	
	size = 0;
	cursor = -1;
	actual = -1;
}

//List class member function that moves the cursor to the beginning of the List
//and returns a bool corresponding to whether or not it was successful.
bool List:: gotoBeginning()
{
	//If the List isn't empty then cursor is set to zero and true is returned,
	//the beginning of the List, otherwise false is returned.
	if(empty() == false)
	{
		cursor = 0;	
		return true;
	}
		
	return false;
}

//List class member function moves the cursor to the end of the List and returns
//a bool corresponding to whether or not it was successful.
bool List:: gotoEnd()
{
	//If the List isn't empty then the cursor is set to actual and true is returned,
	//the end of the List, otherwise false is returned.
	if(empty() == false)
	{
		cursor = actual;	
		return true;
	}
		
	return false;
}

//List class member function that moves the cursor to the next element in the 
//List and returns a bool corresponding to whether or not it was successful.
bool List:: gotoNext()
{
	//If the List isn't empty then it checks that cursor isn't equal to actual,
	//that it's not at the end of the List, and increments cursor if it's not
	//and returns true, otherwise false is returned.
	if(empty() == false)
	{
		if(cursor != actual)
		{
			cursor++;	
		}

		return true;
	}
		
	return false;
}

//List class member function that moves the cursor to the previous element in
//the List and returns a bool corresponding to whether or not it was successful.
bool List:: gotoPrior()
{
	//If the List isn't empty then it checks that the cursor isn't equal to zero,
	//that it's not at the beginning of the List, and decrements cursor if it's
	//not and returns true, otherwise false is returned.
	if(empty() == false)
	{
		if(cursor != 0)
		{
			cursor--;
		}
	
		return true;
	}
		
	return false;
}

//List class member function that takes in a char and inserts it into the List
//at the position following the cursor and returns a bool corresponding to whether
//or not it was successful.
bool List:: insert(char letter)
{
	int i;
	
	//If the List is not full then letter is inserted after the cursor and
	//false is returned.
	if(full() == false)
	{
		//If the List is empty then cursor and actual are simply incremented and
		//letter is copied into the first index of the array.
		if(empty() == true)
		{
			cursor++;
			actual++;
			data[cursor] = letter;
		}
		//If the List isn't empty then a counter controlled loop goes from
		//actual back to cursor and moves the values ahead in the array,
		//cursor and actual are incremented and letter is copied into the
		//index that cursor is at.
		else
		{		
			for(i = actual; i > cursor; i--)
			{
				data[i + 1] = data[i];
			}
			cursor++;
			actual++;
			data[cursor] = letter;			
		}
		
		return true;
	}
	
	//False is returned if the List is full.
	return false;
}

//List class member function that takes in a letter by reference and removes
//an item from the List and returns a bool corresponding to whether or not it
//was successful.
bool List:: remove(char &letter)
{
	int i;

	//If the List isn't empty then the item at cursor is removed from the List
	//and true is returned. 
	if(empty() == false)
	{	
		//Letter is set to the char at cursor, and then if cursor is at the
		//end of the List then actual is decremented and cursor set to zero,
		//otherwise a counter controlled loop goes through the List and moves
		//everything towards the beginning and then actual is decremented, unless
		//cursor and actual are both zerp in which case they are set to -1.
		letter = data[cursor];
		if((cursor == actual)&&(cursor > 0))
		{
			actual--;
			cursor = 0;
		}			
		else
		{	
			if((actual == 0)&&(cursor == 0))
			{
				cursor = -1;
				actual = -1;
			}
			else
			{
				for(i = cursor; i < actual; i++)
				{
					data[i] = data[i + 1];
				}
				actual--;
			}
		}
		
	
		return true;
	}

	//If the List is empty then false is returned.
	return false;
}

//List class member function that and returns a bool corresponding to whether
//or not the List is empty.
bool List:: empty() const
{
	//If actual is at -1 or the size of the array that was passed into the
	//constructor is less than one then true is returned, otherwise false is
	//returned.
	if((actual == -1)||(size < 1))
	{
		return true;
	}

	return false;
}

//List class member function that and returns a bool corresponding to whether
//or not the List is full.
bool List:: full() const
{
	//If actual is equal to size minus one, if it's as the end of the List,
	//then true is returned, otherwise false is returned.
	if(actual == (size - 1))
	{
		return true;
	}
	
	return false;
}

//List class member function that clears the List and returns a bool
//corresponding to whether or not it was successful.
bool List:: clear()
{
	//If the List is empty then false is returned, otherwise cursor and
	//acutal are set to -1 and true is returned.
	if(empty() == true)
	{
		return false;
	}
	
	cursor = -1;
	actual = -1;

	return true;
}

//List class overloaded assignment operator that takes in a List and
//returns a list, both by reference.
List& List:: operator = (const List &list)
{
	int i;
		
	//If data is not NULL then the memory it points to is freed.
	if(data != NULL)
	{
		delete data;
	}

	//Memory of size from the List passed in as a parameter is allocated to
	//data and a counter controlled loop goes through one List and copies
	//in the chars from one to other and data members are set equal to those
	//of the List passed in as a parameter.
	data = new char[list.size];

	for(i = 0; i <= list.actual; i++)
	{
		data[i] = list.data[i];
	}

	size = list.size;
	actual = list.actual;
	cursor = list.cursor;

	//The dereferenced pointer to the calling List is dereferenced.
	return *this;
}

//Overloaded insertion operator that takes in an ostream object, a List object
//both by reference and returns an ostream object by reference and prints a
//List class object to the screen, putting brackets around the element at cursor.
ostream& operator << (ostream &out, const List &list)
{
	int i;

	//If the List is not empty then a counter controlled loop goes through
	//the list and prints each element to the screen, putting brackets
	//around the element at cursor.
	if(list.empty() == false)
	{
		for(i = 0; i <= list.actual; i++)
		{
			if(i == list.cursor)
			{
				cout << "[" << list.data[i] << "] ";
			}
			else
			{
				cout << list.data[i] << " ";
			}
		}
		cout << endl;
	}
	//If the List is empty then a new line is printed.
	else
	{
		cout << endl;
	}

	//The ostream object is returned.
	return out;
}
