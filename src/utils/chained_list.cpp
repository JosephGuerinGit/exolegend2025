#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include "gladiator.h"  // Assuming you have this file for the MazeSquare definition
#include "chained_list.h"
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

    LinkedList() : head(nullptr) {}  // Constructor to initialize the list

    // Add a MazeSquare to the end of the list
    void push_back(MazeSquare* square) {
        Node* newNode = new Node(square);  // Create a new node
        if (!head) {
            head = newNode;  // If list is empty, make the new node the head
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;  // Traverse to the end of the list
            }
            current->next = newNode;  // Add the new node at the end
        }
    }

    // Print all MazeSquare elements in the list
    void printList() {
        Node* current = head;
        while (current) {
            std::cout << "MazeSquare (" << current->square->i << ", " << current->square->j << ")\n";
            current = current->next;
        }
    }

    // Get the first MazeSquare element of the list
    MazeSquare* getFirst() const {
        return (head != nullptr) ? head->square : nullptr;
    }

    // Get the last MazeSquare element of the list
    MazeSquare* getLast() const {
        if (head == nullptr) return nullptr;

        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        return current->square;
    }

    // Reverse the order of the list
    void reverseList() {
        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;  // Set head to the last node, which is now the first
    }

    // Destructor to free dynamically allocated memory
    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            delete current->square;  // Free the MazeSquare object
            delete current;  // Free the Node object
            current = nextNode;
        }
    }
};

#endif  // LINKED_LIST_H