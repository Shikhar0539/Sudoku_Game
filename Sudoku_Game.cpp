#include <iostream>

using namespace std;

const int N = 9;
int board[N][N] =
   {
        {0, 6, 8, 0, 1, 0, 0, 4, 7},
        {0, 0, 0, 6, 8, 0, 1, 0, 5},
        {0, 9, 7, 2, 0, 4, 8, 0, 3},
        {0, 8, 0, 0, 0, 0, 3, 1, 2},
        {7, 0, 4, 0, 0, 2, 9, 0, 0},
        {2, 0, 9, 0, 3, 0, 0, 7, 0},
        {0, 0, 6, 0, 4, 0, 7, 8, 0},
        {8, 5, 0, 0, 2, 0, 4, 3, 0},
        {0, 0, 0, 0, 0, 0, 5, 2, 0}
    };



bool board_solved(int sudoku[][N])
{
    for(int row = 0 ; row < N ; row++)
    {
        for(int col = 0 ; col < N ; col++)
        {
            if(sudoku[row][col]==0)
            {
                return false; // sudoku yet not solved
            }
        }
    }

    return true; // board completely solved if no number on the board is 0 anymore
}

bool is_move_valid(int sudoku[][N], int row , int col, int digit)
{
    for(int i = 0 ; i < N ; i++)
    {
        if(i == col)
        {
            continue;
        }
        if(sudoku[row][i] == digit) // We are checking if the digit entered by the user is already present in the same row
        {
            return false;
        }
    }

    for(int i = 0 ; i < N ; i++)
    {
        if(i == row)
        {
            continue;
        }
        if(sudoku[i][col] == digit) // We are checking if the digit entered by the user is already present in the same column
        {
            return false;
        }
    }

    for(int i = 0 ; i < 3 ; i++)
    {
        for(int j = 0 ; j < 3 ; j++)
        {
            if(i == row%3 && j == col%3)
            {
                continue;
            }
            if(sudoku[row - row%3 + i][col - col%3 + j] == digit) // We are checking if the digit entered by the user is already present in that 3x3 block
            {
                return false;
            }
        }
    }

    return true; // We return true if the digit was not found in the same row , column or that 3x3 block
}

void print(int sudoku[][N])
{
    system("cls"); // To clear the terminal screen
    cout << "\t\t\t************************************************************************" << endl;
    cout << "\t\t\t                        WELCOME TO SUDOKU GAME!                         " << endl;
    cout << "\t\t\t************************************************************************" << endl << endl;

    for(int row = 0 ; row < N ; row++)
    {
        cout << "\t\t\t\t\t\t";
        for(int col = 0 ; col < N ; col++)
        {
            if(col == 3 || col == 6)
            {
                cout << " | ";
            }
                cout << sudoku[row][col] << " ";
        }

        if(row == 2 || row == 5)
        {
            cout << endl;
            cout << "\t\t\t\t\t\t";
            for(int i = 0 ; i < N ; i++)
            {
                cout << "---";
            }
        }

        cout << endl;
    }
}

bool solve(int row, int col)
{
    if(row == N - 1 && col == N) // base case to check if the sudoku is solved or not
    {
        return true;
    }

    if(col == N) // If column reached at 9 then it means we have to move to next row and 1st column
    {
        col = 0;
        row++;
    }

    if(board[row][col] != 0) // If the cell doesn't contain 0 then it means it is already filled so move to next column
    {
        return solve(row , col+1);
    }

    for(int digit = 1 ; digit <= 9 ; digit++) // We try placing all digits one by one
    {
        if(is_move_valid(board, row, col, digit))
        {
            board[row][col] = digit;

            if(solve(row,col+1))
            {
               return true;
            }

            board[row][col] = 0; // backtracking
        }
    }

    return false; // The Sudoku is not solvable
}

void rules()
{
    system("cls");
    print(board);
    cout << endl;
    cout << "Rules : "<< endl << endl;
    cout << "1. Sudoku Game is a puzzle which is a 9x9 matrix containing digits 1-9." << endl;
    cout << "2. You have to fill in the missing digits represented by 0 to be able to solve the Sudoku." << endl;
    cout << "3. To win the game : every row , column and each 3x3 block of the Sudoku puzzle should contain unique digits i.e. no digit should be repeated." << endl;
    cout << "4. You will be allowed a total of 5 mistakes." << endl << endl;
    cout << "Enter any digit to go back to the main screen : ";
    int choice;
    cin >> choice;
    while(choice < 0 or choice > 9)
    {
        cout << "You have to press a digit to be able to go back to the main screen ! : ";
        cin >> choice;
    }
    system("cls");
    print(board);
}

void start(int new_board[][N] , bool& flag)
{
    int row, col, digit, mistakes_left = 5, helper_mistakes_left = 5;
    int temp = 0;

    while(true)
    {
        print(new_board);

        if(temp == 0)
        {
            cout << endl << endl << "Number of allowed mistakes left : " << mistakes_left << endl << endl;
            temp++;
        }

        else
        {
            if(helper_mistakes_left == mistakes_left + 1)
            {
               cout << endl << endl << "Incorrect ! Number of allowed mistakes left : " << mistakes_left << endl << endl;
               helper_mistakes_left--;
            }
            else
            {
               cout << endl << endl << "Correct ! Number of allowed mistakes left : " << mistakes_left << endl << endl;
            }

        }

        cout << "Enter the row number(1-9) where you want to place your digit : ";
        cin >> row;
        while(row <= 0 || row >= 10)
        {
            cout << "Invalid row number ! Please choose again from 1 to 9 : ";
            cin >> row;
        }
        cout << "Enter the column number(1-9) ! where you want to place your digit : ";
        cin >> col;
        while(col <= 0 || col >= 10)
        {
            cout << "Invalid column number ! Please choose again from 1 to 9 : ";
            cin >> col;
        }
        cout << "Enter the digit : ";
        cin >> digit;
        while(digit <= 0 || digit >= 10)
        {
            cout << "The chosen digit has to be from 1 to 9 ! Please choose again : ";
            cin >> digit;
        }


        if(!is_move_valid(new_board, row - 1, col - 1, digit)) // Checking if the move made is valid or not
        {
             mistakes_left--;
             if(mistakes_left == -1)
             {
             system("cls");
             print(new_board);
             cout << endl << "Sorry you could not solve the puzzle because you have utilized the maximum number of allowed mistake attempts ! You can restart over and try again if you wish or view the solved sudoku !" << endl << endl;
             return;
             }
             else
             {
                 continue;
             }
        }

        new_board[row - 1][col - 1] = digit;

        if(board_solved(new_board))
        {
            print(new_board);
            cout << endl << endl << "\t\t\t Congratulations ! You have completely solved the Sudoku ! Thanks for playing !" << endl << endl;
            flag = true;
            break;
        }
    }
}

void set_new_board(int new_board[][N])
{
    int temp_board[N][N] =
    {
        {0, 6, 8, 0, 1, 0, 0, 4, 7},
        {0, 0, 0, 6, 8, 0, 1, 0, 5},
        {0, 9, 7, 2, 0, 4, 8, 0, 3},
        {0, 8, 0, 0, 0, 0, 3, 1, 2},
        {7, 0, 4, 0, 0, 2, 9, 0, 0},
        {2, 0, 9, 0, 3, 0, 0, 7, 0},
        {0, 0, 6, 0, 4, 0, 7, 8, 0},
        {8, 5, 0, 0, 2, 0, 4, 3, 0},
        {0, 0, 0, 0, 0, 0, 5, 2, 0}
    };

    for(int i = 0 ; i < N ; i++)
    {
        for(int j = 0 ; j < N ; j++)
        {
            new_board[i][j] = temp_board[i][j];
        }
    }

}

int main()
{
    system("title Sudoku Game"); // Sets the title of the command prompt to "Sudoku Game"
    system("color E4"); // Sets background color of command prompt to light yellow and text color to red

    print(board); //

    while(true)
    {
        cout << "1. Play Game" << endl;
        cout << "2. View rules" << endl;
        cout << "3. Unable to solve? View the solved sudoku" << endl;
        cout << "4. Quit" << endl << endl;
        cout << "Enter your option : 1 or 2 or 3 or 4 " << endl;

        int option;
        cin >> option;

        if(option == 1)
        {
           int new_board[9][9];
           set_new_board(new_board);
           bool flag = false;
           start(new_board, flag);
           if(flag)
           {
               break;
           }
        }

        else if(option == 2)
        {
          rules();
        }

        else if(option == 3)
        {
            if(solve(0,0))
            {
                system("cls");
                print(board);
                cout << endl << endl << "\t\t\t This is the completely solved Sudoku for you , Thanks for playing !";
                cout << endl << endl;
            }
            else
            {
                cout << endl << "The Sudoku cannot be solved !" << endl;
            }
            break;
        }

        else if(option == 4)
        {
            break;
        }

        else
        {
            cout << endl << "Invalid Option ! Choose again ! " << endl;
        }

    }

   return 0;
}
