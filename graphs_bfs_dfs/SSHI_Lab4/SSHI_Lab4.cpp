#include <iostream>
#include <vector>
#include <stack>
#include <queue>


// Breadth First Search
void BFS(int s, std::vector<int>neighbors[], bool visited[]);


// Depth First Search
void DFS(int s, std::vector<int>neighbors[], bool visited[]);


// Adding nodes
void node(std::vector<int>neighbors[], int u, int v);


int main() {
	int N = 7;
	std::vector<int>neighbors[12];
	bool visited[12]{};

	for (int i = 0; i < N; i++) {
		visited[i] = false;
	}

	node(neighbors, 1, 2);
	node(neighbors, 1, 3);
	node(neighbors, 1, 6);
	node(neighbors, 6, 7);
	node(neighbors, 3, 4);
	node(neighbors, 4, 5);
	
	std::cout << "      Graph traversal\n";
	std::cout << "with DFS and BFS algorithms:\n";
	std::cout << "----------------------------\n\n";

	std::cout << "Traversal with DFS: \n";
	DFS(1, neighbors, visited); // set 0 as a starting point
	std::cout << "\n\n";

	for (int i = 0; i <= N; i++) {
		visited[i] = false;
	}

	std::cout << "Traversal with BFS: \n";
	BFS(1, neighbors, visited); 
	std::cout << "\n\n";

	system("pause"); return 0;
}


// --------------- Functions Implementation ---------------

void BFS(int s, std::vector<int>neighbors[], bool visited[]) {
	
	/*int n = neighbors->size();

	for (int i = 0; i < n; i++) {
		visited[i] = false;
	}*/
	
	std::queue<int>myQueue;
	myQueue.push(s);
	visited[s] = true;

	while (!myQueue.empty()) {
		int u = myQueue.front();
		std::cout << u << " ";
		myQueue.pop();

		for (int i = 0; i < neighbors[u].size(); i++) {
			if (!visited[neighbors[u][i]]) {
				myQueue.push(neighbors[u][i]);
				visited[neighbors[u][i]] = true;
			}
		}
	}
}


void DFS(int s, std::vector<int>neighbors[], bool visited[]) {
	std::stack<int>myStack;
	myStack.push(s);
	visited[s] = true;

	while (!myStack.empty()) {
		int u = myStack.top();
		std::cout << u << " ";
		myStack.pop();

		for (int i = 0; i < neighbors[u].size(); i++) {
			if (!visited[neighbors[u][i]]) {
				myStack.push(neighbors[u][i]);
				visited[neighbors[u][i]] = true;
			}
		}
	}
}


void node(std::vector<int>neighbors[], int u, int v) {
	neighbors[u].push_back(v);
}