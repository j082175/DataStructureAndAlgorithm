#include <iostream>
#include <list>
#include <vector>
#include "DoublyLinkedList.h"
#include "CBST.h"
#include <map>
using namespace std;

int main()
{
	CBST<int, int> cbst;
	tPair<int, int> p1{ 10 };
	cbst.insert(p1);
	cbst.insert(tPair<int, int>{44});
	cbst.insert(tPair<int, int>{35});
	cbst.insert(make_tPair(255,0));

	CBST<int, int>::iterator itr1 = cbst.begin();
	itr1 = cbst.find(255);

	for (auto itr1 = cbst.begin(); itr1 != cbst.end(); itr1++)
	{
		cout << itr1->first << " " << itr1->second << endl;
	}

	return 0;
}