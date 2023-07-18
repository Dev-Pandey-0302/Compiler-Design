#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;


bool findComments(string input) {
    
    bool inSingleLineComment = false;
    bool inMultiLineComment = false;
    for (size_t i = 0; i < input.size(); ++i) {
        
        if (input[i] == '/' && i + 1 < input.size() && input[i+1] == '/') {
            inSingleLineComment = true;
            ++i;
        } else if (input[i] == '/' && i + 1 < input.size() && input[i+1] == '*') {
            inMultiLineComment = true;
            ++i;
        } 
    }
    
    return (inSingleLineComment || inMultiLineComment);
}


int main(){
    vector<string> str={"Comment here//hi","Comment not here","Comment /*here*/ is"};
    for(int i=0;i<3;i++){
        

        if(findComments(str[i])){
            cout<<"Comment present"<<endl;
        }
        else{
            cout<<"Comment absent"<<endl;
        }
    }
    return 0;
}