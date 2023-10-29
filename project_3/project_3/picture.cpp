#include "grid.h"
#include <cctype>
#include <cassert>

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
