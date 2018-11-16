#include <iostream>
#include <cstdlib>
#include "listA.h"

using namespace std;

int main()
{

	List list1;
	List list2;
	List list3(list1);
	List list4(0);

	List list5;
	List list6;

	list5 = list6;

	List list7 = list6; 

	int i;
	int choice;
	char letter;
	bool success; 

	success = false;
	
	choice = 0;
	
	while(choice != 11)
	{
		cout << endl;
		cout << "1.  Insert into list." << endl;
		cout << "2.  Remove from list." << endl;
		cout << "3.  Go to next." << endl;
		cout << "4.  Go to prior." << endl;
		cout << "5.  Go to beginning." << endl;
		cout << "6.  Go to end." << endl;
		cout << "7.  Check if list is full." << endl;
		cout << "8.  Check if list is empty." << endl;
		cout << "9.  Clear list." << endl;
		cout << "10. Test assignment operator." << endl;
		cout << "11. Exit." << endl;
		cout << "Enter a menu option:" << endl;
		cin >> choice;

		switch(choice)
		{
			case 1:
				cout << "Insert into list." << endl;
				cout << "Enter a letter." << endl;
				cin >> letter;	
				list1.insert(letter);
				cout << list1;
			break;

			case 2:
				cout << "Remove from list." << endl;
				list1.remove(letter);
				cout << "The letter is now:" << endl;
				cout << letter << endl;
				cout << list1;
			break;

			case 3:
				cout << "Go to next." << endl;
				list1.gotoNext();
				cout << list1;
			break;

			case 4:
				cout << "Go to prior." << endl;
				list1.gotoPrior();
				cout << list1;
			break;

			case 5:
				cout << "Go to beginning." << endl;
				list1.gotoBeginning();
				cout << list1;
			break;

			case 6:
				cout << "Go to end." << endl;
				list1.gotoEnd();
				cout << list1;
			break;

			case 7:
				cout << "Checking if list is full." << endl;
				
				if(list1.full() == true)
				{
					cout << "The list is full." << endl;
				}
				else
				{
					cout << "The list is not full." << endl;
				}

			break;

			case 8:
				cout << "Checking if list is empty." << endl;
	
				if(list1.empty() == true)
				{
					cout << "The list is empty." << endl;
				}
				else
				{
					cout << "The list is not empty." << endl;
				}				
			break;

			case 9:
				cout << "Testing clear." << endl;
				list1.clear();
				cout << list1;		
			break;

			case 10:
				cout << "Testing assignment operator." << endl;
				list2 = list1;
				cout << "List 1:" << endl;
				cout << list1;
				cout << "List 2:" << endl;
				cout << list2;				
			break;

			case 11:
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
