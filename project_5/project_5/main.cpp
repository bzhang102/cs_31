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
        if(!isspace(c) && c != '\n' && c != '\t') {
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
    
    int len = 0;
    //iterates through input as series of tokens
    for(;;) {
        char token[181] = "";
        
        //breaks at end of file while reading next token
        if(getToken(token, inf)) {
            break;
        }
        
        //checks for and executes paragraph break
        if(strcmp(token, "@P@") == 0) {
            outf << endl << endl;
            len = 0;
            
        //if not paragraph break, attempts to render on current line
        } else {
            if(len + strlen(token) + 1 <= lineLength) {
                //appends space if token is not empty and token is not first in line
                if(len != 0 && strlen(token) != 0) {
                    outf << " ";
                    len++;
                }
                
                outf << token;
                len += strlen(token);
            //word does not fit
            } else {
                //reset len to equal current token length
                len = (int) strlen(token);
                //render token on next line
                outf << endl << token;
            }
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
    int len = 40;
    return render(len, infile, outfile);

}
