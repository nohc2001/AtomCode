#include <iostream>
#include <fstream>
using namespace std;

constexpr char filename[256] = "data_example.txt";
constexpr char outfile[256] = "ifout.txt";

struct ifStruct{
    string* opvalues;
    string comment;
};

int main(){
    ifstream rs;
    rs.open(filename);
    int opbitN = 0;
    rs >> opbitN;
    int linenum = 0;
    rs >> linenum;
    string* ops = new string[opbitN];
    for(int i=0;i<opbitN;++i){
        rs >> ops[i];
    }
    ifStruct* isarr = new ifStruct[linenum];
    for(int i=0;i<linenum;++i){
        isarr[i].opvalues = new string[opbitN];
        for(int k=0;k<opbitN;++k){
            rs >> isarr[i].opvalues[k];
        }

        char c = rs.get();
        while(c != '\n' && c != -1){
            isarr[i].comment.push_back(c);
            c = rs.get();
        }
        //isarr[i].comment.push_back(0);
    }
    rs.close();

    ofstream out;
    out.open(outfile);
    for(int i=0;i<linenum;++i){
        out << "if";
        for(int k=0;k<opbitN-1;++k){
            out << "(masking(" << ops[k] << ", \"" << isarr[i].opvalues[k] << "\") &&";
        }
        out << "(masking(" << ops[opbitN-1] << ", \"" << isarr[i].opvalues[opbitN-1] << "\")";
        for(int k=0;k<opbitN;++k){
            out << ")";
        }
        out << endl;
        out << "{" << endl;
        out << "\t//" << isarr[i].comment << endl;
        out << "}" << endl;
    }
    return 0;
}