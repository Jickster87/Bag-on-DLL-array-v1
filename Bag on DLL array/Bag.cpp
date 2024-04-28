#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	
	sizeBag = 0;
	capacity = MAX_CAPACITY;
	head = tail = -1;
	firstEmpty = 0;

	//init elems array ?
	elems[capacity-1];
	elems[0] = -1;

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
	if (firstEmpty == -1)
	{
		throw exception(); //should i cover resize here??
	}

	int newSlot = firstEmpty;
	firstEmpty = next[firstEmpty];
	elems[newSlot] = elem;

	// if this is the first element added
	if (head == -1)
	{
		head = tail = newSlot;
	}
	// if this is not the first element added
	else {
		next[tail] = newSlot;
		prev[newSlot] = tail;
		tail = newSlot;
	}
	sizeBag++;
}


bool Bag::remove(TElem elem) {
	if (firstEmpty == -1) {
		throw exception();
	}

	// Search for elem
	int current = head;
	int prevNode = -1;

	while (current != -1 && elems[current] != elem) {
		prevNode = current;
		current = next[current];
	}

	if (current != -1) {
		// Update next and prev pointers
		if (current == head) {
			head = next[head];
		}
		else {
			next[prevNode] = next[current];
		}

		// Add the removed slot to the list of empty spaces
		next[current] = firstEmpty;
		firstEmpty = current;

		sizeBag--;
		return true;
	}

	return false; // Element not found
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
	//TODO - Implementation
	return sizeBag;
}


bool Bag::isEmpty() const {
	return sizeBag == 0;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	//TODO - nothing??
}

