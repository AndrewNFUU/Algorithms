#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <set>
#include <utility>
#include <cmath>

using namespace std;

const int ROW = 6;
const int COL = 6;

typedef pair<int, int> cellPair;
typedef pair<int, cellPair> edgeInfo;

struct Cell {
	int x{};
	int y{};
	int g{};
	int h{};
	int f{};
};

set<edgeInfo> openList;
bool closeList[ROW][COL];

bool IsInRange(int row, int col);

bool IsUnblocked(const vector<vector<int>>& cellMatrix, int row, int col);

bool IsGoalCell(int row, int col, const cellPair& finish);

int Heuristic(int row, int col, const cellPair& finish);

vector<vector<int>> ReadFromFile(string& filename);

void PrintPath(const vector<vector<Cell>>& cellMatrix,
			   const cellPair& start, const cellPair& finish,
			   vector<vector<int>>& visualMatrix);

void AStar(vector<vector<int>>& cellMatrix,
		   const cellPair& start,
		   const cellPair& finish);


int main()
{
	string file = "cellMatrix.txt";
	vector<vector<int>> cellMatrix = ReadFromFile(file);

	/*vector<vector<int>> cellMatrix = { { 1, 1, 1, 1, 1, 1 },
										 { 1, 1, 0, 0, 0, 0 },
										 { 1, 1, 0, 1, 1, 1 },
										 { 1, 1, 0, 1, 0, 1 },
										 { 1, 1, 0, 1, 0, 1 },
										 { 1, 1, 1, 1, 0, 1 } };
	*/

	cellPair start = make_pair(0, 0);
	cellPair finish = make_pair(5, 5);
	AStar(cellMatrix, start, finish);
}


bool IsInRange(int row, int col) {
	return (row >= 0 && row < ROW && col >= 0 && col < COL);
}

bool IsUnblocked(const vector<vector<int>>& cellMatrix,
	int row, int col) {

	if (cellMatrix[row][col] == 1) {
		return (true);
	}
	else {
		return (false);
	}
}

bool IsGoalCell(int row, int col, const cellPair& finish) {

	if (row == finish.first && col == finish.second) {
		return (true);
	}
	else {
		return (false);
	}
}

int Heuristic(int row, int col, const cellPair& finish) {
	return (int)(abs(row - finish.first) +
		abs(col - finish.second)) * 10;
}

vector<vector<int>> ReadFromFile(string& filename) {

	ifstream file(filename);

	vector<vector<int>> cellMatrix(ROW, vector<int>(COL));
	if (file.is_open()) {
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				file >> cellMatrix[i][j];
			}
		}
		file.close();
	}
	return cellMatrix;
}

void PrintPath(const vector<vector<Cell>>& cellMatrix,
	const cellPair& start, const cellPair& finish,
	vector<vector<int>>& visualMatrix) {

	int row = finish.first;
	int col = finish.second;
	stack<cellPair> Path;

	while (!(cellMatrix[row][col].x == row
		&& cellMatrix[row][col].y == col)) {

		Path.push(make_pair(row, col));
		int tempRow = cellMatrix[row][col].x;
		int tempCol = cellMatrix[row][col].y;
		row = tempRow;
		col = tempCol;
	}
	Path.push(make_pair(row, col));

	while (!Path.empty()) {
		pair<int, int> p = Path.top();
		Path.pop();

		cout << "\n-> cell (" << p.first << ", " << p.second << ")";
		visualMatrix[p.first][p.second] = 3;
	}
	cout << "\n";

	row = start.first; col = start.second;
	visualMatrix[row][col] = 8;

	row = finish.first; col = finish.second;
	visualMatrix[row][col] = 9;

	cout << "\n-- Path visualization --\n\n";

	for (int i = 0; i < ROW; i++) {

		for (int j = 0; j < COL; j++) {

			if (visualMatrix[i][j] == 8) {
				cout << " A ";
			}
			else if (visualMatrix[i][j] == 9) {
				cout << " B ";
			}
			else if (visualMatrix[i][j] == 0) {
				cout << " W ";
			}
			else if (visualMatrix[i][j] == 1) {
				cout << " . ";
			}
			else {
				cout << " * ";
			}
		}
		cout << "\n";
	}
	cout << "\nA -  start \nB - finish ";
	cout << "\nW - barrier \n. - available cells \n* - optimal path \n";
}

void AStar(vector<vector<int>>& cellMatrix,
	const cellPair& start,
	const cellPair& finish) {

	if (IsInRange(start.first, start.second) == false) {
		cout << "Start point is out of range. \n";
		return;
	}
	if (IsInRange(finish.first, finish.second) == false) {
		cout << "End point is out of range. \n";
		return;
	}
	if (IsUnblocked(cellMatrix, start.first, start.second) == false
		|| IsUnblocked(cellMatrix, finish.first, finish.second) == false) {

		cout << "Start or end point is blocked. \n";
		return;
	}
	if (IsGoalCell(start.first, start.second, finish) == true) {
		cout << "Already at the destination cell. \n";
		return;
	}

	vector<vector<Cell>> matrix(ROW, vector<Cell>(COL));
	int i{};
	int j{};
	int moveX{};
	int moveY{};

	for (i = 0; i < ROW; i++) {

		for (j = 0; j < COL; j++) {

			matrix[i][j].x = -1;
			matrix[i][j].y = -1;
			matrix[i][j].f = INT_MAX;
			matrix[i][j].g = INT_MAX;
			matrix[i][j].h = INT_MAX;
		}
	}
	i = start.first;
	j = start.second;
	matrix[i][j].x = i;
	matrix[i][j].y = j;
	matrix[i][j].f = 0;
	matrix[i][j].g = 0;
	matrix[i][j].h = 0;
	memset(closeList, false, sizeof(closeList));

	openList.insert(make_pair(0, make_pair(i, j)));
	bool foundDest = false;

	while (!openList.empty()) {

		edgeInfo p = *openList.begin();
		openList.erase(openList.begin());
		i = p.second.first;
		j = p.second.second;
		closeList[i][j] = true;

		int gNew, hNew, fNew;
		for (moveX = -1; moveX <= 1; moveX++) {

			for (moveY = -1; moveY <= 1; moveY++) {

				if (moveX == 0 && moveY == 0) {
					continue;
				}
				if (IsInRange(i + moveX, j + moveY)) {

					if (IsGoalCell(i + moveX, j + moveY, finish)) {
						matrix[i + moveX][j + moveY].x = i;
						matrix[i + moveX][j + moveY].y = j;
						cout << "----- Path found! -----\n";

						PrintPath(matrix, start, finish, cellMatrix);
						foundDest = true;
						return;
					}
					else if (!closeList[i + moveX][j + moveY] &&
						IsUnblocked(cellMatrix, i + moveX, j + moveY)) {

						gNew = matrix[i][j].g + 10;
						hNew = Heuristic(i + moveX, j + moveY, finish);
						fNew = gNew + hNew;

						if (matrix[i + moveX][j + moveY].f == INT_MAX
							|| matrix[i + moveX][j + moveY].f > fNew) {

							openList.insert(make_pair(fNew, make_pair(i + moveX, j + moveY)));
							matrix[i + moveX][j + moveY].f = fNew;
							matrix[i + moveX][j + moveY].g = gNew;
							matrix[i + moveX][j + moveY].h = hNew;
							matrix[i + moveX][j + moveY].x = i;
							matrix[i + moveX][j + moveY].y = j;
						}
					}
				}
			}
		}
	}
	if (foundDest == false) {}
	cout << "Path to the destination cell not found. \n";
}
