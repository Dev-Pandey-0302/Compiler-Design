#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

// Function to check if a character is an operator
bool isOperator(char ch) {
    return ch == '+' || ch == '*' || ch == '(' || ch == ')';
}

// Function to get the precedence of an operator
int getPrecedence(char op) {
    if (op == '*')
        return 2;
    else if (op == '+')
        return 1;
    else
        return 0;
}

// Function to evaluate the expression using operator precedence parsing
int evaluateExpression(const string& expression) {
    stack<int> values;
    stack<char> operators;
    unordered_map<char, int> precedences;

    precedences['+'] = 1;
    precedences['*'] = 2;

    for (char ch : expression) {
        if (isspace(ch))
            continue;

        if (ch == '(') {
            operators.push(ch);
        } else if (isdigit(ch)) {
            int num = 0;
            while (isdigit(ch)) {
                num = num * 10 + (ch - '0');
                ch = expression[++i];
            }
            values.push(num);
        } else if (isOperator(ch)) {
            while (!operators.empty() && operators.top() != '(' &&
                   precedences[operators.top()] >= precedences[ch]) {
                int b = values.top();
                values.pop();
                int a = values.top();
                values.pop();

                char op = operators.top();
                operators.pop();

                int result;
                if (op == '+')
                    result = a + b;
                else if (op == '*')
                    result = a * b;

                values.push(result);
            }

            if (ch == ')') {
                operators.pop();
            } else {
                operators.push(ch);
            }
        }
    }

    while (!operators.empty()) {
        int b = values.top();
        values.pop();
        int a = values.top();
        values.pop();

        char op = operators.top();
        operators.pop();

        int result;
        if (op == '+')
            result = a + b;
        else if (op == '*')
            result = a * b;

        values.push(result);
    }

    return values.top();
}

int main() {
    string expression;
    cout << "Enter an expression: ";
    getline(cin, expression);

    int result = evaluateExpression(expression);
    cout << "Result: " << result << endl;

    return 0;
}