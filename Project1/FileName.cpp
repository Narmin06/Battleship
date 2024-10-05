#include<iostream>
#include<iomanip>
#include<Windows.h>
#include<chrono>
#include <thread>
using namespace std;

void MySetColor(int fg, int bg) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, fg | (bg << 4));
}

char** ReserveArray(int& row, int& column) {
    char** array = new char* [row] {};
    for (size_t i = 0; i < row; i++)
    {
        array[i] = new char[column] {};
        for (size_t k = 0; k < column; k++)
        {
            array[i][k] = '*';
        }
    }
    return array;
}

int shot = 0; // 0-> Me 1->Computer

bool IsEmptyCoordinate(char**& array, int& row, int& column) {
    if (row < 10 && row >= 0 && column < 10 && column >= 0) {
        if (array[row][column] == '-') {
            return false;
        }
        else if (array[row][column] == 'X') {
            return false;
        }
        else {
            return true;
        }
    }
}

void ComputerAttack(char**& array1, int& row, int& column) {
    while (true) {
        int attackRow = rand() % row;
        int attackColumn = rand() % column;
        if (array1[attackRow][attackColumn] == '*') {
            array1[attackRow][attackColumn] = '-';
            shot = 0;
            break;
        }
        else if (array1[attackRow][attackColumn] == 'x') {
            array1[attackRow][attackColumn] = 'X';
            shot = 1;
            break;
        }
        else if (array1[attackRow][attackColumn] == 'X') {
            shot = 1;
            break;
        }
        else if (array1[attackRow][attackColumn] == '-') {
            shot = 1;
            break;
        }
        else {
            shot = 0;
            break;
        }
    }
}

void OurAttack(char**& array2, int& enter_row, int& enter_column) {
    while (true) {
        if (array2[enter_row][enter_column] == '*') {
            array2[enter_row][enter_column] = '-';
            shot = 1;
            break;
        }
        else if (array2[enter_row][enter_column] == 'x') {
            array2[enter_row][enter_column] = 'X';
            shot = 0;
            break;
        }
        else {
            shot = 1;
            break;
        }
    }
}

bool AllShips(char**& array, int& row, int& column) {
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (array[i][j] == 'x') {
                return false;
            }
        }
    }
    return true;
}

void PlaceShip(char**& array, int& startRow, int& startColumn, int& shipSize, int& element) {
    for (int i = 0; i < shipSize; i++)
    {
        if (element == 1) {
            array[startRow][startColumn + i] = 'x';
        }
        else {
            array[startRow + i][startColumn] = 'x';
        }
    }
}

bool PositionElement(char**& array, int& row, int& column, int& startRow, int& startColumn, int& shipSize, int& element) {
    int position_row;
    int position_column;
    for (int i = 0; i < shipSize; i++) {
        if (element == 1) {
            position_row = startRow;
            position_column = startColumn + i;
        }
        else {
            position_row = startRow + i;
            position_column = startColumn;
        }

        if (position_row < 0 || position_row >= row || position_column < 0 || position_column >= column) {
            return false;
        }
        if (array[position_row][position_column] == 'x') {
            return false;
        }
        int a = -1;
        for (int i = a; i < 2; i++)
        {
            for (int k = a; k < 2; k++)
            {
                int new_position_row = i + position_row;
                int new_position_column = k + position_column;
                if ((new_position_row >= 0) && (new_position_row < row) && (new_position_column >= 0) && (new_position_column < column)) {
                    if (array[new_position_row][new_position_column] == 'x') {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void InitArray(char**& array, int& row, int& column) {
    int ships[]{ 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
    int min = 0, max = 1;
    for (size_t i = 0; i < 10; i++)
    {
        int shipSize = ships[i];
        bool placed = false;
        while (!placed) {
            int element = min + rand() % (max - min + 1);
            int startRow = rand() % row;
            int startColumn = rand() % column;
            if (PositionElement(array, row, column, startRow, startColumn, shipSize, element))
            {
                PlaceShip(array, startRow, startColumn, shipSize, element);
                placed = true;
            }
        }
    }
}

void ShowArray(char**& array1, char**& array2, int& row, int& column) {
    cout << endl;
    MySetColor(9, 0);
    cout << "  \t   Your grid\t\t\t\t      Opponent's grid" << endl << endl;
    cout << "  ";
    MySetColor(7, 0);
    for (int i = 0; i < column; i++)
    {
        MySetColor(4, 0);
        cout << setw(3) << i;
    }
    MySetColor(7, 0);
    cout << "                 ";
    for (int i = 0; i < column; i++)
    {
        MySetColor(4, 0);
        cout << setw(3) << i;
    }
    MySetColor(7, 0);
    cout << endl << endl;
    for (size_t i = 0; i < row; i++) {
        MySetColor(4, 0);
        cout << i << " ";
        MySetColor(7, 0);
        for (size_t k = 0; k < column; k++)
        {
            if (array1[i][k] == '-') {
                MySetColor(1, 0);
                cout << setw(3) << "-";
                MySetColor(7, 0);
            }
            else if (array1[i][k] == 'X') {
                MySetColor(4, 0);
                cout << setw(3) << "X";
                MySetColor(7, 0);
            }
            else if (array1[i][k] == 'x') {
                MySetColor(6, 0);
                cout << setw(3) << "x";
                MySetColor(7, 0);
            }
            else {
                cout << setw(3) << array1[i][k];
            }
        }
        cout << "               ";
        MySetColor(4, 0);
        cout << i << " ";
        MySetColor(7, 0);
        for (size_t k = 0; k < column; k++)
        {
            if (array2[i][k] == '-') {
                MySetColor(1, 0);
                cout << setw(3) << "-";
                MySetColor(7, 0);
            }
            else if (array2[i][k] == 'X') {
                MySetColor(4, 0);
                cout << setw(3) << "X";
                MySetColor(7, 0);
            }
            else {
                cout << setw(3) << '.';
            }
        }
        cout << endl;
    }
}

bool IsDigit(string& number) {
    for (size_t i = 0; i < number.size(); i++)
    {
        if (char(number[i]) < 58 && char(number[i]) > 47) {
            return true;
        }
    }
    return false;
}

int My_Str_To_Num(string& str) {
    int k = -1;
    int sum = 0;
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] >= '0' && str[i] <= '9') {
            sum = sum * 10 + int(str[i] - 48);
        }
        else {
            return k;
            break;
        }
    }
    return sum;
}

void Clear() {
    this_thread::sleep_for(chrono::seconds(0));
    system("cls");
}

void Clear1() {
    this_thread::sleep_for(chrono::seconds(1));
    system("cls");
}

void DeleteArray(char**& array, int& row, int& column) {

    for (size_t i = 0; i < row; i++)
    {
        delete[] array[i];
    }
    delete[] array;
}


void main() {
    srand(time(NULL));
    int row = 10;
    int column = 10;

    char** array1 = ReserveArray(row, column);
    char** array2 = ReserveArray(row, column);

    InitArray(array1, row, column);
    InitArray(array2, row, column);

    while (true) {
        if (shot == 0) {
            Clear1();
            ShowArray(array1, array2, row, column);
            string enter_row_str;
            cout << endl << "Enter row(1-10): ";
            cin >> enter_row_str;

            cin.ignore();

            string enter_column_str;
            cout << "Enter column(1-10): ";
            cin >> enter_column_str;
            cin.ignore();
            if (IsDigit(enter_row_str) && IsDigit(enter_column_str)) {
                int enter_row = My_Str_To_Num(enter_row_str);
                int enter_column = My_Str_To_Num(enter_column_str);
                if (IsEmptyCoordinate(array2, enter_row, enter_column)) {
                    if (enter_row < 10 && enter_row >= 0 && enter_column < 10 && enter_column >= 0) {
                        Clear();
                        OurAttack(array2, enter_row, enter_column);
                        ShowArray(array1, array2, row, column);
                        if (AllShips(array2, row, column)) {
                            MySetColor(2, 0);
                            cout << endl << "Congratulations, you are the winner!" << endl;
                            MySetColor(7, 0);
                            break;
                        }
                    }
                    else {
                        MySetColor(6, 0);
                        cout << "Please enter correct row and column." << endl;
                        MySetColor(7, 0);
                        continue;
                    }
                }
                else {
                    MySetColor(6, 0);
                    cout << "This coordinate has been hit.Enter a new coordinate.";
                    MySetColor(7, 0);
                    continue;
                }
            }
            else {
                MySetColor(6, 0);
                cout << "Please enter correct row and column." << endl;
                MySetColor(7, 0);
                continue;
            }
        }
        else {
            Clear();
            ComputerAttack(array1, row, column);
            ShowArray(array1, array2, row, column);
            if (AllShips(array1, row, column)) {
                MySetColor(4, 0);
                cout << endl << "The computer has defeated you!" << endl;
                MySetColor(7, 0);
                break;
            }
        }
    }

    DeleteArray(array1, row, column);
    DeleteArray(array2, row, column);

}