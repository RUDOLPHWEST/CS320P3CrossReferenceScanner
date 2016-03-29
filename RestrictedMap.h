// RestrictedMap: emphasizes the insertion and retrieval of keys
// with access to the values.
#pragma once
#include "BinSearchTree.h"
#include "OrderedPair.h"


// implements a map containing key/value pairs.
// a map does not contain multiple copies of the same item.
// types T and Key must have a default constructor
template <typename Key, typename T>
class RestrictedMap
{
public:

	typedef typename BinarySearchTree< OrderedPair<const Key, T> >::iterator map_iterator;
	typedef typename BinarySearchTree< OrderedPair<const Key, T> >::const_iterator const_map_iterator;
	// RestrictedMap iterators are simply BinarySearchTree iterators. an iterator cannot
	// change the key in a tree node, since the key attribute
	// of a OrderedPair object in the tree is cons

	typedef OrderedPair<const Key, T> value_type;
	// for programmer convenience

	RestrictedMap() {};

	RestrictedMap(value_type *first, value_type *last)
	{
		//insert by key and make the element = T
		return t(first, last);
	}
	// build a map whose key/value pairs are determined by pointer
	// values [first, last)

	bool empty() const {
		// is the map empty
		return t.empty()
	}

	int size() const {
		// return the number of elements in the map
		return t.size();
	}

	map_iterator find(const Key& key) {
		// search for item in the map with the given key
		// and return an iterator pointing at it, or end()
		// if it is not found
		return (t.find(OrderedPair<const Key, T>(key, default))).first;
	}

	const_map_iterator find(const Key& key) const {
		// constant version of find()
		return (t.find(OrderedPair<const Key, T>(key, default))).first;
	}

	T& operator[] (const Key& key) {
		// if no value is associated with key, create a new
		// map entry with the default value T() and return a
		// reference to the default value; otherwise,
		// return a reference to the value already associated
		// with the key 
		OrderedPair<map_iterator, 
			bool> result = t.find(OrderedPair<const Key, T>(key, default));
		if (result.second)
			return (*(result.first)).second;
		else {
			OrderedPair<map_iterator, bool> insertResult = t.insert
				(OrderedPair<const Key, T> kvpair(key, default));
			return (*(insertResult.first)).second;
		}
	}

	OrderedPair<map_iterator, bool> insert(const value_type& kvpair) {
		// if the map does not contain a key/value pair whose
		// key matches that of kvpair, insert a coy of kvpair
		// and return a OrderedPair object whose first element is an
		// map_iterator positioned at the new key/value pair and whose second
		// element is true. if the map already contains a key/value
		// pair whose key matches that of kvpair, return a OrderedPair
		// object whose first element is an map_iterator positioned at the
		// existing key/value pair and whose second element is false
		return t.insert(kvpair);
	}

	int erase(const Key& key) {
		// erase the key/value pair with the specified key
		// from the map and return the number
		// of items erased (1 or 0)
		if (t.find(key) == true)
		{
			t.erase(key);
			return 1;
		}
		else
			return 0;
	}

	void erase(map_iterator pos) {
		// erase the map key/value pair pointed by to pos
		t.erase(pos);
	}

	void erase(map_iterator first, map_iterator last) {
		// erase the key/value pairs in the range [first, last)
		t.erase(first, last);
	}

	map_iterator begin() {
		// return an map_iterator pointing at the first member
		// in the map
		map_iterator itr = t.begin();
		return itr;
	}
	const_map_iterator begin() const {
		// constant version of begin()
		map_iterator itr = t.begin();
		return itr;
	}

	map_iterator end() {
		// return an map_iterator pointing just past the last
		// member in the map
		map_iterator itr = t.end();
		return itr;
	}
	const_map_iterator end() const {
		// constant version of end()
		map_iterator itr = t.end();
		return itr;
	}

private:
	// RestrictedMap implemented using an BinarySearchTree of key-value pairs
	BinarySearchTree<OrderedPair<const Key, T> > t;
};

#pragma once
