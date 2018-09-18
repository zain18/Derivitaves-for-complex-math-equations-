#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

class LinkedList
{
private:
    Node * head; // head of linked list

public:
    LinkedList();
    LinkedList(Node * n);
    ~LinkedList();
    void Empty(Node *& n); // deletes all nodes from list
    void Add(Node * n, Node * newNode); // appends a new node to list
    Node * Next(Node * n); // points to next node in list
    void Sort(); // Sorts the list
    void Print(Node * n, bool sign, std::ofstream * os); // prints all nodes from list
    Node * GetHead(); // return head of list
};


#endif /* LINKEDLIST_H */

