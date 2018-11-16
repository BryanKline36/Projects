#include <iostream>

using namespace std;

class List;

class Node
{
	private:

		Node(char, Node*);

		friend class List;

		friend ostream& operator<<(ostream&, const List&);

		char data;
		Node* next;
};

class List
{
	public:

		List(int = 0);
		List(const List&);
		~List();

		bool gotoBeginning();
		bool gotoEnd();
		bool gotoNext();
		bool gotoPrior();
		bool insert(char);
		bool remove(char&);
		bool empty() const;
		bool full() const;
		bool clear();

		List& operator = (const List&);
		friend ostream& operator << (ostream&, const List&);

	private:

		Node* head;
		Node* cursor;
};


