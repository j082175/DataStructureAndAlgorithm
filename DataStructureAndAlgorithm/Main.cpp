
#include <iostream>
#include <list>
#include <vector>
#include "DoublyLinkedList.h"
#include "CBST.h"
#include <map>
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
	

	CBST<int, int> cbst;
	tPair<int, int> p1(10);
	cbst.insert(p1);
	cbst.insert(tPair<int, int>(44));
	cbst.insert(tPair<int, int>(35));

	return 0;
}