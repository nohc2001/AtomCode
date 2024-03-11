#include <iostream>
#include <fstream>
using namespace std;

constexpr char filename[256] = "data_example.txt";

int main(){
    ifstream rs;
    rs.open(filename);
    int opbitN = 0;
    rs >> opbitN;
    string* ops = new string[opbitN];
    for(int i=0;i<opbitN;++i){
        rs >> ops[i];
    }

    
    return 0;
}