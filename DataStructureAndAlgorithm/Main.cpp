
#include <iostream>
#include <list>
#include <vector>
#include "DoublyLinkedList.h"
using namespace std;

int main()
{
	DoublyLinkedList<int> dl{ 1,2,3,4,5 };
	DoublyLinkedList<int>::iterator itr;
	DoublyLinkedList<int>::reverse_iterator riter;

	for (itr = dl.begin(); itr != dl.end(); itr++)
	{
		cout << *itr << endl;
	}

	for (riter = dl.rbegin(); riter != dl.rend(); riter++)
	{
		cout << *riter << endl;
	}
	
	

	list<int> l{ 1,2,3,4,5 };
	list<int>::const_iterator citer;
	list<int>::iterator iter;
	vector<int>::iterator i;
	
}