#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	currentPosition = bag.head;
}

void BagIterator::first() {
	currentPosition = bag.head;
}


void BagIterator::next() {
	if(!valid()) {
		throw exception();
	}
	this->currentPosition = bag.next[currentPosition];
}


bool BagIterator::valid() const {
	return currentPosition != -1;
}



TElem BagIterator::getCurrent() const
{
	if (!valid())
	{
		throw exception();
	}
	return bag.elems[currentPosition];
}
