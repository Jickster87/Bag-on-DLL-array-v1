#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	
	sizeBag = 0;
	head = tail = -1;
	firstEmpty = 0;

	//init elems array
	elems = new TElem[capacity];

	//init next array 
	for (int i = 0; i < capacity; i++) {
		next[i] = i + 1;
	}
	next[capacity - 1] = -1;

	//init prev array 
	for (int i = 0; i < capacity - 1; i++) {
		prev[i] = i - 1;
	}
	prev[0] = -1;

}


void Bag::add(TElem elem) {
	if (firstEmpty == -1) {
		//new capacity
		int newCapacity = capacity * 1.5;
		//temp arrays
		TElem* newElems = new TElem[newCapacity];
		int* newNext = new int[newCapacity];

		for (int i = 0; i < newCapacity; i++) {
			newElems[i] = elems[i];
			newNext[i] = next[i];
		}

		//init new capacity array
		for (int i = 0; i < newCapacity; i++) {
			newNext[i] = i + 1;
		}
		newNext[newCapacity - 1] = -1;

		//clear old arrays and add the new ones
		delete[] elems;
		delete[] next;
		elems = newElems;
		next = newNext;

		firstEmpty = capacity + 1;
		capacity = newCapacity;
	}
	// if this is the first element added
	if (head == -1)
	{
		int newPosition = firstEmpty;
		elems[newPosition] = elem;
		firstEmpty = next[firstEmpty];
		next[newPosition] = head; // why?? next[0] points to -1, shouldn't it point to [1] 
		prev[newPosition] = tail;
		head = tail = newPosition;
	}
	else
	{

	}


	sizeBag++;
}



bool Bag::remove(TElem elem) {
	if (sizeBag == 0) // If the bag is empty
		return false;

	// Search for the elem
	int current = head;

	while (current != -1 && elems[current] != elem) {
		current = next[current];
	}

	if (current != -1) {
		// Update head if removing the first element
		if (current == head) {
			head = next[head];
		}
		else {
			// Update next pointer of the previous node
			next[prev[current]] = next[current];
		}

		// Update tail if removing the last element
		if (current == tail) {
			tail = prev[tail];
		}
		else {
			// Update prev pointer of the next node
			prev[next[current]] = prev[current];
		}

		// Add the removed slot to the list of empty spaces
		next[current] = firstEmpty;
		prev[current] = -1; // Reset prev pointer
		firstEmpty = current;

		sizeBag--;
		return true;
	}

	return false;
}



bool Bag::search(TElem elem) const {
	int current;
	current = head;
	while (current != -1 and elems[current] != elem)
	{
		current = next[current];
	}
	if (current != -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Bag::nrOccurrences(TElem elem) const {
	int count = 0;
	int current = head;
	while (current != -1) {
		if (elems[current] == elem) {
			count++;
		}
		current = next[current];
	}
	return count;
}


int Bag::size() const {
	return sizeBag;
}


bool Bag::isEmpty() const {
	return sizeBag == 0;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	delete[] elems;
	delete[] next;
	delete[] prev;
}

