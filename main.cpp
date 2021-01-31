#include <iostream>
#include <ctime>
#include <vector>
#include <windows.h>

#define HEIGHT 20
#define WIDTH 40
#define FRAMERATE 10

class bodyPart
{
    public:
        char shape;
        int x, y;
        bodyPart(char shape, int x, int y)
        {
            this -> shape = shape;
            this -> x = x;
            this -> y = y;
        }
        bodyPart(char shape)
        {
            this -> shape = shape;
        }
};

class coordinates
{
    public:
        int x,y;
        coordinates(int x, int y)
        {
            this -> x = x;
            this -> y = y;
        }
};

class fClock
{
private:
    time_t initTime;
public:
    fClock()
    {
        initTime = clock();
    }
    void restart()
    {
        initTime = clock();
    }
    clock_t getElapsedTime()
    {
        return (clock() - initTime);
    }
};

char initChar, ScreenGrid[HEIGHT + 2][WIDTH + 2];
int direction = VK_RIGHT, fruitPosNum;
std::vector<bodyPart> Body;
std::vector<coordinates> spaces;
bodyPart Fruit('*');
fClock FRControl;

void clearGrid();
void addBody();
void addItem(bodyPart part);
void updatePartsLocation();
void draw();
void generateFruit();
void getKey();
void updateHeadLocation();
void gameOver();

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    srand((unsigned) time(0));
    Body.push_back(bodyPart('0', WIDTH/2, HEIGHT/2));
    for(int i = 0; i < 3; i++) Body.push_back(bodyPart('o', Body[0].x - (i+1), Body[0].y));
    clearGrid();
    addBody();
    generateFruit();
    while(true)
    {
        if(FRControl.getElapsedTime() >= (1000 / FRAMERATE))
        {
            FRControl.restart();
            if(Body[0].x == Fruit.x && Body[0].y == Fruit.y)
            {
                Body.push_back(bodyPart('o'));
                generateFruit();
            }
            getKey();
            updatePartsLocation();
            updateHeadLocation();
            if(Body[0].x == 0 || Body[0].x >= WIDTH + 1 || Body[0].y == 0 || Body[0].y >= HEIGHT + 1) gameOver();
            for(unsigned int i = 1; i < Body.size(); i++)
            {
                if(Body[0].x == Body[i].x && Body[0].y == Body[i].y) gameOver();
            }
            clearGrid();
            addItem(Fruit);
            addBody();
            system("cls");
            draw();
        }
    }
    return 0;
}

void clearGrid()
{
    for(int i = 0; i < HEIGHT + 2; i++)
    {
        if(i == 0 || i == HEIGHT + 1) initChar = '#';
        else initChar = ' ';
        for(int j = 0; j < WIDTH + 2; j++)
        {
            if(j == 0 || j == WIDTH + 1) ScreenGrid[i][j] = '#';
            else ScreenGrid[i][j] = initChar;
        }

    }
}

void draw()
{
    for(int i = 0; i < HEIGHT + 2; i++)
    {
        for(int j = 0; j < WIDTH + 2; j++)
            std::cout << ScreenGrid[i][j];
        std::cout << std::endl;
    }
}

void addBody()
{
    for(unsigned int i = 0; i < Body.size(); i++) ScreenGrid[Body[i].y][Body[i].x] = Body[i].shape;
}

void addItem(bodyPart part)
{
    ScreenGrid[part.y][part.x] = part.shape;
}

void updatePartsLocation()
{
    for(int i = Body.size() - 1; i > 0; i--)
    {
        Body[i].x = Body[i-1].x;
        Body[i].y = Body[i-1].y;
    }
}

void generateFruit()
{
    spaces.clear();
    for(int i = 1; i <= HEIGHT; i++)
    {
        for(int j = 1; j <= WIDTH; j++)
        {
            if(ScreenGrid[i][j] == ' ')
                spaces.push_back(coordinates(j, i));
        }
    }
    fruitPosNum = rand() % spaces.size();
    Fruit.x = spaces[fruitPosNum].x;
    Fruit.y = spaces[fruitPosNum].y;
}

void getKey()
{
    if(GetAsyncKeyState(VK_UP) && direction != VK_DOWN) direction = VK_UP;
    if(GetAsyncKeyState(VK_DOWN) && direction != VK_UP) direction = VK_DOWN;
    if(GetAsyncKeyState(VK_RIGHT) && direction != VK_LEFT) direction = VK_RIGHT;
    if(GetAsyncKeyState(VK_LEFT) && direction != VK_RIGHT) direction = VK_LEFT;
}

void updateHeadLocation()
{
    switch(direction)
    {
        case VK_UP:
            Body[0].y--;
            break;
        case VK_DOWN:
            Body[0].y++;
            break;
        case VK_RIGHT:
            Body[0].x++;
            break;
        case VK_LEFT:
            Body[0].x--;
            break;
    }
}

void gameOver()
{
    int Dots = 0;
    while(true)
    {
        if(FRControl.getElapsedTime() >= (1000 / FRAMERATE))
        {
            FRControl.restart();
            system("cls");
            std::cout << "\n\n\n\n\n\n\n\n\n\n                              ";
            std::cout << "*** GAME OVER ***\n\n\n\n\n\n\n\n                             press ENTER to exit\n                             ";
            for(int i=0; i<Dots; i++) std::cout << '.';
            std::cout << std::endl;
            if(Dots>=19) Dots=0;
            else Dots++;
        }
        if(GetAsyncKeyState(VK_RETURN)) exit(0);
    }
}


