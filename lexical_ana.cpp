#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

string removeComments(string input) {
    string output;
    bool inSingleLineComment = false;
    bool inMultiLineComment = false;
    for (size_t i = 0; i < input.size(); ++i) {
        if (inSingleLineComment) {
            if (input[i] == '\n') {
                inSingleLineComment = false;
                output += input[i];
            }
        } else if (inMultiLineComment) {
            if (input[i] == '*' && i + 1 < input.size() && input[i+1] == '/') {
                inMultiLineComment = false;
                ++i;
            }
        } else {
            if (input[i] == '/' && i + 1 < input.size() && input[i+1] == '/') {
                inSingleLineComment = true;
                ++i;
            } else if (input[i] == '/' && i + 1 < input.size() && input[i+1] == '*') {
                inMultiLineComment = true;
                ++i;
            } else {
                output += input[i];
            }
        }
    }
    return output;
}

string extra_space_rem(string code_line){
    string res="";
    for(int i=0;i<code_line.size()-1;i++){
        while((code_line[i]==' ' && code_line[i+1]==' ')|| code_line[i]=='\t' || code_line[i]=='\n'){
            i++;
        }
        string a;
        a=code_line[i];
        res.append(a);
    }
    return res;
}



bool isDelimiter(char ch) {
    vector<char> delimiters = {'(', ')', '{', '}', '[', ']', ';', ','};
    return find(delimiters.begin(), delimiters.end(), ch) != delimiters.end();
}

bool isOperator(char ch) {
    vector<string> operators = {"+", "-", "*", "/", "%", "=", "==", "<", ">", "<=", ">=", "!="};
    string op = "";
    op += ch;
    if (find(operators.begin(), operators.end(), op) != operators.end()) {
        return true;
    }
    if (ch == '&' || ch == '|') {
        return true;
    }
    return false;
}

bool isKeyword(string str) {
    vector<string> keywords = {"auto","then", "break", "case", "char", "const", "continue", "default", "do", "double","else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while","print","endif"};
    return find(keywords.begin(), keywords.end(), str) != keywords.end();
}

bool isNumericConstant(string str) {
    if (str.empty()) {
        return false;
    }
    for (char ch : str) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}

bool isFloatConstant(string str) {
    if (str.empty()) {
        return false;
    }
    int dotCount = 0;
    for (char ch : str) {
        if (!isdigit(ch)) {
            if (ch == '.') {
                dotCount++;
            } else {
                return false;
            }
        }
    }
    return dotCount == 1;
}

bool isConstant(string str){
    if(isFloatConstant(str)||isNumericConstant(str)){
        return true;
    }
    return false;
}

bool isIdentifier(string str) {
    if (str.empty()) {
        return false;
    }
    if (isdigit(str[0])) {
        return false;
    }
    for (char ch : str) {
        if (!isalnum(ch) && ch != '_') {
            return false;
        }
    }
    return true;
}


int main() {

    ifstream inputFile("input.cpp");
    if (!inputFile) {
        cerr << "Failed to open file" << endl;
        return 1;
    }

    string inputString((istreambuf_iterator<char>(inputFile)), (istreambuf_iterator<char>()));

    string code = removeComments(inputString);
    code = extra_space_rem(code);

    vector<string> keywords;
    vector<string> identifiers;
    vector<string> delimiters;
    vector<string> constants;
    vector<string> operators;

    string currentToken;

  
    for (size_t i = 0; i < code.size(); ++i) {
        char ch = code[i];

      
        if (isDelimiter(ch)) {
            if (!currentToken.empty()) {
                if (isKeyword(currentToken)) {
                    keywords.push_back(currentToken);
                } else if (isConstant(currentToken)) {
                    constants.push_back(currentToken);
                } else {
                    identifiers.push_back(currentToken);
                }
                currentToken.clear();
            }
            string delimiter(1, ch);
            delimiters.push_back(delimiter);
        }

     
        else if (isOperator(ch)) {
            if (!currentToken.empty()) {
                if (isKeyword(currentToken)) {
                    keywords.push_back(currentToken);
                } else if (isConstant(currentToken)) {
                    constants.push_back(currentToken);
                } else {
                    identifiers.push_back(currentToken);
                }
                currentToken.clear();
            }
            string op(1, ch);

          
            if (ch == '=' || ch == '!' || ch == '<' || ch == '>') {
                if (i + 1 < code.size() && code[i+1] == '=') {
                    op += '=';
                    ++i;
                }
            }

         
            if (ch == '&' || ch == '*') {
                if (i + 1 < code.size() && code[i+1] == ch) {
                    op += ch;
                    ++i;
                }
            }

            operators.push_back(op);
        }

    
        else if (isspace(ch)) {
            if (!currentToken.empty()) {
                if (isKeyword(currentToken)) {
                    keywords.push_back(currentToken);
                } else if (isConstant(currentToken)) {
                    constants.push_back(currentToken);
                } else {
                    identifiers.push_back(currentToken);
                }
                currentToken.clear();
            }
        }

   
        else {
            currentToken += ch;
        }
    }

  
    cout << "Keywords:" << endl;
    for (auto keyword : keywords) {
        cout << keyword <<" ";
    }
    cout << endl;

    cout << "Identifiers:" << endl;
    for (auto identifier : identifiers) {
        cout << identifier<<" ";
    }
    cout << endl;

    cout << "Constants:" << endl;
    for (auto constant : constants) {
        cout << constant <<" ";
    }
    cout << endl;

    cout << "Operators:" << endl;
    for (auto op : operators) {
        cout << op <<" ";
    }
    cout << endl;

    cout << "Delimiters:"<<endl;
    for(auto dl:delimiters){
        cout<<dl<<" ";
    }
    cout<<endl;
}