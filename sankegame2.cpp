#include <iostream>
#include <cstdlib>
#include<ctime>
#include<process.h>
//all to control the position of the cursor
#include <windows.h>
#include <conio.h>
#define width 70
#define height 40

using namespace std;


class Food
{
private:
    COORD pos;

public:
    Food();
    void gen_food();
    COORD get_pos();

};

Food::Food()
{
    gen_food();
}


void Food::gen_food()
{
    //formula for generating rNDOM NO BTW U and L
    pos.X = rand() % (width + 3) -1;
    pos.Y = rand() % (height + 3) -1;
}


COORD Food::get_pos()
{
    return pos;
}

class Snake
{   
private:
    COORD pos;
    int len;
    int vel;
    char direction;

public:
    Snake(COORD pos, int vel); //constructor
    void change_dir(char dir);
    void move_snake();
    COORD get_pos();

    bool eaten(COORD food_pos);
    void grow();
    bool collided();
};

void Snake::grow()
{
    len++;
}

bool Snake::eaten(COORD food_pos)
{
    if (food_pos.X == pos.X && food_pos.Y == pos.Y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Snake::Snake(COORD pos, int vel)
{
    this->pos = pos;
    this->vel = vel;
    len = 1;
    direction = 'n';
}

void Snake::change_dir(char dir)
{
    direction = dir;
}

void Snake::move_snake()
{
    switch (direction)
    {
    case 'u':
        pos.Y -= vel;
        break;
    case 'd':
        pos.Y += vel;
        break;
    case 'l':
        pos.X -= vel;
        break;
    case 'r':
        pos.X += vel;
        break;
    }
}
COORD Snake::get_pos()
{
    return pos;
}

//these are macros

Snake snake({width / 2, height / 2}, 1);


Food food;

void board()
{

    COORD snake_pos = snake.get_pos();
    COORD food_pos = food.get_pos();

    for (int i = 0; i < height; i++)
    {
        cout << "#";
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1)
            {
                cout << "#";
            }
            else if (i == snake_pos.Y && j == snake_pos.X)
            {
                cout << "0";
            }
            else if (i == food_pos.Y && j == food_pos.X)
            {
                cout << "@";
            }
            else
            {
                cout << " ";
            }
        }
        cout << "#" << endl;
    }
}


bool Snake::collided(){
    if(pos.X <1 || pos.X >width){
        return true;
    }
    else {
        return false;
    }
}

int main()
{//generating random food
    // stand(time(NULL));
    // board();
    bool game_over = false;
    while (!game_over)
    {
        board();

        if (kbhit())
        {
            switch (getch())
            {
            case 'w':
                snake.change_dir('u');
                break;
            case 'a':
                snake.change_dir('l');
                break;
            case 's':
                snake.change_dir('d');
                break;
            case 'd':
                snake.change_dir('r');
                break;
                case'x':
                exit(0);
            }
        }
        snake.move_snake();

        if (snake.eaten(food.get_pos()))
        {
            food.gen_food();
            snake.grow();
        }
        if(snake.collided()){
            game_over = true;
            exit(0);
        }
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
    }
}