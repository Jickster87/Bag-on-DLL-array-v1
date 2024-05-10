#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>

Bag::Bag() {
	//capacity = INIT_CAPACITY;
	nodes = new DLLANode[capacity];
    
    //init array
    for (int i = 0; i < capacity; ++i) {
        nodes[i].elem = 0; // or any default value you want to initialize with
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
    int pos = firstEmpty;
    if (pos < 1 or pos > sizeBag + 1) {
       // throw exception();
    }
    
    int newElem = allocate(nodes); //1st case should allocate [0]
    
    // if the array is full resize
    if (newElem == -1) {
        resize(nodes);
        newElem = allocate(nodes);
    }
    
    nodes[newElem].elem = elem;

    // if this is the first element inserted
    if (pos == 0) {
        //
        if (head == -1) {
            head = newElem;
            tail = newElem;
        }
        else {
            nodes[newElem].next = head;
            nodes[head].prev = newElem;
            head = newElem;
        }
    }
    // if it's not the first element inserted
    else {
        int nodC = head;
        int posC = 1;
        while (nodC != -1 and posC < pos - 1) {
            nodC = nodes[nodC].next;
            posC = posC + 1;
        }
        if (nodC != -1) {
            int nodNext = nodes[nodC].next;
            nodes[newElem].next = nodNext;
            nodes[newElem].prev = nodC;
            nodes[nodC].next = newElem;
            if (nodNext == -1) {
                tail = newElem;
            }
            else {
                nodes[nodNext].prev = newElem;
            }
        }
    }
    sizeBag++;
}


bool Bag::remove(TElem elem) {
    // Check if the element exists in the bag
    if (!search(elem)) {
        return false;
    }
    
    // Find the position of the element in the bag
    int current = head;
    while (current != -1 && nodes[current].elem != elem) {
        current = nodes[current].next;
    }
    
    // Mark the node as empty using the free() function
    free(nodes, current);
    
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
    
    // Decrement sizeBag
    sizeBag--;
    
    return true;
}

void Bag::resize(DLLANode *nodes) {
    int newCapacity = capacity * 2;
    DLLANode* newNodes = new DLLANode[newCapacity];
    int i;
    for (i=0; i < capacity; i++) {
        newNodes[i] = nodes[i];
    }
    for (i = capacity; i < newCapacity; i++) {
            newNodes[i].next = -1; // Initialize next pointers for new nodes
        }
    delete [] nodes;
    nodes = newNodes;
    firstEmpty = capacity + 1;
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
    if ((firstEmpty = -1)) {
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
