#include <exception>
#include "BagIterator.h"
#include "Bag.h"
#include <stdexcept>

using namespace std;


BagIterator::BagIterator(const Bag& c) : bag(c)
{
	//TODO - Implementation
	this->hashtable = c.hashtable;
	this->currentPosition = 0;
	while (this->currentPosition < this->hashtable.capacity && hashtable.T[this->currentPosition] == NULL) {
		this->currentPosition++;
	}
	if (this->currentPosition < this->hashtable.capacity) {
		this->currentNode = this->hashtable.T[this->currentPosition];
	}
	else {
		this->currentNode = NULL;
	}
}

void BagIterator::first() {
	//TODO - Implementation
	this->currentPosition = 0;
	while (this->currentPosition < this->hashtable.capacity && hashtable.T[this->currentPosition]==NULL)
	{
		this->currentPosition++;
	}
	if (this->currentPosition < this->hashtable.capacity)
		this->currentNode = this->hashtable.T[this->currentPosition];
	else
		this->currentNode = NULL;
}


void BagIterator::next() {
	//TODO - Implementation
	if (!this->valid()) {
		throw std::exception();
	}
	if (this->currentFrequency == 1)
	{
		this->currentNode = this->currentNode->next;
		if (this->currentNode != NULL)
			this->currentFrequency = this->currentNode->freq;
		if (this->currentNode == NULL)
		{
			this->currentPosition++;
			while (this->currentPosition < this->hashtable.capacity && hashtable.T[this->currentPosition] == NULL) {
				this->currentPosition++;
			}
			if (this->currentPosition < this->hashtable.capacity)
			{
				this->currentNode = this->hashtable.T[this->currentPosition];
				this->currentFrequency = this->currentNode->freq;
			}
			else
				this->currentNode = NULL;
		}
	}
	else
		this->currentFrequency--;
}


bool BagIterator::valid() const {
	//TODO - Implementation
	return this->currentNode != NULL && this->currentPosition < this->hashtable.capacity;
}



TElem BagIterator::getCurrent() const
{
	//TODO - Implementation
	if (!this->valid()) {
		throw std::exception();	
	} 
	return this->currentNode->info;
}
