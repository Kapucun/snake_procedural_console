//основи програмування Си
// Консоль 
//Калифицкий М.О.
/*
игра "Питон"
*/
//20.05.2020

#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>

using namespace std;
const int sz = 30;
struct Snake {
    int x;
    int y;
}Tail[sz / 2 * 10], food, snake;


bool end_game; //переменые
int score, cnt_tail;
enum muve { Stop, Left, Right, Up, Down };
muve motion;
char old_frame[sz][sz];
char frame[sz][sz];
int speed=100;


void Setup()
{
    end_game = false;// начальная инициализация переменых 
    motion = Stop;
    cnt_tail = 0;
    snake.x = sz / 2;
    snake.y = sz / 2;
    do
    {
        food.x = 1 + rand() % (sz - 2);
        food.y = 1 + rand() % (sz - 2);

    } while (food.x == snake.x && food.y == snake.y);// проверка чтобы начальное появление еды не совпало с начальними координатами змеи 
    score = 0;

}



int check() // проверка чтобы появление еды не совпало с координатами змеи 
{
    for (int n = 0; n < cnt_tail; n++)
    {
        if (food.x == Tail[n].x && food.y == Tail[n].y)
        {
            return 1;
        }
    }
    return 0;
}

int tail(int i, int j) //рисование хвоста
{
    for (int n = 0; n < cnt_tail; n++)
    {
        if (Tail[n].x == j && Tail[n].y == i)
        {

            frame[i][j] = '#';
            return 1;
        }
    }
    return 0;
}

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}



void playing_field() // игровое поле
{
            frame[0][0] = 201;//углы рамки
            frame[0][sz - 1] = 187;
            frame[sz - 1][0] = 200;
            frame[sz - 1][sz - 1] = 188;
            frame[snake.y][snake.x] = 'o';//РИСОВАНИЕ ГОЛОВЫ ЗМЕИ в масиве frame
            frame[food.y][food.x] = '@';//РИСОВАНИЕ ЕДЫв масиве frame
            
    for (int i = 1; i < sz-1; i++)
    {       
            frame[i][0] = 186; //боковые рамки
            frame[i][sz - 1] = 186;
            
        for (int j =1; j < sz-1; j++)
        { 
            frame[0][j] = 205;// верхняя и нижняя рамки
            frame[sz - 1][j] = 205;
           
                if (!tail(i, j) && (snake.y != i || snake.x != j) && (food.y != i || food.x != j))
                   frame[i][j] = ' ';
        }
    }
    for (int i = 0; i < sz; i++)// вывод  масива frame на екран и потом вывод меняющихся значений
    {
        for (int j = 0; j < sz; j++) 
        {
            if (frame[i][j] != old_frame[i][j])
            {
                gotoxy(j, i);
                cout << frame[i][j];
                old_frame[i][j] = frame[i][j];
            }
        }
    }
    gotoxy(0,sz + 1);
    cout << "score-->" << score<<"\n";
    Sleep(speed);
}


void input() //отслеживание клавиатуры
{


    if (_kbhit()) {
        switch (_getch())
        {
        case 'a':
        case 'A':  motion = Left;
            break;
        case'd':
        case'D':motion = Right;
            break;
        case'w':
        case'W':motion = Up;
            break;
        case's':
        case'S':   motion = Down;
            break;
        case'x':
        case'X': end_game = true;
            break;
        }
    }
}

void game() //  логика игры
{

    Tail[0] = snake;

    for (int i = 1; i < cnt_tail; i++) // перезаполнение масивов с координатами хвоста
    {
        swap(Tail[i], Tail[i - 1]);
    }

    switch (motion)// отслеживание нажатия клавиш
    {
    case Left:
        snake.x--;
        break;
    case Right:
        snake.x++;
        break;
    case Up:
        snake.y--;
        break;
    case Down:
        snake.y++;
        break;
    }

    
    if (snake.x == sz - 1) //логика поведения при столкновении со стеной
        snake.x = 1;
    else if (snake.x == 0)
        snake.x = sz - 2;
    if (snake.y == sz - 1)
        snake.y = 1;
    else if (snake.y == 0)
        snake.y = sz - 2;


    for (int i = 0; i < cnt_tail; i++)
        if (Tail[i].x == snake.x && Tail[i].y == snake.y)
            end_game = true;
    if (food.y == snake.y && food.x == snake.x)
    {
        score++;
        do// проверка координат респавна еды
        {
            food.x = 1 + rand() % (sz - 2);
            food.y = 1 + rand() % (sz - 2);

        } while (check());

        cnt_tail++;
    }


}

int main()
{
    srand(time(nullptr));
    Setup();
    do
    {
        playing_field();
                
        input();
        game();
        if (end_game)
        {
            cout << "you loozer\n";
            break;
        }

        if (score == 10)
        {
            system("cls");
            cout << "score-->" << score << "\n";
            cout << "you winer\n";
            break;
        }



    } while (true);


    system("pause");
    return 0;
}
