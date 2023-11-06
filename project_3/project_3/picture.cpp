#include "grid.h"
#include <cctype>
#include <cassert>
#include <string>
#include <iostream>

using namespace std;

const int HORIZ = 0;
const int VERT = 1;

const int FG = 0;
const int BG = 1;

//function implementation
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg) {
    //checks for valid direction
    if(dir != HORIZ && dir != VERT) {
        return false;
    }
    
    //checks for valid fgbg
    if(fgbg != FG && fgbg != BG) {
        return false;
    }
    
    //checks if starting point within bounds
    if(r > getRows() || r < 1 || c > getCols() || c < 1) {
        return false;
    }
    
    //checks if plotChar is printable
    if(!isprint(plotChar)) {
        return false;
    }
    
    //split into two cases depending on direction
    if(dir == HORIZ) {
        //find end col
        int endpoint = c + distance;
        
        //check if line within grid
        if(endpoint > getCols() || endpoint < 1) {
            return false;
        }
        
        while(c != endpoint) {
            //if fg or empty, plot char
            if(fgbg == FG || getChar(r, c) == ' ') {
                setChar(r, c, plotChar);
            }
            
            //change col based on sign of direction
            if(distance < 0) {
                c--;
            } else {
                c++;
            }
        }
        
        //attempt to plot one more time for c == endpoint
        if(fgbg == FG || getChar(r, c) == ' ') {
            setChar(r, c, plotChar);
        }
    } else {
        //find end row
        int endpoint = r + distance;
        
        //check if line within grid
        if(endpoint > getRows() || endpoint < 1) {
            return false;
        }
        
        while(r != endpoint) {
            //if fg or empty, plot char
            if(fgbg == FG || getChar(r, c) == ' ') {
                setChar(r, c, plotChar);
            }
            
            //change row based on sign of direction
            if(distance < 0) {
                r--;
            } else {
                r++;
            }
        }
        
        //attempt to plot one more time for r == endpoint
        if(fgbg == FG || getChar(r, c) == ' ') {
            setChar(r, c, plotChar);
        }
    }
    
    return true;
}

//checks if command string is syntatically valid
bool isValidCommandString(string commandString, int& badPos) {
    int index = 0;
    char curr;
    
    while(index < commandString.size()) {
        int length;
        curr = tolower(commandString.at(index));
        
        switch(curr) {
            case 'h':
            case 'v':
                length = 0;
                index++;
                
                //skips first character if it's a negative sign
                if(index < commandString.size() && commandString.at(index) == '-') {
                    index++;
                }
                
                //checks if next two characters are digits
                while(index < commandString.size() && isdigit(commandString.at(index)) && length < 2) {
                    index++;
                    length++;
                }
                
                if(length == 0) {
                    badPos = index;
                    return false;
                }
                
                break;
            case 'f':
            case 'b':
                index++;
                //if out of bounds or unprintable return false
                if(index >= commandString.size() || !isprint(commandString.at(index))) {
                    badPos = index;
                    return false;
                }
                index++;
                break;
            case 'c':
                index++;
                break;
            default:
                badPos = index;
                return false;
        }
    }
    
    return true;
}

//attempts to plot line
bool processVH(string commandString, int dir, int& pos, int& currR, int& currC, char& plotChar, int&mode) {
    //advance pointer to read parameter
    pos++;
    
    //read parameter
    string input;
    while(pos < commandString.size() && (isdigit(commandString.at(pos)) || commandString.at(pos) == '-')) {
        input += commandString.at(pos);
        
        //advance pointer
        pos++;
    }
    
    //parse string parameter to int
    int distance = stoi(input);
    //if plotting failed, return false, else plot line
    if(!plotLine(currR, currC, distance, dir, plotChar, mode)) {
        return false;
    }
    
    //update r/c position
    if(dir == HORIZ) {
        currC += distance;
    } else {
        currR += distance;
    }
    
    return true;
}

//function implementation
int performCommands(string commandString, char& plotChar, int& mode, int& badPos) {
    //checks if character is plotable and modes are valid
    if(!isprint(plotChar) || (mode != FG && mode != BG)) {
        return 2;
    }
    
    //checks syntax
    if(!isValidCommandString(commandString, badPos)) {
        return 1;
    }
    
    //sets position to default
    int currR = 1;
    int currC = 1;
    
    char curr = ' ';
    int pos = 0;
    int command = 0;
    
    //reads and executes command string
    while(pos < commandString.size()) {
        curr = tolower(commandString.at(pos));
        command = pos;
        
        switch(curr) {
            case 'h':
                if(!processVH(commandString, HORIZ, pos, currR, currC, plotChar, mode)) {
                    badPos = command;
                    return 3;
                }
                break;
            case 'v':
                if(!processVH(commandString, VERT, pos, currR, currC, plotChar, mode)) {
                    badPos = command;
                    return 3;
                }
                break;
            case 'f':
                //advance pointer to read parameter
                pos++;
                
                //update mode and plotChar
                mode = FG;
                plotChar = commandString.at(pos);
                
                //advance pointer to read next command char
                pos++;
                break;
            case 'b':
                //advance pointer to read parameter
                pos++;
                
                //update mode and plotChar
                mode = BG;
                plotChar = commandString.at(pos);
                
                //advance pointer to read next command char
                pos++;
                break;
            case 'c':
                //clear and reset to defaults
                clearGrid();
                currR = 1;
                currC = 1;
                plotChar = '*';
                mode = FG;
                
                //advance pointer to read next command char
                pos++;
                break;
                
                //no default included because other cases would not have passed syntax check
        }
    }
    
    return 0;
}

//Test Cases
//int main() {
//    //testplotLine()
//    setSize(20, 15);
//    //valid
//    assert(plotLine(1, 1, 10, HORIZ, '*', FG));
//    assert(plotLine(1, 1, 10, VERT, '*', FG));
//    assert(plotLine(10, 10, 0, HORIZ, '*', FG));
//    assert(plotLine(12, 10, 0, HORIZ, '*', FG));
//    assert(plotLine(20, 15, -10, HORIZ, '*', FG));
//    assert(plotLine(20, 15, -10, VERT, '*', BG));
//    assert(plotLine(20, 15, -10, VERT, '&', BG));
//    //invalid
//    assert(!plotLine(-1, 1, 10, HORIZ, '*', FG));
//    assert(!plotLine(1, -1, 10, HORIZ, '*', FG));
//    assert(!plotLine(20, 15, 10, HORIZ, '*', FG));
//    assert(!plotLine(20, 15, 10, VERT, '*', FG));
//    assert(!plotLine(1, 1, 10, 10, '*', FG));
//    assert(!plotLine(1, 1, 10, HORIZ, '*', 10));
//    assert(!plotLine(1, 1, 10, HORIZ, '\n', FG));
//
//    draw();
//
//    //test isValidCommandString()
//    int badPos = 999;
//    //valid
//    assert(isValidCommandString("H25H-10CF&b*v01", badPos) && badPos == 999);
//    assert(isValidCommandString("", badPos) && badPos == 999);
//    //invalid
//    assert(!isValidCommandString("F#H+25H?V3!", badPos) && badPos == 3);
//    assert(!isValidCommandString("B@H", badPos) && badPos == 3);
//    assert(!isValidCommandString("C12 ", badPos) && badPos == 1);
//    assert(!isValidCommandString("Q3V4#", badPos) && badPos == 0);
//    assert(!isValidCommandString("V03C H123#", badPos) && badPos == 4);
//    assert(!isValidCommandString("H5H-1-2", badPos) && badPos == 5);
//    assert(!isValidCommandString("FH8", badPos) && badPos == 2);
//    assert(!isValidCommandString("H25,H-10", badPos) && badPos == 3);
//    assert(!isValidCommandString("H\n", badPos) && badPos == 1);
//    assert(!isValidCommandString("f\n", badPos) && badPos == 1);
//
//    //test performCommands()
//    int bad = 999;
//    char pc = '*';
//    int m = FG;
//    setSize(12, 15);
//
//    //valid
//    assert(performCommands("V2", pc, m, bad) == 0 && bad == 999);
//    assert(performCommands("b^H14F&V11H-03", pc, m, bad) == 0 && bad == 999);
//    assert(performCommands("", pc, m , bad) == 0 && bad == 999);
//    //code1
//    assert(performCommands("F#H+25H?V3!", pc, m, bad) == 1 && bad == 3);
//    assert(performCommands("B@H", pc, m, bad) == 1 && bad == 3);
//    assert(performCommands("C12 ", pc, m, bad) == 1 && bad == 1);
//    assert(performCommands("Q3V4#", pc, m, bad) == 1 && bad == 0);
//    assert(performCommands("V03C H123#", pc, m, bad) == 1 && bad == 4);
//    assert(performCommands("H5H-1-2", pc, m, bad) == 1 && bad == 5);
//    assert(performCommands("FH8", pc, m, bad) == 1 && bad == 2);
//    assert(performCommands("H25,H-10", pc, m, bad) == 1 && bad == 3);
//    assert(performCommands("H\n", pc, m, bad) && bad == 1);
//    assert(performCommands("f\n", pc, m, bad) && bad == 1);
//    assert(performCommands("V99F", pc, m, bad) == 1 && bad == 4);
//    assert(performCommands(" V10", pc, m, bad) == 1 && bad == 0);
//    assert(performCommands("V10 ", pc, m, bad) == 1 && bad == 3);
//    assert(performCommands("V-001", pc, m, bad) == 1 && bad == 4);
//    assert(performCommands("V-", pc, m, bad) == 1 && bad == 2);
//    assert(performCommands("V-1-", pc, m, bad) == 1 && bad == 3);
//    //code2
//    bad = 999;
//    pc = '\n';
//    assert(performCommands("", pc, m, bad) == 2 && bad == 999);
//    pc = '*';
//    m = 10;
//    assert(performCommands("", pc, m, bad) == 2 && bad == 999);
//    m = FG;
//    //code3
//    assert(performCommands("H-1", pc, m, bad) == 3 && bad == 0);
//    assert(performCommands("V-1", pc, m, bad) == 3 && bad == 0);
//    assert(performCommands("H20", pc, m, bad) == 3 && bad == 0);
//    assert(performCommands("V20", pc, m, bad) == 3 && bad == 0);
//
//    draw();
//    cout << "All test cases passed" << endl;
//    return 0;
//}

//Rachel's Test Cases
//int main() {
//    /** PLOT LINE TEST #1*/
//    setSize(20, 20);
//
//    //valid
//    assert(plotLine(1, 1, 7, HORIZ, 'R', FG)); // horizontal line with positive distance
//    assert(plotLine(1, 10, -9, HORIZ, 'B', BG)); // horizontal line with negative distance
//    assert(plotLine(1, 7, 5, VERT, '&', BG)); // vertical line with positive distance
//    assert(plotLine(20, 20, -15, VERT, '*', FG)); // vertical line with negative distance
//    assert(plotLine(13, 13, 0, HORIZ, '6', FG)); // distance 0 with horizontal command
//    assert(plotLine(6, 7, 0, VERT, '$', BG)); // distance 0 with vertical command
//
//    //invalid
//    assert(!(plotLine(1, 1, 5, -2, 'a', FG))); // invalid dir parameter
//    assert(!(plotLine(1, 1, 5, HORIZ, 'i', 3))); // invalid fgbg parameter
//    assert(!(plotLine(15, 15, 6, HORIZ, 's', FG))); // plots outside the graph
//    assert(!(plotLine(21, 20, -3, VERT, 'v', FG))); // plots outside the graph
//    assert(!(plotLine(2, 2, 0, VERT, '\n', FG))); // fails isprint
//    draw();
//
//    /** PLOT LINE TEST #2 (SMALLBERG) */
//    setSize(20, 15);
//    if (!plotLine(14, 8, 3, HORIZ, '*', FG))
//        cout << "1) Plotting failed when it shouldn't have!" << endl;
//    if (!plotLine(15, 10, -2, VERT, '@', FG))  // second call
//        cout << "2) Plotting failed when it shouldn't have!" << endl;
//    if (!plotLine(13, 8, 3, HORIZ, '#', BG))   // third call
//        cout << "3) Plotting failed when it shouldn't have!" << endl;
//    if (plotLine(13, 14, 3, HORIZ, 'X', FG))     // fourth call
//        cout << "4) Plotting succeeded when it shouldn't have!" << endl;
//    draw();
//
//    /** PLOT LINE TEST #3 (SMALLBERG) */
//    setSize(2, 12);
//    assert(plotLine(1, 1, 0, HORIZ, 'H', FG));
//    assert(plotLine(1, 2, 0, HORIZ, 'i', FG));
//    assert(plotLine(1, 3, 0, HORIZ, '!', FG));
//    draw();  // displays  Hi!  in the top row of the grid
//    assert(plotLine(1, 3, 0, HORIZ, ' ', FG));
//    draw();  // displays  Hi   in the top row of the grid
//    assert(plotLine(1, 1, 10, HORIZ, ' ', BG));
//    draw();  // displays  Hi   in the top row of the grid
//    assert( ! plotLine(1, 1, 10, HORIZ, '\n', FG));
//    draw();  // displays  Hi   in the top row of the grid
//
//    /** PERFORM COMMANDS TEST #1*/
//    setSize(15, 10);
//    char plotChar = '*';
//    int mode = FG;
//    int bad = 999;
//
//    // valid
//    assert(performCommands("", plotChar, mode, bad) == 0 && bad == 999); // empty string
//    assert(performCommands("V10F*H00H6v00", plotChar, mode, bad) == 0 && bad == 999); // calling horizontal and vertical with 00 distance
//    assert(performCommands("h03FAV06F%v0", plotChar, mode, bad) == 0 && bad == 999); // H03 and V06 should have the same effect as H3 and V6
//
//    // invalid
//    assert(performCommands("H76", plotChar, mode, bad) == 3 && bad == 0); // syntantically valid but should not plot
//    assert(performCommands("h000", plotChar, mode, bad) == 1 && bad == 3); // horizontal command with 3 digit character
//    assert(performCommands("V123", plotChar, mode, bad) == 1 && bad == 3); // horizontal command with 3 digit character
//    draw();
//
//    /** PERFORM COMMANDS TEST #2*/
//    setSize(5, 5);
//    plotChar = '*';
//    mode = FG;
//    bad = 999;
//
//    // invalid
//    assert(performCommands("H5V4", plotChar, mode, bad) == 3 && bad == 0); // attempts to plot outside graph
//    assert(performCommands("H4V-2", plotChar, mode, bad) == 3 && bad == 2); // attempts to plot outside graph
//    assert(performCommands("H-1fF3", plotChar, mode, bad) == 1 && bad == 5); // starts a command with 3
//
//    // valid
//    assert(performCommands("f&H0V1", plotChar, mode, bad) == 0 && bad == 5); // should plot with 'F'
//    assert(performCommands("bhh1", plotChar, mode, bad) == 0 && bad == 5);
//    assert(performCommands("F9V3H2FbH-1", plotChar, mode, bad) == 0 && bad == 5); // negative horizontal distance
//    assert(performCommands("B@H4V3b(V-3", plotChar, mode, bad) == 0 && bad == 5); // negative vertical distance
//    assert(performCommands("", plotChar, mode, bad) == 0 && bad == 5); // empty string
//    draw();
//
//    /** PERFORM COMMANDS TEST #3 */
//    setSize(20, 30);
//    plotChar = '*';
//    mode = FG;
//    bad = 999;
//
//    // valid
//    assert(performCommands("bBH29V19", plotChar, mode, bad) == 0 && bad == 999); // background command plotChar is a command letter
//    assert(performCommands("cCcCh1v1", plotChar, mode, bad) == 0 && bad == 999); // command string includes clear command (4 times in a row)
//
//    // invalid
//    assert(performCommands("b\t", plotChar, mode, bad) == 1 && bad == 1); // non-printable character as the argument to b command
//    plotChar = '\t';
//    assert(performCommands("", plotChar, mode, bad) == 2 && bad == 1); // plotChar is a non-printable character
//    plotChar = '*';
//    mode = 3;
//    assert(performCommands("", plotChar, mode, bad) == 2 && bad == 1); // invalid mode
//    draw();
//
//    /** PERFORM COMMANDS TEST #4 (SMALLBERG) */
//    setSize(8, 20);
//    plotChar = '*';
//    mode = FG;
//    bad = 999;
//
//    // valid
//    assert(performCommands("h12V3H-1B@v-3", plotChar, mode, bad) == 0 && bad == 999);
//    draw();
//    assert(performCommands("v2b h12fHh1fih0", plotChar, mode, bad) == 0 && bad == 999);
//    draw();
//    assert(performCommands("CV6", plotChar, mode, bad) == 0 && bad == 999);
//    draw();
//
//    /** PERFORM COMMANDS TEST #5 (SMALLBERG) */
//    setSize(5, 30);
//    plotChar = '*';
//    mode = FG;
//    bad = 999;
//
//    // valid
//    assert(performCommands("H25H-10",plotChar,mode, bad) == 0 && bad == 999);
//
//    // invalid
//    assert(performCommands("H25,H-10", plotChar, mode, bad) == 1 && bad == 3);
//    assert(performCommands("H25 H-10", plotChar, mode, bad) == 1 && bad == 3);
//    assert(performCommands("H+25H-10", plotChar, mode, bad) == 1 && bad == 1);
//    draw();
//
//    /** PERFORM COMMANDS TEST #6 (SMALLBERG) */
//    setSize(5, 5);
//    plotChar = '*';
//    mode = FG;
//    bad = 999;
//
//    // invalid
//    assert(performCommands("F#H+25H?V3!", plotChar, mode, bad) == 1 && bad == 3);
//    assert(performCommands("B@H", plotChar, mode, bad) == 1 && bad == 3);
//    assert(performCommands("C12", plotChar, mode, bad) == 1 && bad == 1);
//    assert(performCommands("Q3V4#", plotChar, mode, bad) == 1 && bad == 0);
//    assert(performCommands("V03C H123#", plotChar, mode, bad) == 1 && bad == 4);
//    assert(performCommands("H18H-123#", plotChar, mode, bad) == 1 && bad == 7);
//    assert(performCommands("H5H-1-2", plotChar, mode, bad) == 1 && bad == 5);
//    assert(performCommands("FH8", plotChar, mode, bad) == 1 && bad == 2);
//    draw();
//
//    /** PERFORM COMMANDS TEST #7 (SMALLBERG) */
//    setSize(20, 30);
//    plotChar = '*';
//    mode = FG;
//    bad = 999;
//
//    assert(performCommands("H28V10H5V86", plotChar, mode, bad) == 3 && bad == 6);
//    assert(performCommands("H23F/t", plotChar, mode, bad) == 1 && bad == 5);
//    assert(performCommands("H23F\t", plotChar, mode, bad) == 1 && bad == 4);
//    assert(performCommands("H2V3H99V2F\tH3", plotChar, mode, bad) == 1 && bad == 10);
//    draw();
//}

//Person 1's Test Cases:
//int main() {
//    char plotChar = '*';
//    int mode = FG;
//    int badPos = 999;
//    setSize(20, 30);
//    
//    //PLOT LINE
//    assert(plotLine(10, 10, 4, HORIZ, '*', FG) == true);//plots a line horiz pos
//    assert(plotLine(10, 10, -4, HORIZ, '*', FG) == true);//plots a line horiz neg
//    assert(plotLine(10, 10, 4, VERT, '*', FG) == true);//plots a line vert pos
//    assert(plotLine(10, 10, -4, VERT, '*', FG) == true);//plots a line vert neg
//    assert(plotLine(1, 1, 4, HORIZ, '#', FG) == true);//background & foreground
//    assert(plotLine(1, 1, 4, HORIZ, '\n', FG) == false);//invalid plot char
//    assert(plotLine(1, 1, 4, HORIZ, '*', 3) == false);//invalid fgbg
//    assert(plotLine(1, 1, 5, 10, '*', FG) == false);//invalid direction
//    assert(plotLine(1, 1, 40, HORIZ, '*', FG) == false);//going out of bounds
//    
//    //COMMAND SYNTAX
//    assert(performCommands("v50b\n", plotChar, mode, badPos) == 1 && badPos == 4);//character change is not valid
//    assert(performCommands("v5b", plotChar, mode, badPos) == 1 && badPos == 3); //instruction setting mode is missing
//    assert(performCommands("vg", plotChar, mode, badPos) == 1 && badPos == 1);  //instruction distance after h or v not valid
//    assert(performCommands("v10h3cf#H10", plotChar, mode, badPos) == 0);//can clear
//    assert(performCommands("v-h", plotChar, mode, badPos) == 1 && badPos == 2);//invalid instruction character
//    assert(performCommands("", plotChar, mode, badPos) == 0);//empty string is valid
//    assert(performCommands("B@H-", plotChar, mode, badPos) == 1 && badPos == 4);//missing character at end
//    
//    //CHECKING IN GRID
//    assert(performCommands("h50", plotChar, mode, badPos) == 3);//outside of bounds horiz positive
//    assert(performCommands("h-50", plotChar, mode, badPos) == 3);//outside of bounds horiz negative
//    assert(performCommands("v50", plotChar, mode, badPos) == 3);//outside of bounds vert positive
//    assert(performCommands("v-50", plotChar, mode, badPos) == 3);//outside of bounds vert negative
//    
//    //DRAWING
//    assert(performCommands("v6", plotChar, mode, badPos) == 0); //one digit vertical command
//    assert(performCommands("h8", plotChar, mode, badPos) == 0); //one digit horizontal command
//    assert(performCommands("h14H-3", plotChar, mode, badPos) == 0); //one digit negative horizontal command
//    assert(performCommands("V10v-2", plotChar, mode, badPos) == 0); //one digit negative vertical command
//    assert(performCommands("h18", plotChar, mode, badPos) == 0); //two digit horizontal command
//    assert(performCommands("V18", plotChar, mode, badPos) == 0); //two digit horizontal command
//    assert(performCommands("h10h-10", plotChar, mode, badPos) == 0); //two digit negative horizontal command
//    assert(performCommands("v10v-10", plotChar, mode, badPos) == 0); //two digit negative vertical command
//
//    draw();
//}

// Andrew’s test cases
int main() {
    
    // MARK: - Test `plotLine`
    setSize(8, 20);
    
    // MARK: - Single points, valid
    assert(plotLine(1, 1, 0, HORIZ, '*', FG) == true); // top left
    assert(plotLine(1, 20, 0, HORIZ, '*', FG) == true); // top right
    assert(plotLine(8, 1, 0, HORIZ, '*', FG) == true); // bottom left
    assert(plotLine(8, 20, 0, HORIZ, '*', FG) == true); // bottom right
    
    // MARK: - Single points vertical, inset, valid
    assert(plotLine(2, 2, 0, VERT, '#', FG) == true); // top left
    assert(plotLine(2, 19, 0, VERT, '#', FG) == true); // top right
    assert(plotLine(7, 2, 0, VERT, '#', FG) == true); // bottom left
    assert(plotLine(7, 19, 0, VERT, '#', FG) == true); // bottom right
    
    // MARK: - Horizontal lines, valid
    assert(plotLine(3, 1, 4, HORIZ, 'X', FG) == true); // 5 characters wide
    assert(plotLine(3, 10, 10, HORIZ, 'X', FG) == true); // hits the right edge
    assert(getChar(3, 10) == 'X'); // make sure the start is drawn
    assert(getChar(3, 20) == 'X'); // make sure the end is drawn
    
    // MARK: - Vertical lines, valid
    assert(plotLine(1, 7, 2, VERT, '@', FG) == true); // 3 characters tall
    assert(plotLine(7, 7, 1, VERT, '@', FG) == true); // 2 characters tall, hits the bottom edge
    
    // MARK: - Negative distance
    assert(plotLine(4, 20, -19, HORIZ, '<', FG) == true); // starting from the right edge to the left
    assert(plotLine(8, 4, -7, VERT, '^', FG) == true); // starting from the bottom to the top
    
    // MARK: - Background lines
    assert(plotLine(1, 14, 7, VERT, '$', BG) == true); // crosses under the X line
    assert(getChar(2, 14) == '$'); // it used to be empty, so now it's changed to '$'
    assert(getChar(3, 14) == 'X'); // drew in background, so now it should still be 'X'
    
    assert(plotLine(6, 1, 19, HORIZ, '&', BG) == true); // underneath the vertical line that was just drawn
    assert(getChar(6, 13) == '&'); // it used to be empty, so now it's changed to '$'
    assert(getChar(6, 14) == '$'); // drew in background, so now it should still be 'X'
    
    
    // MARK: - Invalid lines
    assert(plotLine(0, 0, 0, HORIZ, '&', FG) == false); // out of bounds
    assert(plotLine(0, -1, 5, HORIZ, '&', FG) == false); // negative (out of bounds)
    assert(plotLine(1, 1, 20, HORIZ, '&', FG) == false); // too wide
    assert(plotLine(1, 1, 8, VERT, '&', FG) == false); // too tall
    assert(plotLine(1, 1, 3, HORIZ, '\n', FG) == false); // non-printable char
    assert(plotLine(1, 1, 3, HORIZ, '\t', BG) == false); // another non-printable char
    
    clearGrid();
    
    // MARK: - Test `performCommands`
    char plotChar = '*';
    int badPos = 999;
    int mode = FG;
    
    // MARK: - Valid commands (returns 0)
    assert(performCommands("h12V3H-1B@v-3", plotChar, mode, badPos) == 0 && badPos == 999); // combination of H, V, and Background
    assert(performCommands("v2b h12fHh1fih0", plotChar, mode, badPos) == 0 && badPos == 999); // draws the word "Hi"
    assert(performCommands("h19v7h-19v-6", plotChar, mode, badPos) == 0 && badPos == 999); // rectangle along edges
    assert(performCommands("H19V7", plotChar, mode, badPos) == 0 && badPos == 999); // capital letters
    assert(performCommands("h19v7", plotChar, mode, badPos) == 0 && badPos == 999); // lowercase letters
    assert(performCommands("f h3", plotChar, mode, badPos) == 0 && badPos == 999); // "erase" existing characters with whitespace character
    assert(performCommands("b v2", plotChar, mode, badPos) == 0 && badPos == 999); // "move" brush down first in the background
    assert(performCommands("b v2f@h5", plotChar, mode, badPos) == 0 && badPos == 999); // move brush down then draw to the right
    assert(performCommands("b v3b@h5", plotChar, mode, badPos) == 0 && badPos == 999); // move brush down then draw to the right (in background)
    assert(performCommands("h19v7h-19v-6ch2", plotChar, mode, badPos) == 0 && badPos == 999); // test clear command
    assert(getChar(1, 20) == ' '); // the rectangle's top right should have been cleared
    assert(getChar(1, 3) == '*'); // after clearing the rectangle, we drew some asterisks at the top left
    assert(performCommands("", plotChar, mode, badPos) == 0 && badPos == 999); // empty string should also work
    
    // MARK: - Syntax errors (returns 1)
    assert(performCommands("F#H+25H?V3!", plotChar, mode, badPos) == 1 && badPos == 3); // leftmost syntax error
    assert(performCommands("B@H", plotChar, mode, badPos) == 1 && badPos == 3); // expecting - or digit after H
    assert(performCommands("C12", plotChar, mode, badPos) == 1 && badPos == 1); // C is one command; 1 can't start a command
    assert(performCommands("Q3V4#", plotChar, mode, badPos) == 1 && badPos == 0); // Q can't start a command
    assert(performCommands("V03C H123#", plotChar, mode, badPos) == 1 && badPos == 4); // space can't start a command
    assert(performCommands("H18H-123#", plotChar, mode, badPos) == 1 && badPos == 7); // H-12 is one command; 3 can't start a command
    assert(performCommands("H5H-1-2", plotChar, mode, badPos) == 1 && badPos == 5); // H-1 is one command; - can't start a command
    assert(performCommands("FH8", plotChar, mode, badPos) == 1 && badPos == 2); // FH is one command; 8 can't start a command
    assert(performCommands("H\n", plotChar, mode, badPos) == 1 && badPos == 1); // the horizontal brush char is set to a non-printable character
    assert(performCommands("H4V\n", plotChar, mode, badPos) == 1 && badPos == 3); // the vertical brush char is set to a non-printable character
    assert(performCommands("v4b\n", plotChar, mode, badPos) == 1 && badPos == 3); // changing to background with a non-printable character
    assert(performCommands("V99F", plotChar, mode, badPos) == 1 && badPos == 4); // there is an out of bounds error, but the syntax error at the end takes precedence
    assert(performCommands(" ", plotChar, mode, badPos) == 1 && badPos == 0); // blank space, which isn't a valid command
    assert(performCommands(" H19V7", plotChar, mode, badPos) == 1 && badPos == 0); // starting with a space, but the rest is valid
    assert(performCommands("H19 V7", plotChar, mode, badPos) == 1 && badPos == 3); // extra space in the middle
    assert(performCommands("H19,V7", plotChar, mode, badPos) == 1 && badPos == 3); // extra comma in the middle
    assert(performCommands("H19V ", plotChar, mode, badPos) == 1 && badPos == 4); // missing value after the vertical command
    assert(performCommands("H19V--", plotChar, mode, badPos) == 1 && badPos == 5); // the second negative is invalid
    assert(performCommands("H19V-1-2", plotChar, mode, badPos) == 1 && badPos == 6); // duplicate values, report the bad position of the second one
    
    // MARK: - Invalid input (returns 2)
    badPos = 999; // reset bad position to initial
    mode = FG; // reset to FG
    
    plotChar = '\n'; // set to non-printable char
    assert(performCommands("h19v7h-19v-6", plotChar, mode, badPos) == 2 && badPos == 999); // non-printable char
    plotChar = '*'; // reset
    
    mode = 100;
    assert(performCommands("h19v7h-19v-6", plotChar, mode, badPos) == 2 && badPos == 999); // invalid mode/fgbg value (not 0 or 1)
    mode = FG; // reset to FG
    
    // MARK: - Out of bounds (returns 3)
    assert(performCommands("h20", plotChar, mode, badPos) == 3 && badPos == 0); // one too much to the right
    assert(performCommands("v-2", plotChar, mode, badPos) == 3 && badPos == 0); // drew out of bounds to the top
    assert(performCommands("h20h-20", plotChar, mode, badPos) == 3 && badPos == 0); // multiple errors, return position of the first one (0)
    assert(performCommands("h19v-99", plotChar, mode, badPos) == 3 && badPos == 3); // horizontal command is fine but vertical one draws out of bounds
}
