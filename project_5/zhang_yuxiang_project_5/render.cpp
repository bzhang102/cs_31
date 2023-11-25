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

//Brandon's Test Cases
int main() {
    //MARK: invalid lineLength
    assert(testRender(0, "Hello", "", 2)); //max length can't be 0
    assert(testRender(-10, "Hello", "", 2)); //max length can't be negative

    //MARK: basic test case
    assert(testRender(5, "Hello", "Hello\n", 0));

    //MARK: leading or trailing whitespace
    assert(testRender(15, " asdf", "asdf\n", 0)); //leading space
    assert(testRender(15, "asdf ", "asdf\n", 0)); //trailing space
    assert(testRender(15, "\nasdf", "asdf\n", 0)); //leading line break
    assert(testRender(15, "asdf\n", "asdf\n", 0)); //trailing line break
    assert(testRender(15, "     \n\n\n\n\n\nHello", "Hello\n", 0)); //multiple leading line breaks
    assert(testRender(15, "Hello\n\n\n\n\n\n     ", "Hello\n", 0)); //multiple trailing line breaks

    //MARK: word splitting
    assert(testRender(40, "It always does seem to me that I am doing more work than\nI should do. It is not that I object to the work, mind you;\nI like work: it fascinates me.       I can sit and look at it for hours.\nI love to keep     it by me: the idea of getting\nrid\nof it nearly breaks my heart. @P@ You cannot give me too\nmuch work; to accumulate work has almost become\n\n\na passion with me: my study is so full of it now, that there is hardly\nan inch of room for any more.", "It always does seem to me that I am\ndoing more work than I should do.  It is\nnot that I object to the work, mind you;\nI like work:  it fascinates me.  I can\nsit and look at it for hours.  I love to\nkeep it by me:  the idea of getting rid\nof it nearly breaks my heart.\n\nYou cannot give me too much work; to\naccumulate work has almost become a\npassion with me:  my study is so full of\nit now, that there is hardly an inch of\nroom for any more.\n", 0)); //multiple word splitting tests that cover most cases

    //MARK: hyphens
    assert(testRender(10, "Thames so-called Henley-on-Thames so--called so- -so\n", "Thames so-\ncalled\nHenley-on-\nThames so-\n-called\nso- -so\n", 0)); //multiple hyphen tests
    assert(testRender(10, "asdf-asdf", "asdf-asdf\n", 0)); //hyphen token fits on one line
    assert(testRender(6, "asdf-asdf", "asdf-\nasdf\n", 0)); //hyphen token that needs splitting
    assert(testRender(6, "asdf-asdf-asdf", "asdf-\nasdf-\nasdf\n", 0)); //multiple hyphen tokens
    assert(testRender(12, "asdf-asdf-asdf", "asdf-asdf-\nasdf\n", 0)); //multiple hyphen tokens broken at second hyphen
    assert(testRender(12, "asdf-asdf-asdf", "asdf-asdf-\nasdf\n", 0)); //multiple hyphen tokens broken at second hyphen
    assert(testRender(15, "asdf- asdf", "asdf- asdf\n", 0)); //hyphens split by space
    assert(testRender(15, "asdf-  asdf", "asdf- asdf\n", 0)); //hyphens split by multiple spaces
    assert(testRender(5, "----------", "-----\n-----\n", 0)); //only hyphens
    assert(testRender(5, "- - - - - - - - - -", "- - -\n- - -\n- - -\n-\n", 0)); //hyphens with spaces

    //MARK: paragraph breaks
    assert(testRender(15, "asdf @P@ asdf", "asdf\n\nasdf\n", 0)); //basic case
    assert(testRender(15, "@P@ asdf", "asdf\n", 0)); //leading breaks ignored
    assert(testRender(15, "asdf @P@", "asdf\n", 0)); //trailing breaks ignored
    assert(testRender(15, "asdf @P@ @P@ asdf", "asdf\n\nasdf\n", 0)); //multiple breaks ignored
    assert(testRender(25, "asdf @P@@P@", "asdf @P@@P@\n", 0)); //only '@P@' is considered a break
    assert(testRender(15, "@P@-@P@", "@P@-@P@\n", 0)); //with hyphen
    assert(testRender(4, "@P@-@P@", "@P@-\n@P@\n", 0)); //breaks at hyphen but doesnt not paragraph break
    assert(testRender(2, "as @P@ df", "as\n\ndf\n", 0)); //length less than length of break token

    //MARK: error code 1 cases
    assert(testRender(15, "asdfasdfasdfasdfasdf", "asdfasdfasdfasd\nfasdf\n", 1)); //basic case
    assert(testRender(4, "asdfasdfasdfasdfasdf", "asdf\nasdf\nasdf\nasdf\nasdf\n", 1)); //split to multiple lines
    assert(testRender(4, "asdfasdfasdfasdfasdf", "asdf\nasdf\nasdf\nasdf\nasdf\n", 1)); //split to multiple lines
    assert(testRender(5, "asdf-asdfasdf--asdf asdf", "asdf-\nasdfa\nsdf--\nasdf\nasdf\n", 1)); //with hyphens
    assert(testRender(6, "asdf!-asdfasdf!-asdf asdf", "asdf!-\nasdfas\ndf!-\nasdf\nasdf\n", 1)); //with hyphens and punctuation

    //MARK: misc
    assert(testRender(15, "", "", 0)); //empty input
    assert(testRender(15, "@P@ @P@ @P@", "", 0)); //only breaks
    assert(testRender(179, "asdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasd", "asdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasd\n", 0)); //179 character long token
    assert(testRender(500, "It always does seem to me that I am doing more work than\nI should do. It is not that I object to the work, mind you;\nI like work: it fascinates me.       I can sit and look at it for hours.\nI love to keep     it by me: the idea of getting\nrid\nof it nearly breaks my heart. @P@ You cannot give me too\nmuch work; to accumulate work has almost become\n\n\na passion with me: my study is so full of it now, that there is hardly\nan inch of room for any more.", "It always does seem to me that I am doing more work than I should do.  It is not that I object to the work, mind you; I like work:  it fascinates me.  I can sit and look at it for hours.  I love to keep it by me:  the idea of getting rid of it nearly breaks my heart.\n\nYou cannot give me too much work; to accumulate work has almost become a passion with me:  my study is so full of it now, that there is hardly an inch of room for any more.\n", 0)); //long output line (EXTRA CREDIT CASE)
}
