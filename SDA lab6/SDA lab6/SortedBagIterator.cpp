#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>
#include <stdexcept>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b), currentNode{ nullptr }, stack{ std::stack<BSTNode*>{} } {
	//TODO - Implementation
	first();
}

TComp SortedBagIterator::getCurrent() {
	//TODO - Implementation
	if (!valid())
		throw std::runtime_error("");
	return currentNode->info;
}

bool SortedBagIterator::valid() {
	//TODO - Implementation
	if (bag.isEmpty())
		return false;
	return currentNode != nullptr;
}

void SortedBagIterator::next() {
	//TODO - Implementation
	if (!valid())
		throw std::runtime_error("");
	BSTNode* node = stack.top();
	stack.pop();
	if (node->rightChild != nullptr)
	{
		node = node->rightChild;
		while (node != nullptr)
		{
			stack.push(node);
			node = node->leftChild;
		}
	}
	if (stack.empty() == false)
		currentNode = stack.top();
	else
		currentNode = nullptr;
}

void SortedBagIterator::first() {
	//TODO - Implementation
	currentNode = bag.root;
	stack = std::stack<BSTNode*>{};
	while (currentNode != nullptr)
	{
		stack.push(currentNode);
		currentNode = currentNode->leftChild;
	}
	if (stack.empty() == false)
		currentNode = stack.top();
	else
		currentNode = nullptr;
}

