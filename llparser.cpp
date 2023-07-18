#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Function to check if a character is a terminal symbol
bool isTerminal(char ch) {
    // Define your terminal symbols here
    return (ch == 'i');
}

// Function to perform parsing
bool parseE(string input, int& index);
bool parseT(string input, int& index);
bool parseF(string input, int& index);

bool parseF(string input, int& index) {
    char currentSymbol = input[index];

    if (currentSymbol == '(') {
        index++;
        if (parseE(input, index)) {
            if (input[index] == ')') {
                index++;
                return true;
            }
        }
        return false;
    } else if (isTerminal(currentSymbol)) {
        index++;
        return true;
    } else {
        return false;
    }
}

bool parseT(string input, int& index) {
    if (parseF(input, index)) {
        if (input[index] == '+') {
            index++;
            if (parseT(input, index)) {
                return true;
            }
        } else {
            return true;
        }
    }
    return false;
}

bool parseE(string input, int& index) {
    if (parseT(input, index)) {
        if (input[index] == '*') {
            index++;
            if (parseE(input, index)) {
                return true;
            }
        } else {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream inputFile("input.cpp");
    if (!inputFile) {
        cerr << "Failed to open file" << endl;
        return 1;
    }
    string input((istreambuf_iterator<char>(inputFile)), (istreambuf_iterator<char>()));
    cout<<"Input from file-> "<<endl;
    cout<<input<<endl;
    
    input += "$";  // Add end marker
    
    int index = 0;
    bool success = parseE(input, index);
    
    if (success && index == input.length() - 1) {
        cout<<"Input string is valid!"<<endl;
    } else {
        cout<<"Input string is invalid!"<<endl;
    }
    return 0;
}
