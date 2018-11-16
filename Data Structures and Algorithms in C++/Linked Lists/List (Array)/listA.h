#include <iostream>
#include <cstdlib>

using namespace std;

class List
{
	public:

		List(int = 10);
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

		int size;
		int actual;
		int cursor;
		char *data;
};
