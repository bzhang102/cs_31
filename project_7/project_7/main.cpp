#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20; // max number of rows in a city
const int MAXCOLS = 30; // max number of columns in a city
const int MAXTOOTERS = 125; // max number of Tooters allowed

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class City;  // This is needed to let the compiler know that City is a
// type name, since it's mentioned in the Tooter declaration.

class Tooter {
    public:
        // Constructor
        Tooter(City* cp, int r, int c);
        // Accessors
        int row() const;
        int col() const;
        // Mutators
        void move();

    private:
        City* m_city;
        int m_row;
        int m_col;
};

class Player {
    public:
        // Constructor
        Player(City *cp, int r, int c);
        // Accessors
        int row() const;
        int col() const;
        int age() const;
        int health() const;
        bool isPassedOut() const;
        // Mutators
        void preach();
        void move(int dir);
        void getGassed();

    private:
        City* m_city;
        int m_row;
        int m_col;
        int m_age;
        int m_health;
};

class City {
    public:
        // Constructor/destructor
        City(int nRows, int nCols);
        ~City();
        // Accessors
        int rows() const;
        int cols() const;
        Player* player() const;
        bool isPlayerAt(int r, int c) const;
        int tooterCount() const;
        int nTootersAt(int r, int c) const;
        bool determineNewPosition(int& r, int& c, int dir) const;
        void display() const;
        // Mutators
        bool addTooter(int r, int c);
        bool addPlayer(int r, int c);
        void preachToTootersAroundPlayer();
        void moveTooters();

    private:
        int m_rows;
        int m_cols;
        Player* m_player;
        Tooter* m_tooters[MAXTOOTERS];
        int m_nTooters;

        // Helper functions
        bool isInBounds(int r, int c) const;
};

class Game {
    public:
        // Constructor/destructor
        Game(int rows, int cols, int nTooters);
        ~Game();
        // Mutators
        void play();

    private:
        City* m_city;
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Tooter implementation
///////////////////////////////////////////////////////////////////////////

Tooter::Tooter(City* cp, int r, int c) {
    if(cp == nullptr) {
        cout << "***** A Tooter must be created in some City!" << endl;
        exit(1);
    }
    if(r < 1 || r > cp->rows() || c < 1 || c > cp->cols()) {
        cout << "***** Tooter created with invalid coordinates (" << r << "," << c << ")!" << endl;
        exit(1);
    }
    m_city = cp;
    m_row = r;
    m_col = c;
}

int Tooter::row() const {
    return m_row;
}

int Tooter::col() const {
    return m_col;
}

void Tooter::move() {
    // Attempt to move in a random direction; if nit can't move, don't move.
    // if the player is there, don't move.
    int dir = randInt(0, NUMDIRS-1);  // dir is now UP, DOWN, LEFT, or RIGHT
    if(dir == UP && !m_city->isPlayerAt(m_row - 1, m_col)) {
        m_city->determineNewPosition(m_row, m_col, dir);
    } else if(dir == DOWN && !m_city->isPlayerAt(m_row + 1, m_col)) {
        m_city->determineNewPosition(m_row, m_col, dir);
    } else if(dir == LEFT && !m_city->isPlayerAt(m_row, m_col - 1)) {
        m_city->determineNewPosition(m_row, m_col, dir);
    } else if(dir == RIGHT && !m_city->isPlayerAt(m_row, m_col + 1)) {
        m_city->determineNewPosition(m_row, m_col, dir);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(City* cp, int r, int c) {
    if(cp == nullptr) {
        cout << "***** The player must be created in some City!" << endl;
        exit(1);
    }
    if(r < 1  ||  r > cp->rows()  ||  c < 1  ||  c > cp->cols()) {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_city = cp;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_health = 100;
}

int Player::row() const {
    return m_row;
}

int Player::col() const {
    return m_col;
}

int Player::age() const {
    return m_age;
}

int Player::health() const {
    return m_health;
}

bool Player::isPassedOut() const {
    return m_health <= 0;
}

void Player::preach() {
    m_age++;
    m_city->preachToTootersAroundPlayer();
}

void Player::move(int dir) {
    m_age++;
    if(dir == UP && m_city->nTootersAt(m_row - 1, m_col) == 0) {
        m_city->determineNewPosition(m_row, m_col, dir);
    } else if(dir == DOWN && m_city->nTootersAt(m_row + 1, m_col) == 0) {
        m_city->determineNewPosition(m_row, m_col, dir);
    } else if(dir == LEFT && m_city->nTootersAt(m_row, m_col - 1) == 0) {
        m_city->determineNewPosition(m_row, m_col, dir);
    } else if(dir == RIGHT && m_city->nTootersAt(m_row, m_col + 1) == 0) {
        m_city->determineNewPosition(m_row, m_col, dir);
    }
}

void Player::getGassed() {
    m_health--;
}

///////////////////////////////////////////////////////////////////////////
//  City implementations
///////////////////////////////////////////////////////////////////////////

City::City(int nRows, int nCols) {
    if(nRows <= 0 || nCols <= 0 || nRows > MAXROWS || nCols > MAXCOLS) {
        cout << "***** City created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nTooters = 0;
}

City::~City() {
    delete m_player;
    for(int i = 0; i < m_nTooters; i++) {
        delete m_tooters[i];
    }
}

int City::rows() const {
    return m_rows;
}

int City::cols() const {
    return m_cols;
}

Player* City::player() const {
    return m_player;
}

bool City::isPlayerAt(int r, int c) const {
    return m_player->row() == r && m_player->col() == c;
}

int City::tooterCount() const {
    return m_nTooters;
}

int City::nTootersAt(int r, int c) const {
    int count = 0;

    for(int i = 0; i < m_nTooters; i++) {
        if(m_tooters[i]->row() == r && m_tooters[i]->col() == c) {
            count++;
        }
    }

    return count;
}

bool City::determineNewPosition(int& r, int& c, int dir) const {
    switch (dir) {
        case UP:
            if(!isInBounds(r - 1, c)) {
                return false;
            }
            r--;
            break;
        case DOWN:
            if(!isInBounds(r + 1, c)) {
                return false;
            }
            r++;
            break;
        case LEFT:
            if(!isInBounds(r, c - 1)) {
                return false;
            }
            c--;
            break;
        case RIGHT:
            if(!isInBounds(r, c + 1)) {
                return false;
            }
            c++;
            break;
        default:
            return false;
    }
    return true;
}

void City::display() const {
    // Position (row,col) in the city coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;

    // Fill the grid with dots
    for(r = 0; r < rows(); r++) {
        for(c = 0; c < cols(); c++) {
            grid[r][c] = '.';
        }
    }

    // Indicate each Tooter's position
    for(int i = 0; i < m_nTooters; i++) {
        char& curr = grid[m_tooters[i]->row() - 1][m_tooters[i]->col() - 1];
        if(curr == '.') {
            curr = 'T';
        } else if(curr == 'T') {
            curr = '2';
        } else if(curr != '9') {
            curr++;
        }
    }

    // Indicate player's position
    if(m_player != nullptr) {
        // Set the char to '@', unless there's also a Tooter there
        // (which should never happen), in which case set it to '*'.
        char& gridChar = grid[m_player->row() - 1][m_player->col() - 1];
        if(gridChar == '.') {
            gridChar = '@';
        } else {
            gridChar = '*';
        }
    }

    // Draw the grid
    clearScreen();
    for(r = 0; r < rows(); r++) {
        for(c = 0; c < cols(); c++) {
            cout << grid[r][c];
        }
        cout << endl;
    }
    cout << endl;

    // Write message, Tooter, and player info
    cout << "There are " << m_nTooters << " unconverted Tooters remaining." << endl;
    if(m_player == nullptr) {
        cout << "There is no player." << endl;
    } else {
        if(m_player->age() > 0) {
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        }
        if(m_player->isPassedOut()) {
            cout << "The player has passed out." << endl;
        } else {
            cout << "The player's health level is " << m_player->health() << endl;
        }
    }
}

bool City::addTooter(int r, int c) {
    if(!isInBounds(r, c)) {
        return false;
    }
    // Don't add a Tooter on a spot with a player
    if(m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c) {
        return false;
    }

    if(m_nTooters >= MAXTOOTERS) {
        return false;
    }

    m_tooters[m_nTooters] = new Tooter(this, r, c);
    m_nTooters++;
    return true;
}

bool City::addPlayer(int r, int c) {
    if(!isInBounds(r, c)) {
        return false;
    }

    // Don't add a player if one already exists
    if(m_player != nullptr) {
        return false;
    }

    // Don't add a player on a spot with a Tooter
    if(nTootersAt(r, c) != 0) {
        return false;
    }

    // Dynamically allocate a new Player and add it to the city
    m_player = new Player(this, r, c);
    return true;
}

void City::preachToTootersAroundPlayer() {
    // Preach to Tooters orthogonally or diagonally adjacent to player.
    // if a Tooter is converted, destroy it and remove it from the city,
    // since we have no further need to display it or have it interact with
    // the player.
    for(int i = 0; i < m_nTooters; i++) {
        if((abs(m_tooters[i]->row() - m_player->row()) <= 1 && (m_tooters[i]->col() - m_player->col() == 0)) || (abs(m_tooters[i]->col() - m_player->col()) <= 1 && (m_tooters[i]->row() - m_player->row() == 0))) {
            // 2/3 chance to convert this tooter
            if(randInt(1,9) <= 6) {
                delete m_tooters[i];
                m_nTooters--;
                for(int j = i; j < m_nTooters; j++) {
                    m_tooters[j] = m_tooters[j + 1];
                }
                m_tooters[m_nTooters] = nullptr;
            }
        }
    }
}

void City::moveTooters() {
    for(int i = 0; i < m_nTooters; i++) {
        m_tooters[i]->move();
        if((abs(m_tooters[i]->row() - m_player->row()) <= 1 && (m_tooters[i]->col() - m_player->col() == 0)) || (abs(m_tooters[i]->col() - m_player->col()) <= 1 && (m_tooters[i]->row() - m_player->row() == 0))) {
            m_player->getGassed();
        }
    }
}

bool City::isInBounds(int r, int c) const {
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nTooters) {
    if(nTooters < 0) {
        cout << "***** Cannot create Game with negative number of Tooters!" << endl;
        exit(1);
    }
    if(nTooters > MAXTOOTERS) {
        cout << "***** Trying to create Game with " << nTooters
        << " Tooters; only " << MAXTOOTERS << " are allowed!" << endl;
        exit(1);
    }
    if(rows == 1  &&  cols == 1  &&  nTooters > 0) {
        cout << "***** Cannot create Game with nowhere to place the Tooters!" << endl;
        exit(1);
    }

    // Create city
    m_city = new City(rows, cols);

    // Add a player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_city->addPlayer(rPlayer, cPlayer);

    // Populate with Tooters
    while (nTooters > 0) {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        // Don't put a Tooter where the player is
        if(r == rPlayer && c == cPlayer) {
            continue;
        }
        m_city->addTooter(r, c);
        nTooters--;
    }
}

Game::~Game() {
    delete m_city;
}

void Game::play() {
    m_city->display();
    Player* p = m_city->player();
    if(p == nullptr) {
        return;
    }

    while(!p->isPassedOut() && m_city->tooterCount() > 0) {
        cout << "Move (u/d/l/r//q): ";
        string action;
        getline(cin,action);
        if(action.size() == 0) { // player preaches
            p->preach();
        } else {
            switch (action[0]) {
                default:   // if bad move, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                case 'q':
                    return;
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    p->move(decodeDirection(action[0]));
                    break;
            }
        }
        m_city->moveTooters();
        m_city->display();
    }
    if(p->isPassedOut()) {
        cout << "You lose." << endl;
    } else {
        cout << "You win." << endl;
    }
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir) {
    switch (dir) {
        case 'u':  return UP;
        case 'd':  return DOWN;
        case 'l':  return LEFT;
        case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

// Return a random int from min to max, inclusive
int randInt(int min, int max) {
    if(max < min) {
        swap(max, min);
    }
    static random_device rdv;
    static default_random_engine generator(rdv());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main() {
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 10);

    // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANYTHING BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE forVISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window ifyou launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _WIN32  //  Windows

#pragma warning(disable : 4005)
#include <windows.h>

void clearScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Windows

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen() {  // will just write a newline in an Xcode output window
    static const char* term = getenv("TERM");
    if(term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif
