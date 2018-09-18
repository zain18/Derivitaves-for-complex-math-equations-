
#include "linkedlist.h"
#include "node.h"

// Constructor
LinkedList::LinkedList()
{
    head = NULL; // set head to NULL
}

// Constructor
LinkedList::LinkedList(Node* n)
{
    head = n; // Set head to node
}

// Destructor
LinkedList::~LinkedList()
{
    Empty(head); // Delete all nodes to free up memory
}

// Delete all nodes from list recursively
void LinkedList::Empty(Node *& n)
{
    if (n != NULL)
    {
        Empty(n->next);
        delete n;
        n = NULL;
    }
    head = NULL;
}

// Append node to end of list recursively
void LinkedList::Add(Node* n, Node* newNode)
{
    // If list is empty add node and set head
    if (n == NULL)
    {
        n = newNode;
        n->next = NULL;
        head = n;
    }
    else
    {
        // If it is a last node in list append node to it
        if (n->next == NULL)
        {
            n->next = newNode;
            n->next->next = NULL;
        }
        else
        {
            // If there are more elements in list call add recursively
            Add(n->next, newNode);
        }
    }
}

// Return next element from list if exist
Node * LinkedList::Next(Node* n)
{
    // Check if element exist
    if (n != NULL)
    {
        return n->next;
    }
    else
    {
        // If element not exist, return head
        return head;
    }
}

// Sorts linked list using bubble sort
void LinkedList::Sort()
{
    bool sorted = false;
    Node * n;
    int tmp;

    // Loop until there is no swap in list after iteration
    while (!sorted)
    {
        sorted = true;
        n = head;
        std::string s;
        // Iterate list
        while (n != NULL)
        {
            // Ifthere is a next element
            if (n->next != NULL)
            {
                //compare exponents
                if (n->GetExponent() < n->next->GetExponent())
                {
                    // if next exponent is greater or or current is trig function and next is not then swap
                    tmp = n->GetCoefficient();
                    n->SetCoefficient(n->next->GetCoefficient());
                    n->next->SetCoefficient(tmp);
                    tmp = n->GetNumerator();
                    n->SetNumerator(n->next->GetNumerator());
                    n->next->SetNumerator(tmp);
                    tmp = n->GetDenominator();
                    n->SetDenominator(n->next->GetDenominator());
                    n->next->SetDenominator(tmp);
                    tmp = n->GetExponent();
                    n->SetExponent(n->next->GetExponent());
                    n->next->SetExponent(tmp);
                    s = n->GetTrigFunction();
                    n->SetTrigFunction(n->next->GetTrigFunction());
                    n->next->SetTrigFunction(s);
                    sorted = false; // set flag to false
                }
            }
            n = n->next; // move to next node
        }
    }
}

// Print all nodes from list recursively
void LinkedList::Print(Node* n, bool sign, std::ofstream  * os)
{
    bool s;
    if (n != NULL)
    {
        // Print node with sign if needed
        s = n->Print(os, sign);
        // Recursive call to print next node
        Print(n->next, s, os);
    }
}

// Returns head of list
Node * LinkedList::GetHead()
{
    return head;
}
