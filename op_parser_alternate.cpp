#include <iostream>
#include <string>
using namespace std;

const int precedence[][2] = {
  { 0, 0 }, // ' '
  { 1, 1 }, // +
  { 1, 1 }, // -
  { 2, 2 }, // *
  { 2, 2 }, // /
};

char stack[100];
int top = -1;

void push(char op) {
  stack[++top] = op;
}

char pop() {
  return stack[top--];
}

int get_precedence(char op) {
  return precedence[op - ' '][0];
}

int parse(string expression) {
  for (int i = 0; i < expression.length(); i++) {
    char c = expression[i];
    if (c == '(') {
      push(c);
    } else if (c == ')') {
      
      while (stack[top] != '(') {
        char op = pop();
        cout << op;
      }

      pop();
    } else {

      while (top >= 0 && get_precedence(stack[top]) >= 2) {
        char op = pop();
        cout << op;
      }
      cout << c;
    }
  }

  while (top >= 0) {
    char op = pop();
    cout << op;
  }

  return 0;
}

int main() {
  string expression = "(i*i)+(i*i)+i";
  parse(expression);
  return 0;
}