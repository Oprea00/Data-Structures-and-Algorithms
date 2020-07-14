#include "PriorityQueue.h"
#include <exception>
using namespace std;


PriorityQueue::PriorityQueue(Relation r) {    //BC=WC=AC=theta(n) => theta(n) overall
	//TODO - Implementation
	this->relation = r;
	this->slla.size = 0;
	this->slla.firstEmpty = 0;
	this->slla.head = -1;
	this->slla.capacity = initialCapacity;

	this->slla.elems = new Node[this->slla.capacity];

	for (int index = 0; index < this->slla.capacity - 1; index++)
		this->slla.elems[index].next = index + 1;
	this->slla.elems[this->slla.capacity - 1].next = -1;
}


void PriorityQueue::push(TElem e, TPriority p) {  //BC=theta(1)  WC=AC=theta(n)  => O(n) overall
	//TODO - Implementation
	int currentNode = this->slla.head;
	int currentPosition = 0;
	//search for the correct position to put the element
	while (currentNode != -1 && currentPosition < this->slla.size && this->relation(this->slla.elems[currentNode].element.second, p))
	{
		currentNode = this->slla.elems[currentNode].next;
		currentPosition++;
	}
	//insert node on that position
	int newNode = this->slla.firstEmpty;
	//check for resize
	if (newNode == -1)
	{
		//resize
		Node* newElems = new Node[this->slla.capacity * 2];
		for (int index = 0; index < this->slla.capacity; index++)
			newElems[index] = this->slla.elems[index];
		for (int index = this->slla.capacity; index < 2* this->slla.capacity - 1; index++)
			newElems[index].next = index + 1;
		newElems[this->slla.capacity * 2 - 1].next = -1;
		this->slla.firstEmpty = this->slla.capacity;
		
		delete[] this->slla.elems; 
		this->slla.elems = newElems;
		this->slla.capacity *= 2;
	}
	
	if (currentPosition == 0)  //if the correct position is the first one
	{    
		int newPosition = this->slla.firstEmpty;
		this->slla.elems[newPosition].element.first = e;
		this->slla.elems[newPosition].element.second = p;
		this->slla.firstEmpty = this->slla.elems[slla.firstEmpty].next;
		this->slla.elems[newPosition].next = this->slla.head;
		this->slla.head = newPosition;
	}
	else
	{
		int poz = 0;
		int currentNode = this->slla.head;
		while (currentNode != -1 && poz < currentPosition - 1)
		{
			currentNode = this->slla.elems[currentNode].next;
			poz++;
		}

		if (currentNode != -1)
		{
			newNode = this->slla.firstEmpty;
			this->slla.firstEmpty = this->slla.elems[this->slla.firstEmpty].next;
			this->slla.elems[newNode].element.first = e;
			this->slla.elems[newNode].element.second = p;
			this->slla.elems[newNode].next = this->slla.elems[currentNode].next;
			this->slla.elems[currentNode].next = newNode;
		}
	}
	this->slla.size++;	
}

//throws exception if the queue is empty
Element PriorityQueue::top() const {   //BC=Wc=AC=theta(1) => theta(1) overall
	//TODO - Implementation
	if (this->isEmpty())
		throw exception();
	return this->slla.elems[this->slla.head].element;
}

Element PriorityQueue::pop() {  //BC=theta(1)  WC=AC=theta(n)  => O(n) overall
	//TODO - Implementation
	if (this->isEmpty())
		throw exception();
	Element element = this->slla.elems[slla.head].element;
	if (this->slla.elems[slla.head].next != -1)
		this->slla.head = this->slla.elems[this->slla.head].next;
	else		//if we have only one element 
		this->slla.head = -1;

	this->slla.size--;

	return element;
}

bool PriorityQueue::isEmpty() const {  //BC=Wc=AC=theta(1)  => theta(1) overall
	//TODO - Implementation
	return this->slla.size == 0;
}


PriorityQueue::~PriorityQueue() {  //BC=Wc=AC=theta(1)  => theta(1) overall
	//TODO - Implementation
	delete[] this->slla.elems;
}


void PriorityQueue::merge(PriorityQueue& pq, PriorityQueue& pq1, PriorityQueue& pq2)  //BC=theta(1)  WC=AC=theta(max{n,m})~theta(n^2)  overall: O(n)
{
	if (pq1.isEmpty() == true and pq2.isEmpty() == true)
		return;
	else
		while (pq1.isEmpty() == false or pq2.isEmpty() == false) 
		{
			if (pq1.isEmpty())
			{
				while (pq2.isEmpty() == false)
				{
					Element element = pq2.pop();
					TElem elem = element.first;
					TPriority priority = element.second;
					pq.push(elem, priority);
				}
			}
			else if (pq2.isEmpty())
			{
				while (pq1.isEmpty() == false)
				{
					Element element = pq1.pop();
					TElem elem = element.first;
					TPriority priority = element.second;
					pq.push(elem, priority);
				}
			}

			else
			{
				bool order = pq.relation(pq1.top().second, pq2.top().second);
				if (order == true)
				{
					Element element = pq1.pop();
					TElem elem = element.first;
					TPriority priority = element.second;
					pq.push(elem, priority);
				}
				else
				{
					Element element = pq2.pop();
					TElem elem = element.first;
					TPriority priority = element.second;
					pq.push(elem, priority);
				}
			}
		}
}
;

//adds all elements (and their priorities) from pq into the PriorityQueue
//void merge(PriorityQueue& pq);

//Obs.Assume that the two priority queues use the same relation