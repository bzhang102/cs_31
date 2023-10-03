#include "grid.h"

    int main()
    {
        setSize(15, 12);
        const int middleCol = getCols() / 2;
        setChar(6, middleCol, 'E');
        setChar(8, middleCol, 'L');
        setChar(9, middleCol, 'O');
        setChar(7, middleCol, 'L');
        setChar(5, middleCol, 'H');
        if (getChar(6, middleCol) == 'E')
            setChar(10, middleCol, '!');
        draw();
    }
