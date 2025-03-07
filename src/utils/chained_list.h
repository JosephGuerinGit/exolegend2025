#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include "gladiator.h"  // Assuming you have this file for the MazeSquare definition

// Node structure for the linked list
struct Node {
    MazeSquare* square;  // Pointer to MazeSquare
    Node* next;  // Pointer to the next node in the chain

    Node(MazeSquare* square) : square(square), next(nullptr) {}
};

// LinkedList class for managing a list of MazeSquare objects
class LinkedList {
public:
    Node* head;  // Head of the linked list

    LinkedList();  // Constructor to initialize the list

    // Add a MazeSquare to the end of the list
    void push_back(MazeSquare* square);

    // Print all MazeSquare elements in the list
    void printList() const;

    // Get the first MazeSquare element of the list
    MazeSquare* getFirst() const;

    // Get the last MazeSquare element of the list
    MazeSquare* getLast() const;

    // Reverse the order of the list
    void reverseList();

    // Destructor to free dynamically allocated memory
    ~LinkedList();
};

#endif  // LINKED_LIST_H
