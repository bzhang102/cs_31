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
        if(!isspace(c) && c != '-') {
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
    
    bool bad = false;
    int len = 0;
    char prevToken[181] = "@P@";
    //iterates through input as series of tokens
    for(;;) {
        char token[181] = "";
        
        //reads next token; breaks at end of file
        if(getToken(token, inf)) {
            break;
        }
        
        //skips over empty tokens
        if(strlen(token) != 0) {
            //checks for and executes paragraph break
            if(strcmp(token, "@P@") == 0) {
                //handles multiple paragraph breaks in a row
                if(strcmp(prevToken, "@P@") != 0) {
                    outf << endl << endl;
                    len = 0;
                }
                
                //checks if token is longer than maximum line length, if so, split renders
            } else if(strlen(token) > lineLength) {
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
                bad = true;
                
                //attempts to render on current line
            } else {
                //gets last character
                char lastChar = prevToken[strlen(prevToken) - 1];
                cout << token << " " << lastChar << endl;
                
                //case: first token
                if(len == 0 && strlen(token) <= lineLength) {
                    outf << token;
                    len += strlen(token);
                    
                    //case: last character was hypen, prepend no spaces
                } else if(lastChar == '-' && len + strlen(token) <= lineLength) {
                    outf << token;
                    len += strlen(token);
                    
                    //case: last character was normal character, prepend one space
                } else if((lastChar != '.' && lastChar != '?' && lastChar != '!' && lastChar != ':') && len +           strlen(token) + 1 <= lineLength) {
                    outf << " " << token;
                    len += strlen(token) + 1;
                    
                    //case: last character was punctuation, prepend two spaces
                } else if((lastChar == '.' || lastChar == '?' || lastChar == '!' || lastChar == ':') &&
                          len + strlen(token) + 2 <= lineLength) {
                    outf << "  " << token;
                    len += strlen(token) + 2;
                    
                    //case: word does not fit, start new line
                } else {
                    //reset len to equal current token length
                    len = (int) strlen(token);
                    //render token on next line
                    outf << endl << token;
                }
            }
            
            //update prevToken
            strcpy(prevToken, token);
        }
    }
    
    //returns 1 if token longer than lineLength is found
    if(bad) {
        return 1;
    }
    //returns 0 if state normal
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
    int len = 15;
    return render(len, infile, outfile);
}
