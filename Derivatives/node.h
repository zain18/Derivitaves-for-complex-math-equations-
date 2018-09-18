#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <fstream>
#include <string>

enum TRIG {SIN, COS, TAN, COT, SEC, CSC, nil};

bool IsDigit(char c);

class Node
{
private:
    int coefficient;
    int numerator;
    int denominator;
    int exponent;
    std::string trigFunction;

public:
    Node * next;
    Node();
    Node(std::string);
    void Derivate(); //Derivates node and holds the result in same node, can be private member
    void Simplify(); // Simplifies a fractional
    bool Print(std::ofstream * o, bool sign); // Derivates and prints the term

    // getters
    int GetExponent();
    int GetCoefficient();
    int GetNumerator();
    int GetDenominator();
    std::string GetTrigFunction();

    // setters
    void SetExponent(int e);
    void SetCoefficient(int c);
    void SetNumerator(int n);
    void SetDenominator(int d);
    void SetTrigFunction(std::string t);
};



#endif /* NODE_H */
