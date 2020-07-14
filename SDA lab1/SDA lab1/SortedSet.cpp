#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {	//theta(1)
	//TODO - Implementation
	this->r = r;
	this->capacity = 20;
	this->dynamicArray = new TComp[this->capacity];
	this->length = 0;
}


bool SortedSet::add(TComp elem) {	//O(n)
	//TODO - Implementation
	
	if (this->length == this->capacity)  //then resize
	{
		this->capacity *=2;
		TComp* auxArray;
		auxArray = new TComp[this->capacity];
		for (int index = 0; index <this->length; index++)
			auxArray[index] = this->dynamicArray[index];
		delete[] this->dynamicArray;
		this->dynamicArray = auxArray;
	}

	int index = 0;
	while (index < this->length&& this->r(this->dynamicArray[index], elem))
	{
		if (this->dynamicArray[index] == elem)
			return false;
		index++;
	}
	for (int index2 = this->length; index2 > index; index2--)
		this->dynamicArray[index2] = this->dynamicArray[index2 - 1];
	this->dynamicArray[index] = elem;
	this->length++;
	return true;
	
}


bool SortedSet::remove(TComp elem) {	//O(n)
	//TODO - Implementation
	int index = 0;
	
	while (index < this->length && this->r(this->dynamicArray[index], elem))
	{
		if (this->dynamicArray[index] == elem)
		{
			this->length--;
			for (int index2 = index; index2 < this->length; index2++)
			{
				this->dynamicArray[index2] = this->dynamicArray[index2 + 1];
			}
			
			return true;
		}
		index++;
	}
	return false;
}


bool SortedSet::search(TComp elem) const {	//O(n)
	//TODO - Implementation
	int index = 0;
	while (index < this->length && this->r(this->dynamicArray[index], elem))
	{
		if (this->dynamicArray[index] == elem)
			return true;
		index++;
	}
	return false;
}


int SortedSet::size() const {	//theta(1)
	//TODO - Implementation
	return this->length;
}



bool SortedSet::isEmpty() const {	//theta(1)
	//TODO - Implementation
	if (this->length == 0)
		return true;
	return false;
}

SortedSetIterator SortedSet::iterator() const {	//theta(1)
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {	//theta(1)
	//TODO - Implementation
	delete[] this->dynamicArray;
}


void SortedSet::intesection1(SortedSet& s, SortedSet& s1, SortedSet& s2)
{
	SortedSetIterator iterator = s1.iterator();
	while (iterator.valid())
	{
		TElem element = iterator.getCurrent();
		if (s2.search(element) == true)
		{
			s.add(element);
		}
		iterator.next();
	}
}

//BC=theta(1) WC=theta(n) Ac=theta(n)  TC=O(n)
/*subalgorithm intersaction1(s,s1,s2) is:
	iterator<-s1.iterator()
	while iterator.valid() execute
		element<-iterator.getCurrent()
		if s2.search(element) = true then 
			s.add(element)
		end_if
		iterator.next()
	end_while
end_function
*/



void SortedSet::intersection(const SortedSet& s) //BC=theta(n) WC=theta(n) AC=theta(n) TC=theta(n)
{
	int index = 0;
	while (index < this->length)
	{
		TElem element = this->dynamicArray[index];
		if (s.search(element) != true)
			this->remove(element);
		index++;
	}
}

/*
subalgorithm intersaction(s) is:
	index<-0
	while index<length execute:
		elemet<-dynamicArray[index]
		if s.search(element) != true then
			remove(element)
		end_if
		index+=1
	end_while
end_subalgorithm
*/