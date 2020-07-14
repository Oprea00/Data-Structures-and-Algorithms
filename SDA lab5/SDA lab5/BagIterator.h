#pragma once
#include "Bag.h"

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;

private:
	const Bag& bag;
	//TODO  - Representation
	HashTable hashtable;
	int currentPosition;
	Node* currentNode;
	int currentFrequency=1;

	BagIterator(const Bag& c);
public:
	void first();
	void next();
	TElem getCurrent() const;
	bool valid() const;
};
