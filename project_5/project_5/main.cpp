#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

using namespace std;

//returns true if at end of file, false if not
bool getToken(char token[], istream& inf) {
    char c;
    while(inf.get(c)) {
        //appends to token and continues
        if(!isspace(c) && c != '\n' && c != '\t' && c != '-') {
            token[strlen(token)] = c;
            
        //appends to token and returns if hyphen
        } else if (c == '-') {
            token[strlen(token)] = c;
            return false;
            
        //returns if whitespace
        } else {
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
    
    bool bad = false;
    int lastChar = '\0';
    int len = 0;
    //iterates through input as series of tokens
    for(;;) {
        char token[181] = "";
        
        //reads next token; breaks at end of file
        if(getToken(token, inf)) {
            break;
        }
                
        //checks if token is longer than maximum line length, if so, split renders
        if(strlen(token) > lineLength) {
            for(int i = 0; i < strlen(token); i++) {
                //render char onto current line
                if(len + 1 <= lineLength) {
                    outf << token[i];
                    len++;
                    
                //render onto new line
                } else {
                    outf << endl << token[i];
                    len = 1;
                }
            }
                
            lastChar = token[strlen(token) - 1];
            bad = true;
            
        //checks for and executes paragraph break
        } else if(strcmp(token, "@P@") == 0) {
            outf << endl << endl;
            len = 0;
            
        //if not paragraph break, attempts to render on current line
        } else {
            //case: empty token (does nothing)
            if(strlen(token) == 0) {
                
            //case: first token
            } else if(len == 0 && strlen(token) <= lineLength) {
                outf << token;
                len += strlen(token);
            
            //case: last character was normal character
            } else if((lastChar != '.' && lastChar != '?' && lastChar != '!' && lastChar != ':') && len +           strlen(token) + 1 <= lineLength) {
                outf << " " << token;
                len += strlen(token) + 1;
                
            //case: last character was hypen
            } else if(lastChar == '-' && len + strlen(token) <= lineLength) {
                outf << token;
                len += strlen(token);
                
            //case: last character was punctuation
            } else if((lastChar == '.' || lastChar == '?' || lastChar == '!' || lastChar == ':') &&
                      len + strlen(token) + 2 <= lineLength) {
                outf << "  " << token;
                len += strlen(token) + 2;
                
            //word does not fit
            } else {
                //reset len to equal current token length
                len = (int) strlen(token);
                //render token on next line
                outf << endl << token;
            }
            
            //updates lastChar
            if(strlen(token) > 0) {
                lastChar = token[strlen(token) - 1];
            }
        }
    }
    
    //returns 1 if token longer than lineLength is found
    if(bad) {
        return 1;
    }
    return 0;}

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
