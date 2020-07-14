#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <stdexcept>

// theta(1)
SortedBag::SortedBag(Relation r){
	//TODO - Implementation
	this->nrOFElements = 0;
	this->root = new BSTNode;
	this->root = nullptr;
	this->rel = r;
}

void SortedBag::add(TComp e) {  //BC=theta(1)
	//TODO - Implementation
	BSTNode* currentNode = this->root;
	BSTNode* parentNode;
	bool added = false;
	if (currentNode == nullptr)
	{
		BSTNode* newNode = new BSTNode;
		newNode->info = e;
		newNode->leftChild = nullptr;
		newNode->rightChild = nullptr;
		this->root = newNode;
		this->nrOFElements++;
		return;
	}
	while (!added && currentNode != nullptr)
	{
		if (rel(e,currentNode->info))
		{
			if (currentNode->leftChild == nullptr)
			{
				BSTNode* newNode = new BSTNode;
				newNode->info = e;
				newNode->leftChild = nullptr;
				newNode->rightChild = nullptr;
				currentNode->leftChild = newNode;
				added = true;
				this->nrOFElements++;
				return;
			}
			else
				currentNode = currentNode->leftChild;
		}
		else
		{
			if (currentNode->rightChild == nullptr)
			{
				BSTNode* newNode = new BSTNode;
				newNode->info = e;
				newNode->leftChild = nullptr;
				newNode->rightChild = nullptr;
				currentNode->rightChild = newNode;
				added = true;
				this->nrOFElements++;
				return;
			}
			else
				currentNode = currentNode->rightChild;
		}
	}
}

bool SortedBag::remove(TComp e) {
	//TODO - Implementation
	BSTNode* currentNode = this->root;
	BSTNode* node{};
	BSTNode* minNode;
	BSTNode* parentNode;
	BSTNode* child;
	bool found = false;
	if (!search(e))
		return false;
	while (currentNode != nullptr and !found)
	{
		if (currentNode->info == e)
		{
			node = currentNode;
			found = true;
		}
		else if (rel(e, currentNode->info))
			currentNode = currentNode->leftChild;
		else
			currentNode = currentNode->rightChild;
	}
	
	if (node == this->root)
	{
		if (this->root->leftChild == nullptr and this->root->rightChild == nullptr)
		{
			this->nrOFElements--;
			root = nullptr;
			delete this->root;
			return true;
		}
		else if (this->root->leftChild != nullptr and this->root->rightChild != nullptr)
		{
			minNode = getMinimum(node->rightChild);
			this->root->info = minNode->info;
			this->nrOFElements--;
			delete minNode;
			return true;
		}
		else if (this->root->leftChild == nullptr or this->root->rightChild == nullptr)
		{
			if (node->leftChild != nullptr)
				child = node->leftChild;
			else
				child = node->rightChild;
			delete this->root;
			this->root = child;
			this->nrOFElements--;
			return true; 
		}
	}
	else {
		if (node->leftChild != nullptr and node->rightChild != nullptr)
		{
			minNode = getMinimum(node->rightChild);
			node->info = minNode->info;
			//parentNode = getParent(minNode);
			//parentNode->leftChild = nullptr;
			this->nrOFElements--;
			delete minNode;
			return true;
		}
		else if (node->leftChild == nullptr and node->rightChild == nullptr)
		{
			parentNode = getParent(node);
			if (parentNode->leftChild == node)
				parentNode->leftChild = nullptr;
			else
				parentNode->rightChild = nullptr;
			this->nrOFElements--;
			delete node;
			return true;
		}
		else if (node->leftChild == nullptr or node->rightChild == nullptr)
		{
			if (node->leftChild != nullptr)
				child = node->leftChild;
			else
				child = node->rightChild;
			parentNode = getParent(node);
			if (parentNode->leftChild == node)
				parentNode->leftChild = child;
			else
				parentNode->rightChild = child;
			this->nrOFElements--;
			delete node;
			return true;
		}
	}
	return false;
}
	

BSTNode* SortedBag::getMinimum(BSTNode* startingNode)
{
	BSTNode* currentNode = new BSTNode;
	currentNode->info = startingNode->info;
	currentNode->leftChild = startingNode->leftChild;
	currentNode->rightChild = startingNode->rightChild;
	if (currentNode == nullptr)
		return nullptr;
	else
		while (currentNode->leftChild != nullptr)
		{
			currentNode = currentNode->leftChild;
		}
	
	return currentNode;
}

BSTNode* SortedBag::getParent(BSTNode* node)
{
	BSTNode* child = this->root;
	if (child->info == node->info and child->leftChild == node->leftChild and child->rightChild == node->rightChild)
		return nullptr;
	else
	{
		while (child != nullptr and child->leftChild != node and child->rightChild != node)
			if (!rel(child->info, node->info ))
				child = child->leftChild;
			else
				child = child->rightChild;
		return child;
	}
}


bool SortedBag::search(TComp elem) const {
	//TODO - Implementation
	if (this->nrOFElements == 0 || this->root == nullptr)
		return false;
	BSTNode* currentNode = this->root;
	bool found = false;
	while (currentNode != nullptr and !found)
	{
		if (currentNode->info == elem)
			found = true;
		else if (this->rel(currentNode->info, elem))
			currentNode = currentNode->rightChild;
		else
			currentNode = currentNode->leftChild;
	}
	return found;
}


int SortedBag::nrOccurrences(TComp elem) const {
	//TODO - Implementation
	if (this->nrOFElements == 0 || this->root == nullptr)
		return 0;
	int occurences = 0;
	bool something = false;
	BSTNode* currentNode = this->root;
	while (currentNode != nullptr)
	{
		if (currentNode->info == elem)
		{
			occurences++;
			if (currentNode->leftChild != nullptr and currentNode->leftChild->info == elem)
			{
				currentNode = currentNode->leftChild;
				something = true;
			}
			else if (currentNode->rightChild != nullptr and currentNode->rightChild->info == elem)
			{
				currentNode = currentNode->rightChild;
				something = true;
			}
		}
		if (!something)
		{
			if (this->rel(elem, currentNode->info))
				currentNode = currentNode->leftChild;
			else
				currentNode = currentNode->rightChild;
		}
		something = false;
	}
	return occurences;
}


//adds nr occurrences of elem into the SortedBag.
	//throws an exception if nr is negative
void SortedBag::addOccurrences(int nr, TComp elem)
{
	if (nr < 0)
		throw std::runtime_error("number is negative");
	for (int index = 0; index < nr; index++)
	{
		add(elem);
	}
}


int SortedBag::size() const {    //BC=Wc=AC=theta(1)  => theta(1) overall
	//TODO - Implementation
	return nrOFElements;
}


bool SortedBag::isEmpty() const {   //BC=Wc=AC=theta(1)  => theta(1) overall
	//TODO - Implementation
	return nrOFElements == 0;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	//TODO - Implementation
}



