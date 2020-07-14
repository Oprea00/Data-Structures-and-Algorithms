#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


int Bag::hashFunction(TElem elem) const  //theta(1)
{
	return (elem + 50000) % this->hashtable.capacity;
}

void Bag::resize()  //theta(m)
{
	int oldCapacity = this->hashtable.capacity;
	this->hashtable.capacity *= 2;
	Node** newT = new Node*[this->hashtable.capacity];
	for (int index = 0; index < this->hashtable.capacity; index++)
		newT[index] = NULL;
	Node* prevNode = NULL;
	for (int index = 0; index < oldCapacity; index++)
	{
		Node* currentNode = this->hashtable.T[index];
		while (currentNode != NULL)
		{
			prevNode = currentNode;
			int position = this->hashFunction(currentNode->info);
			Node* newNode = new Node();
			newNode->info = currentNode->info;
			newNode->freq = currentNode->freq;
			newNode->next = newT[position];
			newT[position] = newNode;
			currentNode = currentNode->next;
			delete prevNode;
		}
	}
	delete[] this->hashtable.T;
	this->hashtable.T = newT;
}

Bag::Bag() {	//theta(1)
	//TODO - Implementation
	this->hashtable.capacity = 23;
	this->hashtable.size = 0;
	this->hashtable.T = new Node * [this->hashtable.capacity];
	for (int index = 0; index < this->hashtable.capacity; index++)
	{
		this->hashtable.T[index] = NULL;
	}
}


void Bag::add(TElem elem) {   //O(m)  BC=theta(1)  WC=theta(m)
	//TODO - Implementation
	if (this->hashtable.size / this->hashtable.capacity > 0.7)
		this->resize();
	int position = this->hashFunction(elem);
	bool found = this->search(elem);
	if (found == false)
	{
		Node* newNode = new Node();
		newNode->info = elem;
		newNode->freq = 1;
		newNode->next = this->hashtable.T[position];
		this->hashtable.T[position] = newNode;
		this->hashtable.size++;
	}
	else
	{
		while (this->hashtable.T[position] != NULL && this->hashtable.T[position]->info != elem)
			this->hashtable.T[position] = this->hashtable.T[position]->next;
		if (this->hashtable.T[position] != NULL)
		{
			this->hashtable.T[position]->freq++;
			this->hashtable.size++;
		}
	}
}


bool Bag::remove(TElem elem) {  //theta(1)
	//TODO - Implementation
	int position = this->hashFunction(elem);
	Node* currentNode = this->hashtable.T[position];
	Node* previousNode = NULL;
	int pos;
	while (currentNode != NULL && currentNode->info != elem) {
		previousNode = currentNode;
		currentNode = currentNode->next;
	}
	if (currentNode != NULL)
	{
		if (currentNode->freq == 1)
		{
			if (previousNode == NULL)
				this->hashtable.T[position] = this->hashtable.T[position]->next;
			else
			{
				previousNode->next = currentNode->next;
				currentNode->next = NULL;
			}
			delete currentNode;
			this->hashtable.size--;
			return true;
		}
		else
		{
			currentNode->freq--;
			this->hashtable.size--;
			return true;
		}
	}
	return false;
}


bool Bag::search(TElem elem) const {  //theta(1)
	//TODO - Implementation
	int position = this->hashFunction(elem);
	Node* currentNode = this->hashtable.T[position];
	while (currentNode != NULL && currentNode->info != elem)
	{
		currentNode = currentNode->next;
	}
	if (currentNode != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Bag::nrOccurrences(TElem elem) const {  //theta(1)
	//TODO - Implementation
	int position = this->hashFunction(elem);
	Node* currentNode = this->hashtable.T[position];
	while (currentNode != NULL && currentNode->info != elem)
	{
		currentNode = currentNode->next;
	}
	if (currentNode != NULL)
	{
		return currentNode->freq;
	}
	else
	{
		return 0;
	}
}


int Bag::size() const {  //theta(1)
	//TODO - Implementation
	return this->hashtable.size;
}


bool Bag::isEmpty() const {  //theta(1)
	//TODO - Implementation
	return this->hashtable.size == 0;
}

BagIterator Bag::iterator() const {  //theta(1)
	return BagIterator(*this);
}


Bag::~Bag() {
	//TODO - Implementation
	for (int index = 0; index < this->hashtable.capacity; index++)  //theta(m)
	{
		Node* currentNode = this->hashtable.T[index];
		Node* prevNode = NULL;
		while (currentNode != NULL)
		{
			prevNode = currentNode;
			currentNode = currentNode->next;
			delete prevNode;
		}
	}
	delete[] this->hashtable.T;
}

