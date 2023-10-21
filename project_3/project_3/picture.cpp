#include "grid.h"
#include <cctype>
#include <cassert>

const int HORIZ = 0;
const int VERT = 1;

const int FG = 0;
const int BG = 1;

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

int main() {
    
}
