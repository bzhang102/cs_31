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
        if(!isspace(c) && (c != '-')) {
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
    //return 2 if invalid lineLength
    if(lineLength < 1) {
        return 2;
    }
    
    //state trackers
    bool bad = false;
    int len = 0;
    
    //prepend trackers
    bool prependBreak = false;
    int prependSpaces = 0;
    char prevToken[181] = "@P@";
    char lastChar = '\0';
    
    //iterates through input as series of tokens
    for(;;) {
        //defines current token cstring within to avoid repeated wiping
        char token[181] = "";
        
        //reads next token; breaks at end of file
        if(getToken(token, inf)) {
            break;
        }
        
        //avoids empty tokens
        if(strlen(token) != 0) {
            //checks for break
            if(strcmp(token, "@P@") == 0) {
                //avoids leading and consecutive breaks
                if(strcmp(prevToken, "@P@") != 0) {
                    prependBreak = true;
                }
                
                //checks if token is longer than maximum line length, if so, split renders
            } else if(strlen(token) > lineLength) {
                //prepends break
                if(prependBreak) {
                    outf << endl << endl;
                    len = 0;
                    prependSpaces = 0;
                    prependBreak = false;
                }
                
                //prepends spaces if possible
                if(len + prependSpaces < lineLength) {
                    while(prependSpaces > 0) {
                        outf << ' ';
                        prependSpaces--;
                        len++;
                    }
                } else {
                    outf << endl;
                    len = 0;
                    prependSpaces = 0;
                }
                
                //renders oversize token char by char
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
                switch(lastChar) {
                    case '-':
                        prependSpaces = 0;
                        break;
                    case '.':
                    case '?':
                    case '!':
                    case ':':
                        prependSpaces = 2;
                        break;
                    default:
                        prependSpaces = 1;
                }
                
                //generates error state of 1
                bad = true;
                
                //attempts to render on current line
            } else {
                //prepends break
                if(prependBreak) {
                    outf << endl << endl;
                    len = 0;
                    prependSpaces = 0;
                    prependBreak = false;
                }
                
                //attempts to render string with prepended spaces
                if(len + prependSpaces + strlen(token) <= lineLength) {
                    //render required spaces
                    while(prependSpaces > 0) {
                        outf << ' ';
                        prependSpaces--;
                        len++;
                    }
                    
                    //render token
                    outf << token;
                    len += strlen(token);
                    
                    //string does not fit
                } else {
                    prependSpaces = 0;
                    len = (int) strlen(token);
                    //render token on next line
                    outf << endl << token;
                }
                
                lastChar = token[strlen(token) - 1];
                switch(lastChar) {
                    case '-':
                        prependSpaces = 0;
                        break;
                    case '.':
                    case '?':
                    case '!':
                    case ':':
                        prependSpaces = 2;
                        break;
                    default:
                        prependSpaces = 1;
                }
            }
            //update prevToken
            strcpy(prevToken, token);
        } else {
            //catches case where whitespace follows hyphen
            if(lastChar == '-') {
                prependSpaces = 1;
            }
        }
    }
    
    //returns 1 if token longer than lineLength is found
    if(bad) {
        return 1;
    }
    return 0;
}

int main()
{
    ifstream infile("/Users/brandon/IDEs/XCode/cs_31/project_5/project_5/in");
    if(!infile) {
        cerr << "NO INPUT" << endl;
    }
    ofstream outfile("/Users/brandon/IDEs/XCode/cs_31/project_5/project_5/out");
    if(!infile) {
        cerr << "NO OUTPUT" << endl;
    }
    int len = 10;
    return render(len, infile, outfile);
}
