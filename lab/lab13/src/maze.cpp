#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
using namespace std;

const int m = 10, n = 10;
int start_x, start_y, i, j;
int matrix[m][n];
//ifstream infile1("maze.txt");
ifstream infile1("puzzle.txt");

void initializeMatrix() {
    for (i = 0; i < m; i++) {
        string oneline;
        getline(infile1, oneline);
        stringstream ss1(oneline);
        for (j = 0; j < n; j++) {
            ss1 >> matrix[i][j];
            if (matrix[i][j] == 9) {
                start_y = i; start_x = j;
            }
        }
    }
}

bool isEnd(int x, int y) {
    return matrix[x][y] == 6 || matrix[x][y] == 7;
}

bool isBlocked(int x, int y) {
    return matrix[x][y] == 1 || matrix[x][y] == 4 || matrix[x][y] == 2;
}

bool findWay(int x, int y) {
    if (isEnd(x, y)) return true;
    if (isBlocked(x, y)) return false;

    matrix[x][y] = 2;

    if (findWay(x, y + 1) || findWay(x + 1, y) || findWay(x, y - 1) || findWay(x - 1, y)) {
        matrix[x][y] = 6;
        return true;
    }
    
    matrix[x][y] = 4;
    return false;
}

void printMatrix() {
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (matrix[i][j] == 4) cout << " " << ""; //blank
            else if (matrix[i][j] == 0) cout << " " << ""; //passageway
            else if (matrix[i][j] == 1) cout << "■" << ""; //block
            else if (matrix[i][j] == 6) cout << "▲" << ""; //way
            else if (matrix[i][j] == 9) cout << "★" << ""; //start point
            else if (matrix[i][j] == 7) cout << "☆" << ""; //end point
            else cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    if (!infile1.is_open())
        cout << "can't open the file" << endl;

    initializeMatrix();
	cout << "initial Matrix" << endl;
	printMatrix();

    if (findWay(start_y, start_x)) {
		cout << "the solution" << endl;
        printMatrix();
    } else {
        cout << "there is no way out!";
    }

    return 0;
}
