#include <iostream>
#include <list>
#include <vector>
#include "CBST.h"
#include <map>
//#include "BinarySearchTree.h"
using namespace std;

int main()
{
	CBST<int, int> bstint;
	bstint.insert(make_tPair(100,0));
	bstint.insert(make_tPair(150,0));
	bstint.insert(make_tPair(50, 0));

	CBST<int, int>::iterator Iter = bstint.begin();
	Iter = bstint.find(50);
	Iter = bstint.erase(Iter);



}