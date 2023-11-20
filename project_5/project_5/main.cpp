#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <sstream>
#include <streambuf>
#include <cassert>

using namespace std;

void getToken(char token[], istream& inf, bool& eof);
bool hyphenate(int lineLength, int& len, int& prependSpaces, char token[], ostream& outf, int& state);
void renderInSize(int lineLength, int& len, int& prependSpaces, char token[], ostream& outf, int& state);
void renderOutSize(int& state, int lineLength, int&len, int& prependSpaces, char token[], ostream& outf);

//reads each string
void getToken(char token[], istream& inf, bool& eof) {
    char c;
    //iterate until end of file
    while(!eof) {
        //update eof state variable
        if(!inf.get(c)) {
            eof = true;
            return;
        }
        //break token at space
        if(isspace(c)) {
            return;
        }

        //append next character to token
        token[strlen(token)] = c;
    }
    return;
}

//attempts to split render a hyphenated token
bool hyphenate(int lineLength, int& len, int& prependSpaces, char token[], ostream& outf, int& state) {
    char portion1[180] = "";
    char portion2[180] = "";
    bool hasHyphen = false;
    //splits token at first hyphen
    for(int i = 0; i < strlen(token); i++) {
        if(!hasHyphen) {
            portion1[strlen(portion1)] = token[i];
        } else {
            portion2[strlen(portion2)] = token[i];
        }
        if(token[i] == '-') {
            hasHyphen = true;
        }
    }
    if(hasHyphen && strlen(portion2) > 0) {
        //renders portion1 accordingly
        if(strlen(portion1) <= lineLength) {
            renderInSize(lineLength, len, prependSpaces, portion1, outf, state);
        } else {
            renderOutSize(state, lineLength, len, prependSpaces, portion1, outf);
        }
        //renders portion2 accordingly
        if(strlen(portion2) <= lineLength) {
            renderInSize(lineLength, len, prependSpaces, portion2, outf, state);
        } else {
            renderOutSize(state, lineLength, len, prependSpaces, portion2, outf);
        }
        return true;
    }
    return false;
}

//renders token within size limit
void renderInSize(int lineLength, int& len, int& prependSpaces, char token[], ostream& outf, int& state) {
    //token fits
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
        //token does not fit
    } else {
        //attempts to hyphenate
        if(!hyphenate(lineLength, len, prependSpaces, token, outf, state)) {
            prependSpaces = 0;
            len = (int) strlen(token);
            //render token on next line
            outf << endl << token;
        }
    }
}

void renderOutSize(int& state, int lineLength, int&len, int& prependSpaces, char token[], ostream& outf) {
    //attempts to hyphenate
    if(!hyphenate(lineLength, len, prependSpaces, token, outf, state)) {
        if(len != 0) {
            outf << endl;
        }
        prependSpaces = 0;
        len = 0;
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
        state = 1;
    }
}

//function implementation
int render(int lineLength, istream& inf, ostream& outf) {
    //return 2 if invalid lineLength
    if(lineLength < 1) {
        return 2;
    }
    //state trackers
    int state = -1;
    int len = 0;
    bool eof = false;
    //prepend trackers
    bool prependBreak = false;
    int prependSpaces = 0;
    char prevToken[181] = "@P@";
    //iterates through input as series of tokens
    for(;;) {
        char token[181] = "";
        getToken(token, inf, eof);
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
                if(state == -1) {
                    state = 0;
                }
                //prepends break
                if(prependBreak) {
                    outf << endl << endl;
                    len = 0;
                    prependSpaces = 0;
                    prependBreak = false;
                }
                //renders according to bounds
                if(strlen(token) <= lineLength) {
                    renderInSize(lineLength, len, prependSpaces, token, outf, state);
                } else {
                    renderOutSize(state, lineLength, len, prependSpaces, token, outf);
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
        if(eof) {
            break;
        }
    }
    //if any input is printed, print new line
    if(state == 0 || state == 1) {
        outf << endl;
        return state;
    }
    //nothing is printed, but still return 0
    return 0;
}

//test render
bool testRender(int lineLength, const char input[], const char expectedOutput[], int expectedReturnValue) {
    istringstream iss(input);
    ostringstream oss;
    int retval = render(lineLength, iss, oss);
    if (retval != expectedReturnValue) {
        cout << "WRONG RETURN VALUE FOR: " << input << endl;
        return false;
    } else if (retval == 2) {
        if (!oss.str().empty()) {
            cout << "WROTE OUTPUT WHEN LINELENGTH IS " << lineLength << endl;
            return false;
        }
    } else if (oss.str() != expectedOutput) {
        cout << "-------------------" << endl;
        cout << "WRONG RESULT FOR: " << input << endl;
        cout << "----------received:" << endl;
        cout << oss.str() << endl;
        cout << "----------expected:" << endl;
        cout << expectedOutput << endl;
        cout << "-------------------" << endl;
        return false;
    }
    return true;
}
