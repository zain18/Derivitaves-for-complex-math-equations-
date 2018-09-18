//Name: Walid Zein


#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cctype>
#include "node.h"
#include "linkedlist.h"

using namespace std;


int main()
{
    ifstream ifile;
    char * line;
    string term;
    int i;
    char prevChar;
    LinkedList list;
    ofstream ofile;

    // Handle file functions.txt
    ifile.open("functions.txt");
    // Check if ifle is properly open
    if (!ifile.is_open())
    {
        cout << "Cant open file functions.txt" << endl;
        return 1;
    }
    line = new char[40]; // holds a line from file, supposed wont be longer than 40 characters
    // Open output file
    cout<<"The derivative of the equations is done, check Derive File"<<endl;
    ofile.open("derive.txt");
    while (!ifile.eof()) // Loop all lines from txt file
    {
        ifile.getline(line, 40); // take one line
        i = 0;
        // Empty the linked list of nodes
        Node * tmpNode = list.GetHead();
        list.Empty(tmpNode);

        // Get a term from line
        while (i < strlen(line))
        {
            term = "";
            prevChar = ' ';
            // Read line char by char and form term until there is a logical end of term (space or operation)
            while ((line[i] != '+') && (!((line[i] == '-') && ((IsDigit(prevChar)) || (prevChar == 'x')))) && (i < strlen(line)))
            {
                term += line[i];
                if (line[i] != ' ')
                {
                    prevChar = line[i];
                }
                i++;
            }
            // Check if it is an operation
            if (line[i] == '+')
            {
                i++;
            }
            if (line[i] == '-')
            {
                prevChar = ' ';
            }
            // Create new node from term
            Node * n = new Node(term);
            // Add node to list
            list.Add(list.GetHead(), n);
        }
        // Sort list
        list.Sort();
        // Print all nodes from list
        list.Print(list.GetHead(), false, &ofile);
        ofile << "\n";
    }
    // Close output file
    ofile.close();
    delete line; // free string from memory
    return 0;
}
