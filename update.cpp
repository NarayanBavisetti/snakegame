#include <iostream>
#include <cstdlib>
#include <ctime>
#include <process.h>
//all to control the position of the cursor
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <vector>
#include<fstream>
#define width 60
#define height 30

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
    pos.X = rand() % ((width - 2) + 1); //rand % (u-(l+1))+l
    pos.Y = rand() % ((height - 2) + 1);
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
    int score;
    char direction;
    vector<COORD> body;

public:
    //vector<COORD> body;
    Snake(COORD pos, int vel); //constructor
    void change_dir(char dir);
    void move_snake();
    COORD get_pos();
    vector<COORD> get_body();
    bool eaten(COORD food_pos);
    void grow();
    bool collided();
    //bool collided1();
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
        score += 10;
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

    body.push_back(pos);
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

    body.push_back(pos);
    if (body.size() > len)
        body.erase(body.begin());
}
COORD Snake::get_pos()
{
    return pos;
}

vector<COORD> Snake::get_body()
{
    return body;
}

//these are macros

Snake snake({width / 2, height / 2}, 1);

Food food;

void board()
{

    COORD snake_pos = snake.get_pos();
    COORD food_pos = food.get_pos();

    vector<COORD> snake_body = snake.get_body();
    cout<<"\n\n";
    for (int i = 0; i < height; i++)
    {
         
        cout << "\t\t#";
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1)
            {
                cout << "#";
            }
            else if (i == food_pos.Y && j == food_pos.X)
            {
                cout << "@";
                // if (food_pos.X==1 || food_pos.X==width || food_pos.Y==1 || food_pos.Y==height)
                // {
                //     food.gen_food();
                //  }
            }
            else
            {
                bool isbodypart = false;
                for (int k = 0; k < snake_body.size(); k++)
                {
                    if (i == snake_body[k].Y && j == snake_body[k].X)
                    {
                        cout << '0';
                        isbodypart = true;
                        break;
                    }
                }
                if (!isbodypart)
                {
                    cout << " ";
                }
            }
        }
        cout << "#" << endl;
    }
}

bool Snake::collided()
{
    //vector<COORD> sn_body = snake.get_body();
    if (pos.X < 1 || pos.X > width || pos.Y < 1 || pos.Y > height)
    {
        return true;
    }
    /*for(int i=0;i>len-1;i++)
    {
        if( pos.X==sn_body[i].X && pos.Y==sn_body[i].Y)
        {
            return true;
        }
    }*/
    return false;
}
/*bool Snake::collided1()
{
    for(int i=0;i>len-1;i++)
    {
        if( pos.X==body[i].X && pos.Y==body[i].Y)
        {
            return true;
        }
    }
    return false;
}*/

void starting()
{
    system("cls");
    string var =" \n\n\n\n\n\n\n\n\t\t\t\t Welcome to Snake Game";
    for (int i = 0; i < 35; i++)
    {
        cout << var[i];
        Sleep(200);
    }
}

void Name(char name[])
{
    string var = "\n\n\n\n\n\n\n\n\t\t\t\t Please Enter Your Name:";
    for (int i = 0; i < 36; i++)
    {
        cout << var[i];
        Sleep(20);
    }
    gets(name);
}

void updatescore(char name[],int score)
{
    ofstream fout("score.txt",ios::app);
    fout<<"\n"<<name<<"\t"<<score;
    system("cls");
    cout<<"Your Score :"<<score;
}
void highscore()
{
    char ch;
    ifstream fin;
    fin.open("score.txt",ios::in);
    
    while(fin)
    {
        fin.get(ch);
        cout<<ch;
    }
    cout<<"\npress any key to continue...";
    getch();
}
int main()
{ //generating random food
    srand(time(NULL));
    system("color A0");
    char name[30];
    starting();
    system("cls");
    Name(name);
    // board();
    int c = 1,score=0;
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
            case 'x': updatescore(name,score);
                highscore();
                exit(0);
                break;
            case 'p': getch();
                break;
                
            }
        }
        snake.move_snake();

        if (snake.eaten(food.get_pos()))
        {
            food.gen_food();
            snake.grow();
            score+=10;
        }
        if (snake.collided())
        {
            updatescore(name,score);
            highscore();
            exit(0); //game_over = true;
        }
        cout<<"score:"<<score;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
        if (c == 1)
        {
            system("cls");
            c++;
        }
    }
}