#pragma once
#include "SortedBag.h"
#include <stack>

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);
	BSTNode* currentNode;
	std::stack <BSTNode*> stack;
	//TODO - Representation

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

