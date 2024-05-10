#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
    currentElem = bag.head;
}

void BagIterator::first() {
    currentElem = bag.head;
}


void BagIterator::next() {
	if(!valid()) {
		throw exception();
	}
    currentElem = bag.nodes[currentElem].next;

}

bool BagIterator::valid() const {
	return currentElem != -1;
}


TElem BagIterator::getCurrent() const
{
	if (currentElem == -1)
	{
		throw exception();
	}
	return bag.nodes[currentElem].elem;
}
