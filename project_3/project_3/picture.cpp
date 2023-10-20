#include "grid.h"

void plotHorizontalLine(int r, int c, int distance, char ch) {
    if(distance < 0 || r > getRows() || r < 1) {
        return;
    }
    
    while(distance >= 0) {
        if(c <= getCols() && c >= 1) {
            setChar(r, c, ch);
            cout << "here" << endl;
        }
        c++;
        distance--;
    }
}

void plotVerticalLine(int r, int c, int distance, char ch) {
    if(distance < 0 || c > getCols() || c < 1) {
        return;
    }
    
    while(distance >= 0) {
        if(r <= getRows() && r >= 1) {
            setChar(r, c, ch);
        }
        r++;
        distance--;
    }
}

void plotRectangle(int r, int c, int height, int width, char ch) {
    if(height < 0 || width < 0) {
        return;
    }
    
    plotHorizontalLine(r, c, width, ch);
    plotHorizontalLine(r + height, c, width, ch);
    plotVerticalLine(r, c, height, ch);
    plotVerticalLine(r, c + width, height, ch);
}


int main() {
    setSize(20, 30);
    plotRectangle(0, 0, 3, 3, 'X');
    draw();
}
