#pragma once
#include <iostream>
#include "BinSearchTree.h"
#include "RestrictedMap.h"

using namespace std;

int main()
{
	cout << "Testing Binary Search Tree" << endl;
	//create tree
	BinarySearchTree<int> tree;
	tree.insert(8);
	tree.insert(10);
	tree.insert(14);
	tree.insert(13);
	tree.insert(3);
	tree.insert(1);
	tree.insert(6);
	tree.insert(4);
	tree.insert(7);
	//print tree
	tree.printInOrder();

	cout << "Testing Restricted Map" << endl;
	//create map
	RestrictedMap<int, int> map;
	const OrderedPair<const int, int> kvpair(8, 80);
	const OrderedPair<const int, int> kvpair1(10, 100);
	const OrderedPair<const int, int> kvpair2(14, 140);
	const OrderedPair<const int, int> kvpair3(13, 130);

	OrderedPair<RestrictedMap<int,int>::map_iterator, bool> result = map.insert(kvpair);
	if (result.second)
		cout << "Insertion of 8, 80 successful" << endl;
	else
		cout << "8, 80 already exists" << endl;
	
	//insert duplicate
	map.insert(kvpair1);
	OrderedPair<RestrictedMap<int, int>::map_iterator, bool> result1 = map.insert(kvpair1);
	if (result1.second)
		cout << "Insertion of 10, 100 successful" << endl;
	else
		cout << "10, 100 already exists" << endl;

	map.insert(kvpair2);
	map.insert(kvpair3);
	cout << " Inserted two more pairs into the map." << endl;
	//test access operator
	cout << "map[8] = " << map[8] << endl;



}

