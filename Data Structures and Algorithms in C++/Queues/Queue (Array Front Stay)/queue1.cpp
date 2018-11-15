/**********************************************************************/
/*PROGRAM:		Project 10 (queue1.cpp)								  */
/*																	  */
/*AUTHOR:		Bryan Kline											  */
/*																	  */				
/*DATE:			11/18/15											  */
/*																	  */
/*REVISIONS:	1													  */
/*																	  */	
/*PURPOSE:		Implementation of array (front stay) based Queue class		  */
/*					functions, overloaded operators, and friend function. */
/*																	  */
/**********************************************************************/

#include <iostream>
#include <cstdlib>
#include "queue.h"

using namespace std;

//Queue class default contructor that takes in an int as its size or
//defaults it to 10 and makes an array of that size.
Queue:: Queue(int size)
{
	//If size is greater than zero then memory is allocated to data for
	//an int array of the size otherwise data is set to NULL.
	if(size > 0)
	{
		data = new int[size];
	}
	else
	{
		data = NULL;
	}

	//Data members set to default values.
	max = size;
	front = 0;
	rear = -1;
}


//Queue class copy contructor that takes in a Queue and copies in its values
//into the values created for the new Queue object.
Queue:: Queue(const Queue &queue)
{
	int i;	
	
	//If the max size of the Queue passed in is greater than zero then its
	//values are copied into the new Queue.
	if(queue.max > 0)
	{
		//Memory is allocated of size max from the queue passed in as a parameter
		//to data.
		data = new int[queue.max];

		//Data members are set to the value of the Queue passed in as a parameter.
		max = queue.max;
		front = queue.front;
		rear = queue.rear;

		//Counter controlled loop that goes through the int arrays and sets	
		//one equal to the other.
		for(i = 0; i <= queue.rear; i++ )
		{
			data[i] = queue.data[i];
		}
	}
}

//Queue class destructor.
Queue:: ~Queue()
{
	//If the into pointer data is not NULL then the memory it points to is freed,
	//and data members are set to default values;
	if(data != NULL)
	{
		delete[] data;

		data = NULL;
	}				
	max = size;
	front = 0;
	rear = -1;
}

//Queue class function that takes in an int as a parameter and adds it
//to the rear of the queue and returns a bool corresponding to whether 
//or not it was successful.
bool Queue:: enqueue(int number)
{
	//If a call to the class function full is false there is room to add
	//to the queue, rear is incremented, the int passed in is assigned to
	//the rear of the queue and true is returned.  Otherwise false is returned.
	if(full() == false)
	{
		rear++;
		data[rear] = number;

		return true;
	}
	
	return false;
}

//Queue class function that takes in an int by reference, removes
//an int from the queue and stores it in the int passed in as a 
//parameter and returns a bool corresponding to whether or not it
//was successful.
bool Queue:: dequeue(int &number)
{
	int i;	
	
	//If a call to the class function empty is false then there are
	//values that can be removed and the int passed in, number, is 
	//assigned the value of the int at the front of the queue. 
	if(empty() == false)
	{
		number = data[front];		

		//A counter controlled loop goes through the int array data
		//and moves all values towards the front and rear is incremented.
		for(i = 0; i <= rear; i++)
		{
			data[i] = data[i + 1];
		}	
		
		rear--;

		return true;	
	}

	//If the queue is empty then false is returned.
	return false;
}

//Queue class function that returns a bool corresponding to whether
//or not the queue is empty.
bool Queue:: empty() const
{
	//If rear is -1 then the queue holds not values and true is
	//returned, otherwise false is returned.
	if((data == NULL)||(rear == -1))
	{
		return true;
	}	
	
	return false;

}

//Queue class function that returns a bool corresponding to whether
//or not the queue is full.
bool Queue:: full() const
{
	//If rear is equal to max minus one then the queue is full and true
	//is returned, otherwise there is still room in the array and false
	//is returned.
	if(rear == (max - 1))
	{
		return true;
	}
	
	return false;
}

//Queue class function that clears the queue and returns a bool corresponding
//to whether or not it was successful.
bool Queue:: clear()
{
	//If empty is false then rear is set to -1 and true is returned.  Otherwise
	//it's already empty and false is returned.
	if(empty() == false)
	{
		rear = -1;

		return true;
	}
	
	return false;	
}

//Queue class overloaded assignment operator that returns a Queue by
//reference.
Queue& Queue:: operator = (const Queue& queue)
{
	int i;	
	
	//If the queues are not the same and data of the Queue passed in as a parameter
	//isn't pointing to NULL then the assignment operator can be used.
	if((*this != queue)&&(queue.data != NULL))
	{
		//If the int arrays are not the same size and the array pointer data of the
		//Queue passed in as a parameter is not NULL then the memory is points to is
		//freed, then new memory is allocated for data of size max of the Queue passed
		//in as a parameter. 
		if(max != queue.max)
		{
			if(data != NULL)
			{
				delete[] data;
			}

			data = new int[queue.max];
		}

		//Data members are set to the value of the Queue passed in as a parameter.
		max = queue.max;
		front = queue.front;
		rear = queue.rear;

		//Counter controlled loop that goes through the int arrays and sets	
		//one equal to the other.
		for(i = 0; i <= queue.rear; i++ )
		{
			data[i] = queue.data[i];
		}
	}

	//The Queue is returned with this dereferenced.
	return *this;
}

//Queue class overloaded equality operator that returns a bool corresponding
//to whether or not two Queues are equal.
bool Queue:: operator == (const Queue &queue) const
{
	int i; 

	//If statement that checks if data members front, rear, and max from either
	//Queue are not equal and if not then false is returned.
	if((front != queue.front)||(rear != queue.rear)||(max != queue.max))
	{
		return false;
	}

	//If both Queues' data pointers are both NULL then true is returned.
	if((data == NULL)&&(queue.data == NULL))
	{	
		return true;
	}

	//Counter controlled loop that goes through the int array of each Queue
	//and checks its elements to see if they are equal and if at any point
	//they're not false is returned.
	for(i = 0; i <= queue.rear; i++)
	{
		if(data[i] != queue.data[i])
		{
			return false;
		}
	}

	//If false hasn't yet been returned then true is returned.
	return true;
}

//Overloaded insertion operator that is a friend of the Queue class which takes in
//and returns an ostream object by reference and prints the ints in the Queue to
//the screen.
ostream& operator << (ostream &out, const Queue& queue)
{
	int i;	

	//If the Queue is not empty then a counter controlled loop goes through
	//the array data and prints out each element to the screen, putting 
	//square brackets around the front and rear of the queue.
	if(empty() == false)
	{
		for(i = 0; i <= queue.rear; i++)
		{
			if((i == 0)||(i == queue.rear))
			{
				out << "[" << queue.data[i] << "] ";
			}
			else
			{
				out << queue.data[i] << " ";
			}
		}
		out << endl;
	}
	//If the Queue is emptry then a new line is printed.
	else
	{
		out << endl;
	}

	//The ostream object is returned.
	return out;
}

