#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

using namespace std;

//returns true if at end of file, false if not
bool getToken(char token[], istream& inf) {
    char c;
    while(inf.get(c)) {
        //appends to token
        if(!isspace(c)) {
            token[strlen(token)] = c;
        } else {
            //end of token reached (hit whitespace)
            return false;
        }
    }
    
    //end of file reached (while condition not satisfied)
    return true;
}

//function implementation
int render(int lineLength, istream& inf, ostream& outf) {
    if(lineLength < 1) {
        return 2;
    }
    
    //for each token in inf
    for(;;) {
        char token[181] = "";
        
        //breaks at end of file while reading next token
        if(getToken(token, inf)) {
            break;
        }
    }
    
    return 0;
}

int main()
{
    ifstream infile("/Users/brandon/IDEs/XCode/cs_31/project_5/project_5/in");
    if(!infile) {
        cout << "NO INPUT" << endl;
    }
    ofstream outfile("/Users/brandon/IDEs/XCode/cs_31/project_5/project_5/out");
    if(!infile) {
        cout << "NO OUTPUT" << endl;
    }
    int len = 10;
    
    return render(len, infile, outfile);

}
