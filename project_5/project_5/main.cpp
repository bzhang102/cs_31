#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <sstream>
#include <streambuf>
#include <cassert>

using namespace std;

bool getToken(char token[], istream& inf);
bool hyphenate(int lineLength, int& len, int& prependSpaces, char token[], ostream& outf, int& state);
void renderInSize(int lineLength, int& len, int& prependSpaces, char token[], ostream& outf, int& state);
void renderOutSize(int& state, int lineLength, int&len, int& prependSpaces, char token[], ostream& outf);

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
    int state = 0;
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
    }
    outf << endl;
    return state;
}

//tester
void testRender(int lineLength, const char input[], const char expectedOutput[], int expectedReturnValue) {
    istringstream iss(input);
    ostringstream oss;
    ostringstream dummy;
    streambuf* origCout = cout.rdbuf(dummy.rdbuf());
    int retval = render(lineLength, iss, oss);
    cout.rdbuf(origCout);
    if ( ! dummy.str().empty())
        cerr << "WROTE TO COUT INSTEAD OF THIRD PARAMETER FOR: " << input << endl;
    else if (retval != expectedReturnValue)
        cerr << "WRONG RETURN VALUE FOR: " << input << endl;
    else if (retval == 2)
    {
        if ( ! oss.str().empty())
            cerr << "WROTE OUTPUT WHEN LINELENGTH IS " << lineLength << endl;
    }
    else if (oss.str() != expectedOutput)
        cerr << "WRONG RESULT FOR: " << input << endl;
}

//Development Tester
//int main() {
//    ifstream infile("/Users/brandon/IDEs/XCode/cs_31/project_5/project_5/in");
//    ofstream outfile("/Users/brandon/IDEs/XCode/cs_31/project_5/project_5/out");
//    return render(40, infile, outfile);
//}

//Smallberg's Test Cases
//int main() {
//    testRender(7, "This\n\t\tis a\ntest\n", "This is\na test\n", 0);
//    testRender(8, "  This is a test  \n", "This is\na test\n", 0);
//    testRender(6, "Testing it\n", "Testin\ng it\n", 1);
//    testRender(-5, "irrelevant", "irrelevant", 2);
//    cerr << "Tests complete" << endl;
//}



