#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)	//theta(1)
{
	//TODO - Implementation
	this->position = 0;
}


void SortedSetIterator::first() {	//theta(1)
	//TODO - Implementation
	this->position = 0;
}


void SortedSetIterator::next() {	//theta(1)
	//TODO - Implementation
	if (this->valid())
		this->position++;
	else
		throw std::exception();
}


TElem SortedSetIterator::getCurrent()	//theta(1)
{
	//TODO - Implementation
	if (this->valid())
		return this->multime.dynamicArray[this->position];
	else
		throw std::exception();
}

bool SortedSetIterator::valid() const {	//theta(1)
	//TODO - Implementation
	return this->position<this->multime.length;
}