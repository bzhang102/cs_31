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
        if(!isspace(c)) {
            token[strlen(token)] = c;
            //returns if whitespace without appending
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
    //iterates through input as series of tokens
    for(;;) {
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
                //attempts to render token
            } else {
                //prepends break
                if(prependBreak) {
                    outf << endl << endl;
                    len = 0;
                    prependSpaces = 0;
                    prependBreak = false;
                }

                //renders token that fits on current line
                if(strlen(token) <= lineLength) {
                    //string fits
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
                    
                    //renders token longer than line length
                } else {
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
                    //generates error state of 1
                    bad = true;
                }
                //prepare to prepend space to next token if not break
                char lastChar = token[strlen(token) - 1];
                if(lastChar == '.' || lastChar == '!' || lastChar == '?' || lastChar == ':') {
                    prependSpaces = 2;
                } else {
                    prependSpaces = 1;
                }
            }
            //update prevToken
            strcpy(prevToken, token);
        }
    }
    outf << endl;
    
    //returns 1 if token longer than lineLength is found
    if(bad) {
        return 1;
    }
    return 0;
}

int main()
{
    ifstream infile("/Users/brandon/IDEs/XCode/cs_31/project_5/project_5/in");
    ofstream outfile("/Users/brandon/IDEs/XCode/cs_31/project_5/project_5/out");
    return render(40, infile, outfile);
}
