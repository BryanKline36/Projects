#include <iostream>
#include "queueN.h"

using namespace std;

int main()
{

	Queue queue1;
	Queue queue2;
	Queue queue3;

	int i;
	int choice;
	int number;
	bool success; 

	success = false;
	
	choice = 0;
	
	while(choice != 9)
	{
		cout << endl;
		cout << "1. Enqueue." << endl;
		cout << "2. Dequeue." << endl;
		cout << "3. Print out queue." << endl;
		cout << "4. Clear queue." << endl;
		cout << "5. Assign queue." << endl;
		cout << "6. Equate queue." << endl;
		cout << "7. Check if full." << endl;
		cout << "8. Check if empty." << endl;
		cout << "9. Exit." << endl;
		cout << "Enter a menu option:" << endl;
		cin >> choice;

		switch(choice)
		{
			case 1:
				cout << "Enqueue." << endl;
				cout << "Enter a number." << endl;
				cin >> number;

				success = queue1.enqueue(number);

			break;

			case 2:
				cout << "Dequeue." << endl;
				success = queue1.dequeue(number);
				cout << "The number is now:" << endl;
				cout << number << endl;

			break;

			case 3:
				cout << "Printing out queue." << endl;
				cout << queue1;
	
			break;

			case 4:
				cout << "Clearing queue." << endl;
				queue1.clear();
			break;

			case 5:
				cout << "Assigning queue." << endl;
				queue2 = queue1;
				cout << queue2;
			break;

			case 6:
				cout << "Equating queue." << endl;
	
				if(queue1 == queue2)
				{
					cout << "The queues are equal." << endl;
				}
				else 
				{
					cout << "The queues are not equal." << endl;
				}

				success = queue2.dequeue(number);	

				if(queue1 == queue2)
				{
					cout << "The queues are equal." << endl;
				}
				else 
				{
					cout << "The queues are not equal." << endl;
				}

			break;

			case 7:
				cout << "Checking if full." << endl;
				
				if(queue1.full())
				{
					cout << "The queue is full." << endl;
				}
				else
				{
					cout << "The queue is not full." << endl;
				}

			break;

			case 8:
				cout << "Checking if empty." << endl;
	
				if(queue1.empty())
				{
					cout << "The queue is empty." << endl;
				}
				else
				{
					cout << "The queue is not empty." << endl;
				}			

				if(queue3.empty())
				{
					cout << "The queue is empty." << endl;
				}
				else
				{
					cout << "The queue is not empty." << endl;
				}	
	
			break;

			case 9:
				cout << "Exiting." << endl;
			break;

			default:
				cout << "Enter a valid choice" << endl;
		}
	
	cin.clear();
	cin.ignore();
	}



	return 0;
}
