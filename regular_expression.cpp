#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


vector<string> linemaker(string input){
    vector<string> output;
    string res="";
    for(size_t i = 0; i < input.size(); ++i){
        
        if(input[i]!='\n'){
            res=res+input[i];
        }
        else{
            output.push_back(res);
            res="";
        }
    }
    return output;
}


bool checker(string a){
    int s=a.size();
    
    for(int i=0;i<s;i++){
        
        if(a[i]=='a'){
            continue;
        }
        else if(a[i]=='b'){
            for(int j=i;j<s;j++){
                if(a[j]=='a'){
                    return false;
                }

            }
            return true;
        }
    }
    return false;
    
}

int main(){
    ifstream inputFile("input.cpp");
    if (!inputFile) {
        cerr << "Failed to open file" << endl;
        return 1;
    }

    string inputString((istreambuf_iterator<char>(inputFile)), (istreambuf_iterator<char>()));
    
    vector<string> file_values=linemaker(inputString);

    for(int i=0;i<file_values.size();i++){
        cout<<file_values[i];
        if(checker(file_values[i])){
            cout<<" Accepted!"<<endl;
        }
        else{
            cout<<" Rejected!"<<endl;
        }
    }
    return 0;

}
