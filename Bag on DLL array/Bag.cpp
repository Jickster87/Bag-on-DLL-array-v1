#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>

Bag::Bag() {
	nodes = new DLLANode[capacity];
    //init array
    for (int i = 0; i < capacity; ++i) {
        nodes[i].elem = NULL_TELEM; // or any default value you want to initialize with
        if (i < capacity - 1) {
            nodes[i].next = i + 1;
        } else {
            nodes[i].next = -1; // last node, so next points to nullptr
        }
        if (i > 0) {
            nodes[i].prev = i - 1;
        } else {
            nodes[i].prev = -1; // first node, so prev points to nullptr
        }
    }
	head = tail = -1;
	firstEmpty = 0;
	sizeBag = 0;
}


void Bag::add(TElem elem) {
    int newElem = allocate(nodes);
    
    // resize
    if (newElem == -1) {
        resize(nodes);
        newElem = allocate(nodes);
    }
    // add elem on alloc node
    nodes[newElem].elem = elem;

    if (tail != -1) 
    {
        nodes[tail].next = newElem;
        nodes[newElem].prev = tail;
    }
    else
    {
        head = newElem;
    }
    tail = newElem;

    sizeBag++;
}


bool Bag::remove(TElem elem) {

    int current = head;
    while (current != -1 && nodes[current].elem != elem) {
        current = nodes[current].next;
    }

    if (current == -1)
    {
        return false;
    }
    
    // Adjust pointers if necessary
    if (current == head) {
        head = nodes[current].next;
    } else {
        nodes[nodes[current].prev].next = nodes[current].next;
    }
    if (current == tail) {
        tail = nodes[current].prev;
    } else {
        nodes[nodes[current].next].prev = nodes[current].prev;
    }

    // Mark the node as empty using the free() function
    free(nodes, current);

    // Decrement sizeBag
    sizeBag--;
    
    return true;
}

void Bag::resize(DLLANode *nodes) {
    int newCapacity = capacity * 2;
    DLLANode* newNodes = new DLLANode[newCapacity];

    //init newNodes
    for (int i = 0; i < capacity; ++i) {
        newNodes[i].elem = NULL_TELEM; // or any default value you want to initialize with
        if (i < capacity - 1) {
            newNodes[i].next = i + 1;
        }
        else {
            newNodes[i].next = -1; // last node, so next points to nullptr
        }
        if (i > 0) {
            newNodes[i].prev = i - 1;
        }
        else {
            newNodes[i].prev = -1; // first node, so prev points to nullptr
        }
    }

    //copy existing nodes
    for (int i=0; i < capacity; i++) {
        newNodes[i] = nodes[i];
    }

    // update stuff
    head = tail = -1;
    firstEmpty = capacity;
    sizeBag = capacity;

    // *cheat gpt
    for (int i = capacity; i < newCapacity; i++) {
        if (i == newCapacity - 1) {
            // If it's the last node in the new array, set next to -1 (nullptr)
            newNodes[i].next = -1;
        }
        else {
            // Otherwise, set next to the index of the next node
            newNodes[i].next = i + 1;
        }
    }

    delete [] nodes;
    nodes = newNodes;
    capacity = newCapacity;
}

int Bag::allocate(DLLANode* nodes) {
    int newElem = firstEmpty;
    if (newElem != -1) {
        firstEmpty = nodes[firstEmpty].next;
        if (firstEmpty != -1) {
            nodes[firstEmpty].prev = -1;
        }
        nodes[newElem].next = -1;
        nodes[newElem].prev = -1;
    }
    return newElem;
}

void Bag::free(DLLANode* nodes, int pos){
    nodes[pos].next = firstEmpty;
    nodes[pos].prev = -1;
    if ((firstEmpty == -1)) {
        nodes[firstEmpty].prev = pos;
    }
    firstEmpty = pos;
}


bool Bag::search(TElem elem) const {
    int current = head;
    while (current != -1 && nodes[current].elem != elem) {
        current = nodes[current].next;
    }
    if (current != -1) {
        return true;
    }
    else {
        return false;
    }
}

int Bag::nrOccurrences(TElem elem) const {
    int count = 0;
    int current = head;
    while (current != -1) {
        if (nodes[current].elem == elem) {
            count++;
        }
        current = nodes[current].next;
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
    delete [] nodes;
}
