#pragma once
#include <vector>
#include <utility>

using namespace std;

//DO NOT CHANGE THIS PART
#define initialCapacity 10;
typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool (*Relation)(TPriority p1, TPriority p2);
#define NULL_TELEM pair<TElem, TPriority> (-11111,-11111);

struct Node {
	pair<TElem, TPriority> element;
	int next;
};

struct SLLA {
	Node* elems;
	int capacity, head, firstEmpty, size;
};

class PriorityQueue {
private:
	//TODO - Representation
	
	Relation relation;
	SLLA slla;

public:
	//implicit constructor
	PriorityQueue(Relation r);

	//pushes an element with priority to the queue
	void push(TElem e, TPriority p);

	//returns the element with the highest priority with respect to the order relation
	//throws exception if the queue is empty
	Element top()  const;

	//removes and returns the element with the highest priority
	//throws exception if the queue is empty
	Element pop();

	//checks if the queue is empty
	bool isEmpty() const;

	//destructor
	~PriorityQueue();

	void merge(PriorityQueue& pq, PriorityQueue& pq1, PriorityQueue& pq2);

};