#include <iostream>
#include <stack>
#include <string>
#include <fstream>
using namespace std;

int calculateExpression(const string& expression) {
    stack<int> numbers;
    stack<char> operators;
    string buffer; 

    for (char ch : expression) {
        if (ch == ' ') {
            continue; 
        } else if (isdigit(ch)) {
            buffer += ch; 
        } else {
            if (!buffer.empty()) {
                numbers.push(stoi(buffer));  
                buffer.clear(); 
            }
            if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                
                while (!operators.empty() && (operators.top() == '*' || operators.top() == '/')) {
                    int b = numbers.top();
                    numbers.pop();
                    int a = numbers.top();
                    numbers.pop();
                    char op = operators.top();
                    operators.pop();

                    if (op == '*') {
                        int result = a * b;
                        numbers.push(result);
                        cout << a << " * " << b << " = " << result << endl;
                    } else if (op == '/') {
                        int result = a / b;
                        numbers.push(result);
                        cout << a << " / " << b << " = " << result << endl;
                    }
                }
                operators.push(ch);
            }
        }
    }

    if (!buffer.empty()) {
        numbers.push(stoi(buffer));  
    }

    while (!operators.empty()) {
        int b = numbers.top();
        numbers.pop();
        int a = numbers.top();
        numbers.pop();
        char op = operators.top();
        operators.pop();

        if (op == '+') {
            int result = a + b;
            numbers.push(result);
            cout << a << " + " << b << " = " << result << endl;
        } else if (op == '-') {
            int result = a - b;
            numbers.push(result);
            cout << a << " - " << b << " = " << result << endl;
        } else if (op == '*') {
            int result = a * b;
            numbers.push(result);
            cout << a << " * " << b << " = " << result << endl;
        } else if (op == '/') {
            int result = a / b;
            numbers.push(result);
            cout << a << " / " << b << " = " << result << endl;
        }
    }

    return numbers.top();
}

int main() {
    ifstream inputFile("input.cpp");
    if (!inputFile) {
        cerr << "Failed to open file" << endl;
        return 1;
    }

    string input((istreambuf_iterator<char>(inputFile)), (istreambuf_iterator<char>()));
    int result = calculateExpression(input);
    cout << "Result: " << result << endl;
    return 0;
}