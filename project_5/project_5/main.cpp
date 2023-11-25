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

int main() {
    // MARK: - Invalid parameters
    assert(testRender(0, "Hello", "", 2)); // max length can't be 0

    // MARK: - Whitespaces
    assert(testRender(100, " Hello!", "Hello!\n", 0)); // space at beginning, remove it
    assert(testRender(100, "\nHello!", "Hello!\n", 0)); // newline at beginning, remove it
    assert(testRender(100, "  \n\n\nHello!", "Hello!\n", 0)); // space + newlines at beginning, remove them
    assert(testRender(100, "Hello! ", "Hello!\n", 0)); // space at end, remove it
    assert(testRender(100, "Hello! \n\n  ", "Hello!\n", 0)); // spaces + newlines at end, remove them
    assert(testRender(8, "Hello world", "Hello\nworld\n", 0)); // break at space
    assert(testRender(8, "Hello   world", "Hello\nworld\n", 0)); // consecutive spaces are ignored

    // MARK: - Hyphen behavior
    assert(testRender(100, "Henley-on-Thames", "Henley-on-Thames\n", 0)); // normal behavior where it fits
    assert(testRender(12, "Henley-on-Thames", "Henley-on-\nThames\n", 0)); // broken up after a hyphen
    assert(testRender(5, "1234-1234-1234", "1234-\n1234-\n1234\n", 0)); // multiple hyphen breaks
    assert(testRender(4, "1234-1234-1234", "1234\n-\n1234\n-\n1234\n", 1)); // hyphen couldn't fit and is on its own line
    assert(testRender(2, "1234-1234-1234", "12\n34\n-\n12\n34\n-\n12\n34\n", 1)); // both word and hyphen are split
    assert(testRender(1, "1234-1234-1234", "1\n2\n3\n4\n-\n1\n2\n3\n4\n-\n1\n2\n3\n4\n", 1)); // one single vertical line
    assert(testRender(100, "Hello- world", "Hello- world\n", 0)); // space after hyphen
    assert(testRender(100, "Hello-   world", "Hello- world\n", 0)); // multiple spaces after hyphen

    // MARK: - Punctuation (.?!:)
    assert(testRender(100, "Hello! My name is Andrew.", "Hello!  My name is Andrew.\n", 0)); // 2 spaces after !
    assert(testRender(100, "Hello?!! World", "Hello?!!  World\n", 0)); // consecutive punctuation
    assert(testRender(100, "What time is it? Time to get a watch.", "What time is it?  Time to get a watch.\n", 0)); // test question mark
    assert(testRender(100, "A wise man once said: I love CS 31.", "A wise man once said:  I love CS 31.\n", 0)); // test colon
    assert(testRender(100, "Hi... how are you doing?", "Hi...  how are you doing?\n", 0)); // 2 spaces after end of ellipsis
    assert(testRender(100, "!-!-!-!-!", "!-!-!-!-!\n", 0)); // punctuation with hyphen
    assert(testRender(5, "!-!-!-!-!", "!-!-\n!-!-!\n", 0)); // break in middle
    assert(testRender(16, "What time is it? Time to get a watch.", "What time is it?\nTime to get a\nwatch.\n", 0)); // no space after question mark when breaking
    assert(testRender(6, "Hello world!", "Hello\nworld!\n", 0)); // remove the extra space from the exclamation mark
    assert(testRender(5, "Hello, world!", "Hello\n,\nworld\n!\n", 1)); // comma and exclamation mark on separate line

    // MARK: - Single word over multiple lines
    assert(testRender(3, "abcdef", "abc\ndef\n", 1)); // split across 2 lines, returning 1
    assert(testRender(3, "abcdefg", "abc\ndef\ng\n", 1)); // single character at the end
    assert(testRender(10, "A long word is supercalifragilisticexpialidocious", "A long\nword is\nsupercalif\nragilistic\nexpialidoc\nious\n", 1)); // only last word is too long

    // MARK: - Paragraph breaks
    assert(testRender(100, "Hello @P@ World", "Hello\n\nWorld\n", 0)); // paragraph break in middle
    assert(testRender(100, "Hello @P@ @P@ World", "Hello\n\nWorld\n", 0)); // duplicate paragraph breaks have no effect
    assert(testRender(100, "@P@ Hello @P@ World", "Hello\n\nWorld\n", 0)); // paragraph break at start is ignored
    assert(testRender(100, "Hello @P@ World @P@", "Hello\n\nWorld\n", 0)); // paragraph break at end is ignored
    assert(testRender(100, "Hello @P@ World @P@ ", "Hello\n\nWorld\n", 0)); // paragraph break at end and extra space are both ignored
    assert(testRender(100, "banjo@P@", "banjo@P@\n", 0)); // @P@ is part of the previous word
    assert(testRender(100, "banjo@P@ banjo@P@", "banjo@P@ banjo@P@\n", 0)); // space after the @P@ isn't enough, need space before too
    assert(testRender(100, "Hello @P@world", "Hello @P@world\n", 0)); // space before the @P@ isn't enough, need space after too
    assert(testRender(100, "Hello @P@@P@ World", "Hello @P@@P@ World\n", 0)); // consecutive @P@'s without space just renders it as-is
    assert(testRender(100, "@P@-@P@", "@P@-@P@\n", 0)); // should print out as a single word
    assert(testRender(100, "@P@ @P@- -@P@ @P@", "@P@- -@P@\n", 0)); // ignore leading and ending paragraph break
    assert(testRender(100, "@P@ @P@- -@P@World! @P@- !-@P@ Hello-@P@-World.", "@P@- -@P@World!  @P@- !-@P@ Hello-@P@-World.\n", 0)); // lots of weird combinations
    assert(testRender(20, "@P@ @P@- -@P@World! @P@- !-@P@ Hello-@P@-World.", "@P@- -@P@World!\n@P@- !-@P@ Hello-\n@P@-World.\n", 0)); // split on the hyphen after "Hello"
    assert(testRender(10, "@P@ @P@- -@P@World! @P@- !-@P@ Hello-@P@-World.", "@P@- -\n@P@World!\n@P@- !-@P@\nHello-@P@-\nWorld.\n", 0)); // more splits
    assert(testRender(1, "@P@ @P@- -@P@World! @P@- !-@P@ Hello-@P@-World.", "@\nP\n@\n-\n-\n@\nP\n@\nW\no\nr\nl\nd\n!\n@\nP\n@\n-\n!\n-\n@\nP\n@\nH\ne\nl\nl\no\n-\n@\nP\n@\n-\nW\no\nr\nl\nd\n.\n", 1)); // single vertical line of output

    // MARK: - Stress testing
    assert(testRender(500, "The input word @P@ is not to be processed as a word according to the above rules; instead, it indicates a paragraph break. The first word in the input following a paragraph break will be the first word of a new paragraph in the output. If a paragraph has already been output, the new paragraph must be separated from the one that precedes it by an empty line (i.e., a line with no characters other than the terminating newline). The very first output paragraph must not be preceded by an empty line. The very last output paragraph must not be followed by an empty line. Two or more consecutive @P@ words in the input are treated as just one paragraph break. Notice that banjo@P@ is one eight-character word; it does not cause a paragraph break, because in that string, @P@ is not a word because of the immediately preceding non-whitespace character o.", "The input word\n\nis not to be processed as a word according to the above rules; instead, it indicates a paragraph break.  The first word in the input following a paragraph break will be the first word of a new paragraph in the output.  If a paragraph has already been output, the new paragraph must be separated from the one that precedes it by an empty line (i.e., a line with no characters other than the terminating newline).  The very first output paragraph must not be preceded by an empty line.  The very last\noutput paragraph must not be followed by an empty line.  Two or more consecutive\n\nwords in the input are treated as just one paragraph break.  Notice that banjo@P@ is one eight-character word; it does not cause a paragraph break, because in that string,\n\nis not a word because of the immediately preceding non-whitespace character o.\n", 0)); // first parameter greater than 250

    assert(testRender(25, "asdlfdasoifjaspodfj-\n1239ij9 fsdjna9fusd-\n14890r413\n9fjasdjioasdcj9asdf-dfa-\naqwe-qwe-=q=q-q-=qfnjvc\nvf @P@-\ndfiosj90vji0af0jaw @P@@P@\nafsdokfja-@P@\n\nfd9as0ad0-s-09\n", "asdlfdasoifjaspodfj-\n1239ij9 fsdjna9fusd-\n14890r413\n9fjasdjioasdcj9asdf-dfa-\naqwe-qwe-=q=q-q-=qfnjvc\nvf @P@-\ndfiosj90vji0af0jaw @P@@P@\nafsdokfja-@P@ fd9as0ad0-\ns-09\n", 0)); // lots of combinations

    // MARK: - Additional test cases
    assert(testRender(40, "It always does seem to me that I am doing more work than\nI should do. It is not that I object to the work, mind you;\nI like work: it fascinates me.   I can sit and look at it for hours.\nI love to keep it by me: the idea of getting\nrid\nof it nearly breaks my heart. @P@ You cannot give me too\nmuch work; to accumulate work has almost become\n\n\na passion with me: my study is so full of it now, that there is hardly\nan inch of room for any more.\n\n", "It always does seem to me that I am\ndoing more work than I should do.  It is\nnot that I object to the work, mind you;\nI like work:  it fascinates me.  I can\nsit and look at it for hours.  I love to\nkeep it by me:  the idea of getting rid\nof it nearly breaks my heart.\n\nYou cannot give me too much work; to\naccumulate work has almost become a\npassion with me:  my study is so full of\nit now, that there is hardly an inch of\nroom for any more.\n", 0));
    assert(testRender(30, "This text was rendered with max line length 30. @P@ This is paragraph 2!", "This text was rendered with\nmax line length 30.\n\nThis is paragraph 2!\n", 0));
    assert(testRender(7, "This\n\t\tis a\ntest\n", "This is\na test\n", 0));
    assert(testRender(8, "  This is a test  \n", "This is\na test\n", 0));
    assert(testRender(6, "Testing it\n", "Testin\ng it\n", 1));
    assert(testRender(-5, "irrelevant", "irrelevant", 2));

    cerr << "All tests complete!" << endl;

    return 0;
}
