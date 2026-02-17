#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double num1, num2;
    char operation;
    double result;
    
    cout << "=== Simple Calculator ===" << endl;
    cout << "Enter first number: ";
    cin >> num1;
    
    cout << "Enter second number: ";
    cin >> num2;
    
    cout << "\nChoose operation:" << endl;
    cout << "1. Addition (+)" << endl;
    cout << "2. Subtraction (-)" << endl;
    cout << "3. Multiplication (*)" << endl;
    cout << "4. Division (/)" << endl;
    cout << "Enter your choice (+, -, *, /): ";
    cin >> operation;
    
    switch(operation) {
        case '+':
            result = num1 + num2;
            cout << fixed << setprecision(2);
            cout << num1 << " + " << num2 << " = " << result << endl;
            break;
            
        case '-':
            result = num1 - num2;
            cout << fixed << setprecision(2);
            cout << num1 << " - " << num2 << " = " << result << endl;
            break;
            
        case '*':
            result = num1 * num2;
            cout << fixed << setprecision(2);
            cout << num1 << " * " << num2 << " = " << result << endl;
            break;
            
        case '/':
            if(num2 != 0) {
                result = num1 / num2;
                cout << fixed << setprecision(2);
                cout << num1 << " / " << num2 << " = " << result << endl;
            } else {
                cout << "Error: Division by zero is not allowed!" << endl;
            }
            break;
            
        default:
            cout << "Error: Invalid operation! Please use +, -, *, or /" << endl;
            break;
    }
    
    cout << "\nThank you for using the calculator!" << endl;
    return 0;
}
