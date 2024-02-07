//#pragma once
//#include <iostream>
//#include <string>
//#include <cstdlib>
//#include <ctime>
//#include <conio.h>
//#include <windows.h>
//using namespace std;
//
//const int BOARD_WIDTH = 30;
//const int BOARD_HEIGHT = 20;
//
//int playerX = BOARD_WIDTH / 2;
//int playerY = BOARD_HEIGHT - 1;
//
//int obstacleX = 0;
//int obstacleY = 0;
//
//int score = 0;
//
//void drawBoard()
//{
//    system("cls");
//    for (int i = 0; i < BOARD_WIDTH + 2; i++)
//        cout << "-";
//    cout << endl;
//    for (int i = 0; i < BOARD_HEIGHT; i++)
//    {
//        cout << "|";
//        for (int j = 0; j < BOARD_WIDTH; j++)
//        {
//            if (i == playerY && j == playerX)
//                cout << "O";
//            else if (i == obstacleY && j == obstacleX)
//                cout << "X";
//            else
//                cout << " ";
//        }
//        cout << "|" << endl;
//    }
//    for (int i = 0; i < BOARD_WIDTH + 2; i++)
//        cout << "-";
//    cout << endl;
//    cout << "Obstacle avoided : " << score << endl;
//
//    // Bounds checking for the player's position
//    if (playerX < 0) {
//        playerX = 0;
//    }
//    else if (playerX >= BOARD_WIDTH) {
//        playerX = BOARD_WIDTH - 1;
//    }
//    if (playerY < 0) {
//        playerY = 0;
//    }
//    else if (playerY >= BOARD_HEIGHT) {
//        playerY = BOARD_HEIGHT - 1;
//    }
//}
//
//void moveObstacle()
//{
//    obstacleY++;
//    if (obstacleY >= BOARD_HEIGHT)
//    {
//        obstacleY = 0;
//        obstacleX = rand() % BOARD_WIDTH;
//        score++;
//    }
//}
//
//void movePlayer(char input)
//{
//    switch (input)
//    {
//    case 'A':
//    case 'a':
//        playerX--;
//        break;
//    case 'D':
//    case 'd':
//        playerX++;
//        break;
//    case 'S':
//    case 's':
//        playerY++;
//        break;
//    case 'W':
//    case 'w':
//        playerY--;
//        break;
//    }
//
//    if (playerX < 0)
//        playerX = 0;
//    if (playerX >= BOARD_WIDTH)
//        playerX = BOARD_WIDTH - 1;
//}
//
//bool checkCollision()
//{
//    return (playerX == obstacleX && playerY == obstacleY);
//}
//
//int main()
//{
//    cout << "Enter Your Name: ";
//    string name;
//    getline(cin, name);
//    srand(time(NULL));
//    char input;
//    while (true)
//    {
//        drawBoard();
//        moveObstacle();
//        if (checkCollision())
//        {
//            cout << "Game Over!" << endl;
//            cout << "Your score was: " << score << endl;
//            break;
//        }
//        if (_kbhit())
//        {
//            input = _getch();
//            movePlayer(input);
//        }
//        Sleep(50);
//    }
//    return 0;
//}
