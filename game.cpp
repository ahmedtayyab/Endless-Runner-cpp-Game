#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <fstream>
#include <dos.h>
using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);  // FOR COLORING

int lives = 3;

const int BOARD_WIDTH = 30;
const int BOARD_HEIGHT = 20;

int playerX = BOARD_WIDTH / 2;
int playerY = BOARD_HEIGHT - 1;

string playerName;

int obstacleX = 0;
int obstacleY = 0;
int obstacleA = 0;
int obstacleB = 0;
int obstacleJ = 0;
int obstacleK = 0;

int coinX = 0;
int coinY = 0;
int coinA = 0;
int coinB = 0;
int coinJ = 0;
int coinK = 0;

int Numberofcoins = 0;
int score = 0;
int highestdistance = 0;
int distanceCovered = 0;

bool soundPlayed = false;


void filehandling(string playerName,int highestdistance)
{

    if (distanceCovered > highestdistance)
    {
        highestdistance = distanceCovered;

        

        // Write the player's name and high score to a file
        ofstream outFile("high_scores.txt", ios::app);  // Open the file in append mode
        if (outFile.is_open())
        {
            outFile <<playerName << "\t" << highestdistance << endl;
            outFile.close();
        }
        else {
            cout << "Unable to write to file." << endl;
        }
    }
}


void drawBoard()
{
   
    system("cls");
    for (int i = 0; i < BOARD_WIDTH + 2; i++)
    {
        SetConsoleTextAttribute(h, 11);          //12 is for bright cyan
        cout << "-";
    }
    cout << endl;
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        {
            SetConsoleTextAttribute(h, 11);    ////12 is for bright red
            cout << "|";
        }
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            if (i == playerY && j == playerX)
            {
                SetConsoleTextAttribute(h, 15);   //15 is for bright white
                cout << "0";
               
            }
            else if (i == playerY+2 && j == playerX-1 && distanceCovered >= 2000)
            {
                SetConsoleTextAttribute(h, 9);
                cout << " ";
                cout << "U";
                if (!soundPlayed)
                {
                    PlaySound(TEXT("police.wav"), NULL, SND_ASYNC);
                    soundPlayed = true;
                }
                
            }
            
            //OBSTACLES GENERATION

            else if (i == obstacleY && j== obstacleX)
            {
                SetConsoleTextAttribute(h, 12);     //12 is for bright red
                cout << "X";
            }
            else if (i == obstacleB && j== obstacleA) //12 is for bright red
            {
                SetConsoleTextAttribute(h, 12);
                cout << "A";
            }
            else if (i == obstacleK && j== obstacleJ) //12 is for bright red
            {
                SetConsoleTextAttribute(h, 12);
                cout << "J";
            }

            //COINS GENERATION

            else if (i == coinY && j == coinX)  
            {
                SetConsoleTextAttribute(h, 14);
                cout << "*";
            }
            else if (i == coinB && j == coinA) 
            {
                SetConsoleTextAttribute(h, 14);
                cout << "*";
            }
            else if (i == coinK && j  == coinJ) 
            {
                SetConsoleTextAttribute(h, 14);
                cout << "*";
            }
            else
                cout << " ";
        }
        {
               SetConsoleTextAttribute(h, 11);    //11 is for bright cyan
               cout << "|" << endl;
        }
    }
    for (int i = 0; i < BOARD_WIDTH + 2; i++)
    {
        SetConsoleTextAttribute(h, 11);         //11 is for bright cyan
        cout << "-";
    }
    cout << endl;
    
    cout << "Distance Covered: [ ";
    SetConsoleTextAttribute(h, 15);           ////15 is for bright white
    cout << distanceCovered;
    SetConsoleTextAttribute(h, 15);
    cout << " ]" << endl;

    SetConsoleTextAttribute(h, 11);
    cout << "Obstacle avoided : [ ";
    SetConsoleTextAttribute(h, 15);
    cout << score;
    SetConsoleTextAttribute(h, 15);
    cout << " ]" << endl;

    SetConsoleTextAttribute(h, 11);
    cout << "Number of Coins : [ ";
    SetConsoleTextAttribute(h, 15);
    cout << Numberofcoins;

    SetConsoleTextAttribute(h, 15);
    cout << " ]" << endl;
    
    SetConsoleTextAttribute(h, 11);
    cout << "Lives Remaining : [ ";
    SetConsoleTextAttribute(h, 15);
    cout << lives;
    SetConsoleTextAttribute(h, 15);
    cout << " ]" << endl;

    // Bounds checking for the player's position
    if (playerX < 0) {
        playerX = 0;
    }
    else if (playerX >= BOARD_WIDTH)
    {
        playerX = BOARD_WIDTH - 1;
    }
    if (playerY < 0) {
        playerY = 0;
    }
    else if (playerY >= BOARD_HEIGHT) {
        playerY = BOARD_HEIGHT - 1;
    }

}

void moveObstacle()
{
    obstacleY++;
    if (obstacleY >= BOARD_HEIGHT) {   
        obstacleY = 0;                
        obstacleX = rand() % BOARD_WIDTH;   
        score++;
       
    }
    obstacleK++;
    if (obstacleK >= BOARD_HEIGHT) {   
        obstacleK = -4;                
        obstacleJ = rand() % BOARD_WIDTH;  
        score++;

    }
    obstacleB++;
    if (obstacleB >= BOARD_HEIGHT) {   
        obstacleB = -7;                
        obstacleA = rand() % BOARD_WIDTH;   
        score++;

    }

    
}


void moveCoin()
{
    coinY++;
    if (coinY >= BOARD_HEIGHT) {   
        coinY = 0;   
        coinX = rand() % BOARD_WIDTH;   
    }

    coinK++;   
    if (coinK >= BOARD_HEIGHT) {   
        coinK = -4;   
        coinJ = rand() % BOARD_WIDTH;   
       
    }

    coinB++;   
    if (coinB >= BOARD_HEIGHT) {   
        coinB = -9;   
        coinA = rand() % BOARD_WIDTH;   
        
    }
}

void movePlayer(char input)
{
    switch (input)
    {
    case 'A':
    case 'a':
        playerX--;
        break;
    case 'D':
    case 'd':
        playerX++;
        break;
    case 'S':
    case 's':
        playerY++;
        break;
    case 'W':
    case 'w':
        playerY--;
        break;
    }

    if (playerX < 0)
        playerX = 0;
    if (playerX >= BOARD_WIDTH)
        playerX = BOARD_WIDTH - 1;
}

bool checkCollision()
{
    if (((playerX == obstacleY || playerX == obstacleX) && (playerY == obstacleX || playerY == obstacleY) || (playerX == obstacleB || playerX == obstacleA) && (playerY == obstacleB || playerY == obstacleA) || (playerX == obstacleK || playerX == obstacleJ) && (playerY == obstacleK || playerY == obstacleJ)))
    {
        PlaySound(TEXT("Punch.wav"), NULL, SND_ASYNC);    //Just for FUN :P
        return true;
    }
    else
        return false;
}


int coinGain()
{
    if ((playerX == coinY || playerX == coinX) && (playerY == coinX || playerY == coinY) || (playerX == coinB || playerX == coinA) && (playerY == coinB || playerY == coinA)||(playerX == coinK || playerX == coinJ) && (playerY == coinK || playerY == coinJ))
    {
        PlaySound(TEXT("coinpick.wav"), NULL, SND_ASYNC);    //Just for FUN :P
        Numberofcoins++;
        return Numberofcoins;
        

    }
    else
    {
        return false;
    }
    
}
void game()
{

    
   
    srand(time(0));
    char input;
    while (true)
    {

        drawBoard();
        moveObstacle();
        moveCoin();
        if (checkCollision())
        {
            
            lives--;
            if (lives == 0)
            {
                cout << "Game Over!" << endl;
                cout << "Your score was: " << distanceCovered*3 << endl;
                break;
            }
        }
        
        cout << coinGain();
        if (_kbhit())
        {
            input = _getch();
            movePlayer(input);
        }
        if (distanceCovered <= 1000)
            Sleep(14);
        if (distanceCovered <= 2000)
            Sleep(9);
        if (distanceCovered <= 3000)
            Sleep(5);
        if (distanceCovered <= 4000)
            Sleep(1);
       
        if (distanceCovered > 4000)
            Sleep(0);
       

        distanceCovered=distanceCovered+10;
        system("cls");
     
    }
    
}

void credit() 
{
    system("cls");
    cout << setw(70) << "--CREDITS-- " << endl;
    
    cout << "   Dev 1:   Ahmad Tayyab" << endl;
    cout << "   Roll #: 22F-8817" << endl;
    cout << "   Dev 2:  Umar Javed" << endl;
    cout << "   Roll #: 21F-9642" << endl;

    cout << setw(10) << setw(60)<<" -- Ahmad's Portion -- " << endl;
    cout << "   1. Logo, Main Menu and Menu Colors" << endl;
    cout << "   2. Map Design" << endl;
    cout << "   3. Obstacles " << endl;
    cout << "   4. Boundary Check for Player " << endl;
    cout << "   5. Second Player Generation and Follow Up" << endl;
    cout << "   6. Coins Collection" << endl;
    cout << "   7. Game Speed" << endl;

    cout << setw(10) << setw(60) << " -- Umar's Portion -- " << endl;
    cout << "   1. Player Movement" << endl;
    cout << "   2. Game Coloring" << endl;
    cout << "   3. Score Function" << endl;
    cout << "   4. Collision with obstacles" << endl;
    cout << "   5. File Handling" << endl;
    cout << "   6. Sound" << endl;
    cout << "   7. Code Commenting" << endl;

    cout << setw(10) << setw(60) << " --BETA TESTER -- " << endl;
    cout << " Tester:    Muhammad Abdullah" << endl;
    cout << " Roll #:    22F-3722" << endl;
}


void score_()
{
    string score1;
    ifstream infile;
    infile.open("high_scores.txt");
    if (infile.is_open())
    {
        while (!infile.eof())
        {
    
            getline(infile, score1);

            cout << score1 << endl;
        }

    }
    infile.close();
}
void exit()
{
    terminate;
}
void MainMenu()
{
    
    system("cls");														// Clear screen
    cout << endl << endl;
    cout << " Please enter your name: ";
    string playerName;
    getline(cin, playerName);

    system("Color 09");													// Changing text color
    cout << endl << endl;
    cout << setw(105) << "  <============> ENDLESS RUNNER! <============>" << endl;
    cout << endl;
    cout << setw(98) << "=======> MAIN MENU <=======" << endl;
    cout << setw(90);
    cout << "1 -- PLAY GAME" << endl;
    cout << setw(87);
    cout << "2 -- CREDIT" << endl;
    cout << setw(94);
    cout << "3 -- INSTRUCTIONS " << endl;
    cout << setw(87);
    cout << "4 -- SCORE " << endl;
    cout << setw(86);
    cout << "5 -- EXIT " << endl << endl;
    cout << endl;
  
 

}
void Logo() {		// Creates game logo which appears on the beginning of game
    system("Cls");		// Clear screen
    cout << "\n\n";
    system("Color 09");

    cout << " ||                                                              dddddddd                                                                " << endl;
    cout << " ||          EEEEEEEEEEEEEEEEEEEEEE                              d::::::dlllllll                                                         " << endl;
    cout << " ||          E::::::::::::::::::::E                              d::::::dl:::::l                                                         " << endl;
    cout << " ||          E::::::::::::::::::::E                              d::::::dl:::::l                                                         " << endl;
    cout << " ||          EE::::::EEEEEEEEE::::E                              d:::::d l:::::l                                                         " << endl;
    cout << " ||             E:::::E       EEEEEEnnnn  nnnnnnnn        ddddddddd:::::d  l::::l     eeeeeeeeeeee        ssssssssss       ssssssssss     " << endl;
    cout << " ||            E:::::E             n:::nn::::::::nn    dd::::::::::::::d  l::::l   ee::::::::::::ee    ss::::::::::s    ss::::::::::s    " << endl;
    cout << " ||            E::::::EEEEEEEEEE   n::::::::::::::nn  d::::::::::::::::d  l::::l  e::::::eeeee:::::eess:::::::::::::s ss:::::::::::::s   " << endl;
    cout << " ||            E:::::::::::::::E   nn:::::::::::::::nd:::::::ddddd:::::d  l::::l e::::::e     e:::::es::::::ssss:::::ss::::::ssss:::::s  " << endl;
    cout << " ||             E:::::::::::::::E     n:::::nnnn:::::nd::::::d    d:::::d  l::::l e:::::::eeeee::::::e s:::::s  ssssss  s:::::s  ssssss   " << endl;
    cout << " ||             E::::::EEEEEEEEEE     n::::n    n::::nd:::::d     d:::::d  l::::l e:::::::::::::::::e    s::::::s         s::::::s        " << endl;
    cout << " ||             E:::::E               n::::n    n::::nd:::::d     d:::::d  l::::l e::::::eeeeeeeeeee        s::::::s         s::::::s     " << endl;
    cout << " ||             E:::::E       EEEEEE  n::::n    n::::nd:::::d     d:::::d  l::::l e:::::::e           ssssss   s:::::s ssssss   s:::::s   " << endl;
    cout << " ||           EE::::::EEEEEEEE:::::E  n::::n    n::::nd::::::ddddd::::::ddl::::::le::::::::e          s:::::ssss::::::ss:::::ssss::::::s  " << endl;
    cout << " ||           E::::::::::::::::::::E  n::::n    n::::n d:::::::::::::::::dl::::::l e::::::::eeeeeeee  s::::::::::::::s s::::::::::::::s   " << endl;
    cout << " ||           E::::::::::::::::::::E  n::::n    n::::n  d:::::::::ddd::::dl::::::l  ee:::::::::::::e   s:::::::::::ss   s:::::::::::ss    " << endl;
    cout << " ||           EEEEEEEEEEEEEEEEEEEEEE  nnnnnn    nnnnnn   ddddddddd   dddddllllllll    eeeeeeeeeeeeee    sssssssssss      sssssssssss      " << endl;
    cout << " ||                                                                                                                                      " << endl;
    cout << "                                                                                                                                         " << endl;
    cout << "                                                                                                                                         " << endl;
    cout << "                                                                                                                                         " << endl;
    cout << "                       ||                                                                                                                                          " << endl;
    cout << "                       ||              RRRRRRRRRRRRRRRRR                                                                                                           " << endl;
    cout << "                       ||              R::::::::::::::::R                                                                                                          " << endl;
    cout << "                       ||              R::::::RRRRRR:::::R                                                                                                         " << endl;
    cout << "                       ||              RR:::::R     R:::::R                                                                                                        " << endl;
    cout << "                       ||                R::::R     R:::::Ruuuuuu    uuuuuunnnn  nnnnnnnn    nnnn  nnnnnnnn        eeeeeeeeeeee    rrrrr   rrrrrrrrr               " << endl;
    cout << "                       ||                R::::R     R:::::Ru::::u    u::::un:::nn::::::::nn  n:::nn::::::::nn    ee::::::::::::ee  r::::rrr:::::::::r              " << endl;
    cout << "                       ||                R::::RRRRRR:::::R u::::u    u::::un::::::::::::::nn n::::::::::::::nn  e::::::eeeee:::::eer:::::::::::::::::r             " << endl;
    cout << "                       ||                R:::::::::::::RR  u::::u    u::::unn:::::::::::::::nnn:::::::::::::::ne::::::e     e:::::err::::::rrrrr::::::r            " << endl;
    cout << "                       ||                R::::RRRRRR:::::R u::::u    u::::u  n:::::nnnn:::::n  n:::::nnnn:::::ne:::::::eeeee::::::e r:::::r     r:::::r            " << endl;
    cout << "                       ||                R::::R     R:::::Ru::::u    u::::u  n::::n    n::::n  n::::n    n::::ne:::::::::::::::::e  r:::::r     rrrrrrr            " << endl;
    cout << "                       ||                R::::R     R:::::Ru::::u    u::::u  n::::n    n::::n  n::::n    n::::ne::::::eeeeeeeeeee   r:::::r                        " << endl;
    cout << "                       ||                R::::R     R:::::Ru:::::uuuu:::::u  n::::n    n::::n  n::::n    n::::ne:::::::e            r:::::r                        " << endl;
    cout << "                       ||              RR:::::R     R:::::Ru:::::::::::::::uun::::n    n::::n  n::::n    n::::ne::::::::e           r:::::r                        " << endl;
    cout << "                       ||              R::::::R     R:::::R u:::::::::::::::un::::n    n::::n  n::::n    n::::n e::::::::eeeeeeee   r:::::r                        " << endl;
    cout << "                       ||              R::::::R     R:::::R  uu::::::::uu:::un::::n    n::::n  n::::n    n::::n  ee:::::::::::::e   r:::::r                        " << endl;
    cout << "                       ||              RRRRRRRR     RRRRRRR    uuuuuuuu  uuuunnnnnn    nnnnnn  nnnnnn    nnnnnn    eeeeeeeeeeeeee   rrrrrrr                        " << endl;
    cout << "                       ||                                                                                                                                          " << endl;

    Sleep(1000);				// Wait for 2.5 seconds then do next task
}
int GetKey()					// Checks which main menu option user is choosing
{
    int key = _getch();			// get the key
    return key;
}
int main()
{

  
    srand(time(0));
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);				// maximize screen 
    Logo();
    redo:
    MainMenu();
    int choice;
    cout << setw(89);
   
    cout << "Select Your Choice: ";
    cin >> choice;
    switch (choice)
    {

    case 1:
    {
        
        game();
        cout << "THE END";
        break;
    }
    case 2:
    {
        system("cls");
        credit();
        break;
    }

    case 3:
    {
        system("Cls");

        cout << "--GAME RULES--" << endl;

        cout << "1. The game will start with the player character running automatically, and the player can control the character's movement by moving sideways, forwards or backwards using WASD keys" << endl;

        cout << "2. The player character will have three lives at the start of the game, and they will lose a life if they hit an obstacle." << endl;

        cout << "3. The game will end when the player runs out of lives." << endl;

        cout << "4. The player character will collect coins while running, and the score will increase with each coin collected." << endl;

        cout << "5. The distance covered by the player character will be measured, and the game's speed will increase as the distance increases." << endl;

        cout << "6. When the distance covered by the player character exceeds 2000 meters, a computer player will be introduced in the game that will follow the player character and try to collide with them." << endl;

        cout << "7. The player cannot pass through the walls on the side." << endl;

        cout << "8. The player can enter their name at the start of the game, and their high score will be stored in a file." << endl;
        
        break;
    }
    case 4:
    {
        system("cls");
        score_();
        break;
    }

    case 5:
    {
        system("cls");
        exit();
        break;
    }

    default:
    {
        system("cls");
        cout << "INVALID CHOICE" << endl;
        goto redo;
        break;
    }
    }
    filehandling(playerName,highestdistance);
    
}