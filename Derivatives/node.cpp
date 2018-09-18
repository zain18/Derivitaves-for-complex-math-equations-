#include "node.h"

// Returns absolute value of an integer
int abs(int x)
{
    int y = x;
    if (x < 0)
    {
        y *= -1;
    }
    return y;
}

// Checks if character is a digit
bool IsDigit(char c)
{
    return ((c >= '0') && (c <= '9'));
}

// Constructor
Node::Node()
{
    coefficient = 1;
    numerator = 1;
    denominator = 1;
    exponent = 1;
    trigFunction = "";
    next = NULL;
}

// Constructor
Node::Node(std::string term)
{
    int i = 0;
    int sign = 1;
    // Default values
    trigFunction = "";
    coefficient = 1;
    numerator = 0;
    exponent = 0;

    // Check sign of coefficient
    if (term[i] == '-')
    {
        sign = -1;
        i++;
    }
    if (term[i] == ' ')
    {
        i++;
    }

    // Check if it is a fractional coefficient
    if (term[i] == '(')
    {
        // It is a fractional
        // Get numerator
        numerator = 0;
        i++;
        while (term[i] != '/')
        {
            if (IsDigit(term[i]))
            {
                numerator = numerator * 10 + (term[i] - 48);
            }
            i++;
        }
        numerator *= sign;
        i++;
        // Get denominator
        denominator = 0;
        while (term[i] != ')')
        {
            if (IsDigit(term[i]))
            {
                denominator = denominator * 10 + (term[i] - 48);
            }
            i++;
        }
        coefficient = 0;
        i++;
    }
    else // it is not a fractional
    {
        if (IsDigit(term[i]))
        {
            coefficient = 0;
            while (IsDigit(term[i]))
            {
                coefficient = coefficient * 10 + (term[i] - 48);
                i++;
            }
        }
        coefficient *= sign;
    }

    // Check if it is a polynom term with x variable
    if (term[i] == 'x')
    {
        i++;
        // Get exponent
        if (term[i] == '^')
        {
            i++;
            while (term[i] == ' ')
            {
                i++;
            }
            exponent = 0;
            sign = 1;
            // Check sign of exponent
            if (term[i] == '-')
            {
                sign = -1;
                i++;
            }
            while (IsDigit(term[i]))
            {
                exponent = exponent * 10 + (term[i] - 48);
                i++;
            }
            exponent *= sign;
        }
        else
        {
            // If no exponent after x then exponent is 1
            exponent = 1;
        }
    }
    // Check if it is a valid trigonometry function
    else if ((term[i] == 's') || (term[i] == 'c') || (term[i] == 't'))
    {
        // Copy trigonometry function
        while (i < term.length())
        {
            trigFunction += term[i];
            i++;
        }
        // Set exponent to lowest integer value for sorting purposes
        exponent = -2147483647;
    }
}

// Derivates a term
void Node::Derivate()
{
    int i;
    std::string function = "";
    std::string trigTerm = "";
    TRIG f = nil;

    // Check if it is a trigonometry function
    if (trigFunction == "")
    {
        // Derivate polinomial with fractional coefficient
        if (coefficient == 0)
        {
            numerator *= exponent;
            Simplify(); // Simplify new fractional
        }
        else
        {
            coefficient *= exponent;
        }
        // Decrement exponent
        if (exponent != 0)
        {
            exponent--;
        }
    }
    else
    {
        // Determine trigonometry function
        i = 0;
        while (trigFunction[i] == ' ')
        {
            i++;
        }
        while (trigFunction[i] != ' ')
        {
            function += trigFunction[i];
            i++;
        }
        if (function == "sin")
        {
            f = SIN;
        }
        else if (function == "cos")
        {
            f = COS;
        }
        else if (function == "tan")
        {
            f = TAN;
        }
        else if (function == "cot")
        {
            f = COT;
        }
        else if (function == "sec")
        {
            f = SEC;
        }
        else if (function == "csc")
        {
            f = CSC;
        }
        while (trigFunction[i] == ' ')
        {
            i++;
        }

        // Determine argument of trigonometry function
        while (i < trigFunction.length())
        {
            trigTerm += trigFunction[i];
            i++;
        }

        // Create node for the argument
        Node * trigNode = new Node(trigTerm);
        // If it is a fractional coefficient
        if (trigNode->coefficient == 0)
        {
            if (coefficient != 0)
            {
                numerator = coefficient;
                denominator = 1;
            }
            numerator *= trigNode->numerator;
            denominator *= trigNode->denominator;
        }
        else if ((coefficient == 0) && (numerator != 0))
        {
            // if the coefficient of trigonometry function is fractional
            numerator *= trigNode->coefficient;
        }
        else
        {
            coefficient *= trigNode->coefficient;
        }
        delete trigNode; //free memory

        // If it is a fractional, simplify it
        if (numerator != 0)
        {
            Simplify();
        }

        // Derive trigonometry function
        switch (f)
        {
            case SIN:
                trigFunction = "cos " + trigTerm;
                break;
            case COS:
                trigFunction = "sin " + trigTerm;
                coefficient *= -1;
                numerator *= -1;
                break;
            case TAN:
                trigFunction = "sec^2 " + trigTerm;
                break;
            case COT:
                trigFunction = "csc^2 " + trigTerm;
                coefficient *= -1;
                numerator *= -1;
                break;
            case SEC:
                trigFunction = "sec " + trigTerm + " tan " + trigTerm;
                break;
            case CSC:
                trigFunction = "csc " + trigTerm + " cot " + trigTerm;
                coefficient *= -1;
                numerator *= -1;
                break;
             default:
                 std::cout << "Trig function not recognized" << std::endl;
                break;
        }
    }
}

// Simplifies a fractional
void Node::Simplify()
{
    int n1 = abs(numerator);
    int n2 = abs(denominator);
    int n3;

    // Find GCD by Euclids algorithm
    while (n1 > 0)
    {
        n3 = n1;
        n1 = n2 % n1;
        n2 = n3;
    }

    // If denominator is negative, change sign of GCD
    if (denominator < 0)
    {
        n2 *= -1;
    }

    // Divide numerator and denominator by GCD
    numerator /= n2;
    denominator /= n2;

    // Check if it is still afractional
    if (denominator == 1)
    {
        // Not a fractional, set coefficient ot numerator
        coefficient = numerator;
        numerator = 0;
    }
}

// Derivates node and prints it
bool Node::Print(std::ofstream* o, bool sign)
{
    Derivate();
    // If coefficient is 0, then print nothing
    if ((coefficient == 0) && (numerator == 0))
    {
        return sign;
    }

    // Print sign if it is needed
    if (sign)
    {
        if ((coefficient != 0) || (numerator != 0))
        {
            if (coefficient == 0)
            {
                // Print sign of a fractional
                if (numerator > 0)
                {
                    *o << "+ ";
                }
                else
                {
                    *o << "- ";
                }
            }
            else
            {
                // Print sign of non fractional
                if (coefficient > 0)
                {
                    *o << "+ ";
                }
                else
                {
                    *o << "- ";
                }
            }
        }
    }
    // If coefficient is not 0 or not 1
    if ((coefficient != 0) && (abs(coefficient) != 1))
    {
        // Print sign if needed
        if ((!sign) && (coefficient < 0))
        {
            *o << "-";
        }
        *o << abs(coefficient);
    }
    else
    {
        // Print fractional coefficient
        if ((coefficient == 0) && (numerator != 0))
        {
            // Print sign if needed
            if ((!sign) && (numerator < 0))
            {
                *o << "-";
            }
            *o << "(" << abs(numerator) << "/" << abs(denominator) << ")";
        }
    }

    // Check if it is a trigometry function
    if (trigFunction == "")
    {
        // It is a polynom term
        // Check if exponent is 0
        if (exponent != 0)
        {
            // If exponent not 0 then print x
            *o << "x";
            // If exponent <> 1 then print exponent
            if (exponent != 1)
            {
                *o << "^" << exponent;
            }
        }
        else
        {
            // Exponent is 0, no x, print coefficient if it is 1 (if not 1 it is already printed)
            if (coefficient == 1)
            {
                *o << coefficient;
            }
        }
        *o << " ";
    }
    else
    {
        // print trigonometry function
        *o << trigFunction;
    }
    return true;
}

// Getters

// Get value of exponent
int Node::GetExponent()
{
    return exponent;
}

// Get trigonometry funcion
std::string Node::GetTrigFunction()
{
    return trigFunction;
}

// Get value of coefficient
int Node::GetCoefficient()
{
    return coefficient;
}

// Get value of numerator
int Node::GetNumerator()
{
    return numerator;
}

// Get value of denominator
int Node::GetDenominator()
{
    return denominator;
}

// Setters

// Set value of exponent
void Node::SetExponent(int e)
{
    exponent = e;
}

// Set value of coefficient
void Node::SetCoefficient(int c)
{
    coefficient = c;
}

// Set value of numerator
void Node::SetNumerator(int n)
{
    numerator = n;
}

// Set value of denominator
void Node::SetDenominator(int d)
{
    denominator = d;
}

// Set trigonometry function
void Node::SetTrigFunction(std::string t)
{
    trigFunction = t;
}
