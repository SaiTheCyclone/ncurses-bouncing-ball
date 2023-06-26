#include <array>
#include <ncurses.h>
#include <random>

#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4

void moveBall(std::array<int, 2>& ballYX, int directionY, int directionX)
{
    if (directionY == UP)
        --ballYX[0];
    else if (directionY == DOWN)
        ++ballYX[0];

    if (directionX == LEFT)
        --ballYX[1];
    else if (directionX == RIGHT)
        ++ballYX[1];
}

void checkCollision(std::array<int, 2> ballYX, int& directionY,
    int& directionX)
{
    if (ballYX[0] == LINES - 1)
        directionY = UP;
    else if (ballYX[0] == 0)
        directionY = DOWN;

    if (ballYX[1] == COLS - 1)
        directionX = LEFT;
    else if (ballYX[1] == 0)
        directionX = RIGHT;
}

std::array<int, 2> getRandomYX()
{
    std::random_device rd {};
    std::seed_seq ss      { rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    std::mt19937 mt       { ss };

    std::uniform_int_distribution rangeY { 0, LINES - 1 };
    std::uniform_int_distribution rangeX { 0, COLS - 1 };
    return { rangeY(mt), rangeX(mt) };
}

void startWindow()
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);
    intrflush(stdscr, true);
    curs_set(0);
}

int main()
{
    startWindow();

    constexpr char ballBody   { 'O' };
    std::array<int, 2> ballYX { getRandomYX() };
    int directionY            { DOWN };
    int directionX            { RIGHT };

    timeout(100);
    while (getch() != 'q')
    {
        clear();
        checkCollision(ballYX, directionY, directionX);
        moveBall(ballYX, directionY, directionX);
        attron(A_BOLD);
        mvaddch(ballYX[0], ballYX[1], ballBody);
        attroff(A_BOLD);
    }

    endwin();
    return 0;
}