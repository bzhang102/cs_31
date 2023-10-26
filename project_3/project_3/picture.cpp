#include "grid.h"
#include <cctype>
#include <cassert>

const int HORIZ = 0;
const int VERT = 1;

const int FG = 0;
const int BG = 1;

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

//attempts to plot line
int processVH(string commandString, int dir, int& pos, int& currR, int& currC, char& plotChar, int&mode) {
    //advance pointer
    pos++;
    
    //check if pointer is at end of command string
    if(pos >= commandString.size()) {
        return 1;
    }
    
    /*
     Attempts to read next few lines:
     Case 1: If the first char is a '-', length is not incremented
     Case 2: One digit
     Case 3: Two digits
     */
    string input;
    int length = 0;
    while(pos < commandString.size() && (commandString.at(pos) == '-' || isdigit(commandString.at(pos))) && length < 2) {
        input += commandString.at(pos);
        
        //does not count '-' as part of two digits
        if(commandString.at(pos) != '-') {
            length++;
        }
        
        //advance pointer
        pos++;
    }
    
    int distance = stoi(input);
    //if plotting failed, return error code 3, else plot line
    if(!plotLine(currR, currC, distance, dir, plotChar, mode)) {
        return 3;
    }
    
    //updates current position (r, c)
    if(dir  == HORIZ) {
        currC += distance;
    } else {
        currR += distance;
    }
    
    return 0;
}

//Sets mode to FG or BG and changes current character
int processFB(string commandString, char& plotChar, int& mode, int newMode, int& pos) {
    //advance pointer
    pos++;
    
    //check if pointer is at end of command string
    if(pos == commandString.size()) {
        return 1;
    }
    
    //check if plotChar is plottable
    if(!isprint(commandString.at(pos))) {
        return 1;
    }
    
    //update mode and plotChar
    mode = newMode;
    plotChar = commandString.at(pos);
    
    return 0;
}

//clears board and sets variables to default
int processC(int& r, int& c, char& plotChar, int& mode) {
    clearGrid();
    r = 1;
    c = 1;
    plotChar = '*';
    mode = FG;
    
    return 0;
}

//function implementation
int performCommands(string commandString, char& plotChar, int& mode, int& badPos) {
    //checks if character is plotable and modes are valid
    if(!isprint(plotChar) || (mode != FG && mode != BG)) {
        return 2;
    }
    
    //sets position to default
    int currR = 1;
    int currC = 1;
    
    int state = 0;
    char curr = ' ';
    
    int pos = 0;
    int commandPos = 0;
    //reads and executes command string
    while(pos < commandString.size()) {
        curr = tolower(commandString.at(pos));
        commandPos = pos;
        
        switch(curr) {
            case 'h':
                state = processVH(commandString, HORIZ, pos, currR, currC, plotChar, mode);
                break;
            case 'v':
                state = processVH(commandString, VERT, pos, currR, currC, plotChar, mode);
                break;
            case 'f':
                state = processFB(commandString, plotChar, mode, FG, pos);
                break;
            case 'b':
                state = processFB(commandString, plotChar, mode, BG, pos);
                break;
            case 'c':
                state = processC(currR, currC, plotChar, mode);
                pos++;
                break;
            default:
                state = 1;
        }
        
        //if in error state, return error code
        if(state != 0 && state != 3) {
            badPos = pos;
            return state;
        }
        
        
        if(state == 3) {
            badPos = commandPos;
            return state;
        }
    }
    
    return 0;
}

int main()
    {
        setSize(12, 15);
        assert(plotLine(3, 5, 2, HORIZ, '@', FG));
        for (int c = 5; c <= 7; c++)
            assert(getChar(3, c) == '@');
        assert(getChar(3, 8) == ' ');
        clearGrid();
        char pc = '%';
        int m = FG;
        int bad = 999;

        assert(performCommands("H4V3V-1H-9", pc, m, bad) == 3  &&  bad == 7);
    draw();
        cout << "All tests succeeded." << endl;
    }

