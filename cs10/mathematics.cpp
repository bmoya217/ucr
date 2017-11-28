#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main () 
{
    // defines variables
    string mathType;
    double num1, num2, num3;
    
    // asks for operation type
    cout << "Please choose an operation: ";
    cin >> mathType;
    cout << endl;
    
    if (mathType == "sqrt" || mathType == "addition" || mathType == 
    "subtraction" || mathType == "multiplication" || mathType == "division" ||
    mathType == "pythagorean" || mathType == "fabs" || mathType == "quadratic")
    {
        cout << "Enter your first number: ";
        cin >> num1;
        cout << endl;
    }
    
    if (mathType == "fabs")
    {
        // fabs output
        cout << "Equation: fabs(" << num1 << ")";
        cout << "\nResult: " << fabs(num1);
    }
    
    else if (mathType == "sqrt")
    {
        // sqrt output
        cout << "Equation: sqrt(" << num1 << ")";
        
        if (num1>=0)
        {
            cout << "\nResult: " << sqrt(num1);
        }
            
        else if (num1<0)
        {
            cout << endl;
            cout << "Error: Cannot take square root of a negative number.";
        }
    }
    
    else if (mathType == "addition" || mathType == "subtraction" || mathType == 
    "multiplication" || mathType == "division" || mathType == "pythagorean" ||
    mathType == "quadratic")
    {
        cout << "Enter your second number: ";
        cin >> num2;
        cout << endl;
        
        if (mathType == "addition")
        {
            // addition output
            cout << "Equation: " << num1 << " + " << num2;
            cout << "\nResult: " << num1 + num2;
        }
        
        else if (mathType == "subtraction")
        {
            // subtraction output
            cout << "Equation: " << num1 << " - " << num2;
            cout << "\nResult: " << num1 - num2;
            
        }
        
        else if (mathType == "multiplication")
        {
            // multiplication output
            cout << "Equation: " << num1 << " * " << num2;
            cout << "\nResult: " << num1 * num2;
        }
        
        else if (mathType == "division")
        {
            // division output
            cout << "Equation: " << num1 << " / " << num2;
            cout << endl;
            
            if (num2 != 0)
            {
                cout << "\nResult: " << num1 / num2;
            }
            
            else if (num2 == 0)
            {
                cout << "\nError: Cannot divide by zero.";
            }
        }
        
        else if (mathType == "pythagorean")
        {
            // pytagorean output
            cout << "Equation: " << "sqrt(" << num1 << "^2 + " << num2 << "^2)";
            cout << "\nResult: " << sqrt(pow(num1,2)+pow(num2,2));
        }
        
        else if (mathType == "quadratic")
        {
            cout << "Enter your third number: ";
            cin >> num3;
            cout << endl;
            
            // quadratic output
            cout << "Equation: " << num1 << "x^2 + " << num2 << "x + ";
            cout << num3 << " = 0" << endl;
            
            if (num1 == 0 && (pow(num2,2)-(4*num1*num3)) < 0)
            {
                cout << "Error: Cannot divide by zero and cannot take square";
                cout << " root of a negative number.";
            }
            
            else if ((pow(num2,2)-(4*num1*num3)) < 0)
            {
                cout << "Error: Cannot take square root of a negative";
                cout << " number.";
            }
             
            else if (num1 == 0)
            {
                cout << "Error: Cannot divide by zero.";
            }
            
            else if (((0 - num2 - sqrt(pow(num2,2)-(4*num1*num3)))/(2*num1)
            == 0) && ((0 - num2 + sqrt(pow(num2,2)-(4*num1*num3)))/(2*num1)
            == 0))
            {
                cout << "Result: 0";
            }
            
            else
            {
                cout << "Result: ";
                cout << (0 -num2-sqrt(pow(num2,2)-(4*num1*num3)))/(2*num1);
                cout << ", ";
                cout << (0 -num2+sqrt(pow(num2,2)-(4*num1*num3)))/(2*num1);                
            }
        }
    }
    
    else
    {
        cout << "Error: Operation not supported.";
    }
    cout << "\n";
    
    return 0;
}