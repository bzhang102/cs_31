#include "grid.h"
#include <cctype>
#include <cassert>

const int HORIZ = 0;
const int VERT = 1;

const int FG = 0;
const int BG = 1;

//state variables
int currR;
int currC;
int currMode;
char currChar;

void plotHorizontalLine(int r, int c, int distance, char ch) {
    //checks if plotting too high or too low
    if(distance < 0 || r > getRows() || r < 1) {
        return;
    }
    
    while(distance >= 0) {
        //checks if plotting within grid
        if(c <= getCols() && c >= 1) {
            setChar(r, c, ch);
            cout << "here" << endl;
        }
        c++;
        distance--;
    }
}

void plotVerticalLine(int r, int c, int distance, char ch) {
    //checks if plotting too far left or right
    if(distance < 0 || c > getCols() || c < 1) {
        return;
    }
    
    while(distance >= 0) {
        //checks if plotting within grid
        if(r <= getRows() && r >= 1) {
            setChar(r, c, ch);
        }
        r++;
        distance--;
    }
}

void plotRectangle(int r, int c, int height, int width, char ch) {
    //checks if triangle size invalid
    if(height < 0 || width < 0) {
        return;
    }
    
    plotHorizontalLine(r, c, width, ch);
    plotHorizontalLine(r + height, c, width, ch);
    plotVerticalLine(r, c, height, ch);
    plotVerticalLine(r, c + width, height, ch);
}

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

//TODO
//int processH(string commandString, char& plotChar, int& mode, int& badPos) {
//    badPos++;
//    
//    return 0;
//}
//
//int processV(string commandString, char& plotChar, int& mode, int& badPos) {
//    badPos++;
//    
//    return 0;
//}

//Sets mode to FG and changes current character
int processF(string commandString, char& plotChar, int& badPos) {
    badPos++;
    if(!isprint(commandString.at(badPos))) {
        return 1;
    }
    
    currMode = FG;
    currChar = plotChar;
    
    return 0;
}

//Sets mode to BG and changes current character
int processB(string commandString, char& plotChar, int& badPos) {
    badPos++;
    if(!isprint(commandString.at(badPos))) {
        return 1;
    }
    
    currMode = BG;
    currChar = plotChar;
    
    return 0;
}

//clears board and sets variables to default
int processC() {
    clearGrid();
    currR = 1;
    currC = 1;
    currChar = '*';
    currMode = FG;
    
    return 0;
}

//function implementation
int performCommands(string commandString, char& plotChar, int& mode, int& badPos) {
    //checks if character is plotable and modes are valid
    if(!isprint(plotChar) || mode != FG || mode != BG) {
        return 2;
    }
    
    //sets variables to default
    currR = 1;
    currC = 1;
    currMode = mode;
    
    char curr;
    int state = 0;
    
    //reads and executes command string
    while(badPos != commandString.size()) {
        curr = tolower(commandString.at(badPos));
        
        switch(curr) {
            case 'h':
                state = processH(commandString, plotChar, mode, badPos);
                break;
            case 'v':
                state = processV(commandString, plotChar, mode, badPos);
                break;
            case 'f':
                state = processF(commandString, plotChar, badPos);
                break;
            case 'b':
                state = processB(commandString, plotChar, badPos);
                break;
            case 'c':
                state = processC();
                break;
            default:
                state = 1;
        }
        
        //if in error state, return error code
        if(state != 0) {
            return state;
        }
        
        //move pointer to next character
        badPos++;
    }
    
    return 0;
}
