/**********************************************************************/
/*PROGRAM:		Project 10 (queue2.cpp)								  */
/*																	  */
/*AUTHOR:		Bryan Kline											  */
/*																	  */				
/*DATE:			11/18/15											  */
/*																	  */
/*REVISIONS:	1													  */
/*																	  */	
/*PURPOSE:		Implementation of array (front wrap) based Queue class		  */
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
	front = -1;
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
		for(i = 0; i <= (max - 1); i++)
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
	max = 0;
	front = -1;
	rear = -1;
}

//Queue class function that takes in an int and enqueues it to the rear
//of the Queue and returns a bool corresponding to whether or not it was
//successful. 
bool Queue:: enqueue(int number)
{
	//If the Queue isn't full then rear is moved back and the value passed
	//in is added to the array at that index and true is returned.
	if(full() == false)
	{
		//If the Queue is empty then front is incremented from -1 to 0;
		if(empty() == true)
		{
			front++;
		}
		
		//Rear is determined by adding one and modding it with max.
		rear = ((rear + 1) % max);
		data[rear] = number;

		return true;
	}
	
	//If the Queue is full then false is returned.
	return false;
}

//Queue class function that takes in an int by reference, removes an int from
//the Queue and stores it in the int passed in as a parameter and returns a bool
//corresponding to whether or not it was successful.
bool Queue:: dequeue(int &number)
{
	//If the Queue isn't empty then number is set to the int that
	//will be dequeued, front is moved toward the end of the array
	//and true is returned.
	if(empty() == false)
	{
		//The int number is set to the value at index front of data.
		number = data[front];

		//If front is equal to rear then there is only one element in the array 
		//and front and rear are both set to -1.
		if(front == rear)
		{
			front = -1;
			rear = -1;
		}
		//If there are more than one value in the array then front is set to
		//front plus one modded by max to wrap it around to the begging of the
		//array.
		else
		{
			front = ((front + 1) % max);		
		}

		//True is returned.
		return true;	
	}

	//If the Queue is empty then false is returned.
	return false;
}

//Queue class function that returns a bool corresponding to whether
//or not the Queue is empty.
bool Queue:: empty() const
{
	//If front and rear are -1 or if data is NULL then the queue holds no
	//values and true is returned, otherwise false is returned.
	if(((front == -1)&&(rear == -1))||(data == NULL))
	{
		return true;
	}	
	
	return false;

}

//Queue class function that returns a bool corresponding to whether
//or not the Queue is full.
bool Queue:: full() const
{

	//If front is less than rear then the only time the array can be full is
	//if rear minus front is equal to the last index, in which case true is
	//returned, otherwise false is returned.
	if(front < rear)
	{
		if((rear - front) == (max - 1))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	//If front is greater than rear then when the difference between front and
	//rear is one then the array is full, in which case true is returned,
	//otherwise false is returned.
	if(front > rear)
	{
		if((front - rear) == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//If front and rear are equal and they are not -1 and the size of the 
	//array is one then true is returned as the array of one is full.
	if(((front == rear)&&(max == 1))&&((front != -1)&&(rear != -1)))
	{
		return true;
	}

	//For all other cases false is returned.
	return false;
}

//Queue class function that clears the queue and returns a bool corresponding
//to whether or not it was successful.
bool Queue:: clear()
{
	//If empty is false then front and rear are set to -1 and true is returned.
	//Otherwise it's already empty and false is returned.
	if(empty() == false)	
	{
		front = -1;
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
	if(((*this == queue) == false)&&(queue.data != NULL))	
	{
		//If the int arrays are not the same size and the array pointer data of the
		//Queue passed in as a parameter is not NULL then the memory is points to is
		//freed, then new memory is allocated for data of size max of the Queue passed
		//in as a parameter.
		if(max != queue.max)	
		{
			if(queue.data != NULL)
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
		for(i = 0; i <= (max - 1); i++ )
		{
			data[i] = queue.data[i];
		}
	}

	//The Queue is returned with this dereferenced.
	return *this;
}

//Queue class overloaded equality operator that takes in a Queue by
//reference and returns a bool corresponding to whether or not the
//two Queues are equal.
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
	for(i = front; i != rear; i = ((i + 1) % max))
	{
		if(data[i] != queue.data[i])
		{
			return false;
		}		
	}

	return true;
}

//Overloaded insertion operator that's a friend of the Queue class which takes
//in an ostream object and a Queue class object, both by reference and returns 
//an ostream object by reference and goes through the Queue and prints its 
//contents to the screen.
ostream& operator << (ostream &out, const Queue& queue)
{
	int i;	

	//If the Queue isn't empty the a counter controlled loop goes through
	//the Queue from front to rear printing out each int to the screen,
	//putting brackets around the front.
	if(queue.empty() == false)
	{	
		//Counter controlled loop that starts at front and goes through the
		//array until it gets to rear, incrementing by adding one and modding
		//the counter by max.
		for(i = queue.front; i != queue.rear; i = ((i + 1) % queue.max))
		{
			if(i == queue.front)
			{
				out << "[" << queue.data[i] << "] ";
			}
			else
			{
				out << queue.data[i] << " ";
			}
		}
		//Rear is printed out, also with brackets around it.
		out << "[" << queue.data[i] << "] " << endl;
	}
	//If the Queue is empty then a new line is printed.
	else
	{
		out << endl;
	}

	//The ostream object is returned.
	return out;
}

