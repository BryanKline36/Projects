/**********************************************************************/
/*PROGRAM:		Project 10 (queue3.cpp)								  */
/*																	  */
/*AUTHOR:		Bryan Kline											  */
/*																	  */				
/*DATE:			11/18/15											  */
/*																	  */
/*REVISIONS:	1													  */
/*																	  */	
/*PURPOSE:		Implementation of Node based Queue class		  */
/*					functions, overloaded operators, and friend function. */
/*																	  */
/**********************************************************************/

#include <iostream>
#include <cstdlib>
#include "queueN.h"

using namespace std;

//Queue class default constructor that takes in an int which it ignores and set
//default values to the data members.
Queue:: Queue(int ignore)
{
	//Front and rear both set to NULL meaning the Queue is empty.
	front = NULL;
	rear = NULL;
}

//Queue class copy constructor which takes in another Queue object by reference
//and creates another with those same values.
Queue:: Queue(const Queue& queue)
{
	Node* temp1;
	Node* temp2;

	temp1 = queue.front;
	temp2 = NULL;	
	front = NULL;
	rear = NULL;
	
	//If the Queue passed in as a parameter is not empty then its
	//contents will be copied into the new Queue.
	if((queue.front != NULL)&&(queue.rear != NULL))
	{
		//If the Queue passed in as a parameter has a front Node whose next
		//is NULL then there is only one Node in the Queue and front has memory
		//allocated to it and the values from the Node copied in a rear is set to
		//front. 
		if((queue.front)->next == NULL)
		{
			front = new Node(temp1->data, NULL);
			rear = front;
		}
		//If there is more than one Node in the Queue then temp1 points to front, 
		//is moved through the Queue until its next is NULL and Nodes are created
		//and the values copied in.
		else
		{	
			while(temp1->next != NULL)	
			{
				//If it's the first Node created for this then front has
				//memory allocated to it and the value is copied in and temp2
				//is set to front.
				if(front == NULL)
				{
					front = new Node(temp1->data, NULL);
					temp1 = temp1->next;
					temp2 = front;
				}
				//If it's not the first Node, then temp2's next pointer has
				//memory allocated to it and the temporary Node pointers
				//are moved to next.
				else
				{
					temp2->next = new Node(temp1->data, NULL);
					temp2 = temp2->next;
					temp1 = temp1->next;
				}
			}
		
			//Memory is allocated to temp2's next pointer one final time
			//and rear is set to temp2.
			temp2->next = new Node(temp1->data, NULL);
			rear = temp2;
		}
	}	
}

//Queue class destructor.
Queue:: ~Queue()
{
	Node* temp1;
	Node* temp2;
	temp1 = front;
	temp2 = front;

	//If front and rear aren't NULL then the Queue is moved
	//through and the Nodes are deleted.	
	if((front != NULL)&&(rear != NULL))
	{
		while(temp1 != NULL)
		{
			temp1 = temp1->next;
			delete temp2;
			temp2 = temp1;
		}
	}
	
	//Front and rear are set to NULL.
	front = NULL;
	rear = NULL;
	
}

//Queue class function that takes in an int and enqueues it to the rear
//of the Queue and returns a bool corresponding to whether or not it was
//successful.
bool Queue:: enqueue(int number)
{

	Node* temp;
 	temp = front;

	//If the Queue is not full then it is moved through until the rear is 
	//reached and a new Node is created and linked up to the rear and rear
	//is moved.
	if(full() == false)
	{
		//If there are no Nodes in the Queue yet then front has memory allocated
		//to it and number and NULL are passed into the Node's copy constructor
		//and rear is set to front.
		if(empty() == true)
		{
			front = new Node(number, NULL);			
			rear = front;
		}
		//If the Queue is not empty then the Queue is move through until temp
		//gets to the rear and the next pointer of temp has memory allocated
		//to it, the values are passed into the Node's constructor and rear
		//is set to this Node.
		else
		{
			while(temp != rear)
			{
				temp = temp->next;
			}

			temp->next = new Node(number, NULL);	
			rear = temp->next; 
			temp = NULL;
		}	

		//True is returned to indicated that the value was enqueued
		//successfully.
		return true;
	}	

	//If the Queue is full then false is returned.
	return false;
}

//Queue class function that removes a Node from the front of the Queue
//and returns a bool corresponding to whether or not it is successful.
bool Queue:: dequeue(int& number)
{
	Node* temp;

	//If the Queue is not empty then the front is dequeued.
	if(empty() == false)
	{
		//If the front is the only Node in the Queue then
		//number is set to the Node's data value, front
		//is deleted and front and rear are set to NULL.
		if(front == rear)
		{
			number = front->data;
			delete front;
			front = NULL;
			rear = NULL;
		}
		//If there is more than one Node in the Queue then temp
		//points to the next Node in the Queue, front is deleted
		//and front is set to temp.
		else
		{
			temp = front->next;
			number = front->data;
			delete front;
			front = temp;
			temp = NULL;
		}
	
		//True is returned to indicated the value was dequeued successfully.
		return true;
	}

	//If the Queue is empty then nothing can be dequeued and false
	//is returned.
	return false;
}

//Queue class function that returns a bool corresponding to whether or noth
//the Queue is empty.
bool Queue:: empty() const
{
	//If both the front and the rear are NULL then true is returned.
	if((front == NULL)&&(rear == NULL))
	{
		return true;
	}
		
	//False is returned otherwise.
	return false;
}

//Queue class function that returns a bool corresponding to whether or not
//the Queue is full.
bool Queue:: full() const
{
	//As a Queue is never full false is simply returned.
	return false;
}

//Queue class function that clears the Queue and returns a bool corresponding to 
//whether or not it was successful.
bool Queue:: clear()
{
	Node* temp1;
	Node* temp2;
	temp1 = front;
	temp2 = front;

	//If front and rear are NULL then the Queue is already empty and
	//false is returned.
	if((front == NULL)&&(rear == NULL))
	{
		return false;
	}

	//If the Queue isn't empty then the Queue is moved through and the
	//Nodes are deleted.
	while(temp1 != NULL)
	{
		temp1 = temp1->next;
		delete temp2;
		temp2 = temp1;
	}
	
	//Front and rear are set to NULL and true is returned.
	front = NULL;
	rear = NULL;

	return true;
}

//Queue class overloaded assignment operator that takes in and returns
//a Queue by reference.
Queue& Queue:: operator = (const Queue& queue)
{
	Node* temp1;
	Node* temp2;

	temp1 = queue.front;
	temp2 = NULL;
	
	//If the two Queues that have the overloaded assignment operator
	//called on them aren't the same then the calling Queue is cleared
	//and then parameter Queue has its values copied into Node created
	//for the calling Queue.
	if((*this == queue) == false)
	{
		//The Nodes of the calling Queue are cleared.
		this->clear();

		//If the Queue passed in as a parameter is not empty then its
		//contents will be copied into the calling Queue.
		if(queue.front != NULL)
		{
			//If the Queue passed in as a parameter has a front Node whose next
			//is NULL then there is only one Node in the Queue and front has memory
			//allocated to it and the values from the Node copied in a rear is set to
			//front. 
			if((queue.front)->next == NULL)
			{
				front = new Node(temp1->data, NULL);
				rear = front;
			}
			//If there is more than one Node in the Queue then temp1 points to front, 
			//is moved through the Queue until its next is NULL and Nodes are created
			//and the values copied in.
			else
			{	
				while(temp1->next != NULL)	
				{
					//If it's the first Node created for this then front has
					//memory allocated to it and the value is copied in and temp2
					//is set to front.
					if(front == NULL)
					{
						front = new Node(temp1->data, NULL);
						temp1 = temp1->next;
						temp2 = front;
					}
					//If it's not the first Node, then temp2's next pointer has
					//memory allocated to it and the temporary Node pointers
					//are moved to next.
					else
					{
						temp2->next = new Node(temp1->data, NULL);
						temp2 = temp2->next;
						temp1 = temp1->next;
					}
				}

				//Memory is allocated to temp2's next pointer one final time
				//and rear is set to temp2.
				temp2->next = new Node(temp1->data, NULL);
				rear = temp2;
			}
		}
	}	

	//The calling Queue is returned.
	return *this;
}

//Queue class overloaded equality operator that takes in a Queue by reference
//and returns a bool corresponding to whether or not two Queues are equal.
bool Queue:: operator == (const Queue& queue) const
{
	Node* temp1;
	Node* temp2;
	bool match;

	temp1 = front;
	temp2 = queue.front;

	//The bool match is set to false.
	match = false;
	
	//If both Queues are empty then true is returned.
	if((front == NULL)&&(rear == NULL)&&((queue.front == NULL)&&(queue.rear == NULL)))
	{
		return true;
	}

	//If both Queues' fronts are not NULL then the Queues are moved through and the
	//values in their data member data are compared.
	if((front != NULL)&&(queue.front != NULL))
	{
		while((temp1->next != NULL)&&(temp2->next != NULL))
		{
			//If values in each Queues' Node are equal then match is set to
			//true.
			if(temp1->data == temp2->data)
			{
				match = true;
			}
			//If at any point the values in either Node are not equal then
			//false is returned.
			else 
			{
				return false;
			}
				
			//The temp pointers are moved.
			temp1 = temp1->next;
			temp2 = temp2->next;
		}

		//If either Queue is not at its rear then false is returned.
		if((temp1->next != NULL)||(temp2->next != NULL))
		{
			return false;
		}
	}

	//The bool match is returned.
	return match;
}

//Node class default constructor that takes in an int and a Node pointer
//and sets it's data members to those values passed in as parameters.
Node:: Node(int number, Node* nodePtr)
{
	data = number;
	next = nodePtr;
}

//Overloaded insertion operator that is a friend of the Queue class that
//takes in an ostream object and a Queue object both by reference and returns
//an ostream object by reference and prints the Queue Nodes to the screen. 
ostream& operator << (ostream& out, const Queue& queue)
{
	Node* temp;

	temp = queue.front;
	
	//If the Queue is not empty then the Queue is moved through and the
	//Nodes are printed to the screen.
	if(queue.empty() == false)
	{
		while(temp != NULL)
		{
			//If temp is pointing to the front or rear then brackets are printed
			//out around data.			
			if(temp == (queue.front)||(temp == queue.rear))
			{
				cout << "[" << temp->data << "] ";
				temp = temp->next;
			}
			//If temp is not pointing to the front then data is printed.	
			else
			{
				cout << temp->data << " ";
				temp = temp->next;
			}
		}
		cout << endl;
	}
	//If the Queue is empty then a new line is printed.
	else
	{
		cout << endl;
	}

	//The ostream object is returned.
	return out;
}
