#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>

Bag::Bag() {
    capacity = 20;
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
  
    // resize
    if (firstEmpty == -1) {
        resize();
    }

    int newElem = allocate();
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
    nodes[newElem].next = -1;

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
    free(current);

    // Decrement sizeBag
    sizeBag--;
    
    return true;
}

void Bag::resize() {

    int newCapacity = capacity * 2;
    DLLANode* newNodes = new DLLANode[newCapacity];

    //copy existing nodes
    for (int i = 0; i < capacity; i++) {
        newNodes[i] = nodes[i];
    }

    //LAST ISSUE WAS THIS FOR LOOP  (THIS IS CORRECT)
    for (int i = capacity; i < newCapacity; i++) 
        {
            newNodes[i].elem = NULL_TELEM;
            newNodes[i].next = i + 1;
            newNodes[i].prev = i - 1;
        }

    // THIS LOOP BELOW IS WRONG !!!
    // 
    //for (int i = capacity; i < newCapacity; i++) {
    //    newNodes[i].elem = NULL_TELEM; 
    //    if (i < capacity - 1) {
    //        newNodes[i].next = i + 1;
    //    }
    //    else {
    //        newNodes[i].next = -1;
    //    }
    //    if (i > capacity) {
    //        newNodes[i].prev = i - 1;
    //    }
    //    else {
    //        newNodes[i].prev = -1; 
    //    }
    //}
    

    newNodes[newCapacity - 1].next = -1;

    // update stuff
    delete [] nodes;
    nodes = newNodes;
    firstEmpty = capacity;
    capacity = newCapacity;
}

int Bag::allocate() {
    int newElem = firstEmpty; // get index of empty slot

    // if there's a slot
    if (newElem != -1) {
        //update firstEmpty to point to new empty slot, as this one just got ocupied
        firstEmpty = nodes[firstEmpty].next;

        if (firstEmpty != -1) {
            nodes[firstEmpty].prev = -1; 
}
        nodes[newElem].next = -1;
        nodes[newElem].prev = -1;
    }
    return newElem;
}

void Bag::free(int pos){
    nodes[pos].next = firstEmpty;
    nodes[pos].prev = -1;
    if (firstEmpty == -1) {
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
