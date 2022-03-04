
#include <iostream>
#include <list>
#include <vector>
#include "DoublyLinkedList.h"
using namespace std;

int main()
{
	DoublyLinkedList<int> dl{ 2,5,3,8,5,39,1,44,3,23 };
	DoublyLinkedList<int>::iterator itr;
	DoublyLinkedList<int>::reverse_iterator riter;
	dl.Sort();
	for (itr = dl.begin(); itr != dl.end(); itr++)
	{
		cout << *itr << endl;
	}
	
	
	

	list<int> l{ 1,2,3,4,5 };
	list<int>::const_iterator citer;
	list<int>::iterator iter;
	vector<int>::iterator i;
	
}