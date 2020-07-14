#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <stdexcept>

MultiMapIterator::MultiMapIterator(const MultiMap& c) : col(c) {
	//TODO - Implementation
	currentNode = this->col.dll.head;
}

TElem MultiMapIterator::getCurrent() const {
	//TODO - Implementation
	if (!valid())
	{
		throw std::runtime_error("error");
	}
	return currentNode->element;
}

bool MultiMapIterator::valid() const {
	//TODO - Implementation
	//if (this->position == this->col.dll.listSize)
	//	return false;
	//return true;
	return currentNode != NULL;
}

void MultiMapIterator::next() {
	//TODO - Implementation
	if (!valid())
	{
		throw std::runtime_error("error");
	}
	currentNode = currentNode->next;
}

void MultiMapIterator::first() {
	//TODO - Implementation
	currentNode = this->col.dll.head;
}

