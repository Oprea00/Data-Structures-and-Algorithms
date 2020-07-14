#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {   //theta(1)
	//TODO - Implementation
	this->dll.head = NULL;
	this->dll.tail = NULL;
	this->dll.listSize = 0;
}


void MultiMap::add(TKey c, TValue v) {  //insert last   theta(1)
	//TODO - Implementation 
	DLLNode* newNode = new DLLNode;
	newNode->element.first = c;
	newNode->element.second = v;
	newNode->next = NULL;
	newNode->prev = this->dll.tail;
	if (this->dll.head == NULL)
	{
		this->dll.head = newNode;
		this->dll.tail = newNode;
	}
	else
	{
		newNode->prev = this->dll.tail;
		this->dll.tail->next = newNode;
		this->dll.tail = newNode;
	}
	this->dll.listSize++;
}


bool MultiMap::remove(TKey c, TValue v) {   //O(n)
	//TODO - Implementation
	DLLNode* currentNode = this->dll.head;
	//search the element in list 
	while ((currentNode!= NULL) and ((currentNode->element.first!=c) or (currentNode->element.second!=v)))
	{
		currentNode = currentNode->next;
	}
	DLLNode* deletedNode = currentNode;
	if (currentNode != NULL)
	{
		if (currentNode == this->dll.head) //first element
			if (currentNode == this->dll.tail) //which is the last as well
			{
				this->dll.head = NULL;
				this->dll.tail = NULL;
				this->dll.listSize--;
			}
			else
			{
				this->dll.head = this->dll.head->next;
				this->dll.head->prev = NULL;
				this->dll.listSize--;
			}
		else if (currentNode == this->dll.tail)
		{
			this->dll.tail = this->dll.tail->prev;
			this->dll.tail->next = NULL;
			this->dll.listSize--;
		}
		else
		{
			currentNode->next->prev = currentNode->prev;
			currentNode->prev->next = currentNode->next;
			this->dll.listSize--;
			deletedNode->next = NULL;
			deletedNode->prev = NULL;
		}
		return true;
	}

	return  false;
}


vector<TValue> MultiMap::search(TKey c) const {   //O(n) because BC=theta(1), WC=AC=theta(n)
	//TODO - Implementation
	vector<TValue> resultList;
	if (this->dll.head == NULL)
		return resultList;
	DLLNode* currentNode = this->dll.head;
	while (currentNode!=NULL)
	{
		if (currentNode->element.first == c)
		{
			resultList.push_back(currentNode->element.second);
		}
		currentNode = currentNode->next;
	}

	return resultList;
}


int MultiMap::size() const {  //theta(1)
	//TODO - Implementation
	return this->dll.listSize;
}


bool MultiMap::isEmpty() const {  //theta(1)
	//TODO - Implementation
	return this->dll.listSize==0;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {   //theta(n)
	DLLNode* currentNode;
	while (this->dll.head!=NULL)
	{
		currentNode = this->dll.head;
		this->dll.head = this->dll.head->next;
		delete currentNode;
	}
}
