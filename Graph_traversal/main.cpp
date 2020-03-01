#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct node {
	int v;
	node* next;

	node(int x, node* t) {
		v = x;
		next = t;
	}
};

typedef node* link;
const int V = 8;

void fill_adjacency_matrix(int adj[V][V]) {
	int i, j;

	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			adj[i][j] = 0;
		}
	}

	while (cin >> i >> j) {
		adj[i][j] = 1;
		adj[j][i] = 1;
	}
}

void fill_adjacency_list(link adj[]) {
	int i, j;

	for (i = 0; i < V; i++) {
		adj[i] = 0;
	}

	while (cin >> i >> j) {
		adj[j] = new node(i, adj[j]);
		adj[i] = new node(j, adj[i]);
	}
}

void print_leaf(int k) {
	cout << k << "\t";
}

void wide_traverse(int k, void visit(int), bool visited[], link adj[]) {
	queue<int> q;
	q.push(k);

	while (!q.empty()) {
		k = q.front();
		q.pop();
		if (!visited[k]) {
			visit(k);
			visited[k] = 1;

			for (link t = adj[k]; t != 0; t = t->next) {
				if (!visited[t->v]) {
					q.push(t->v);
				}
			}
		}
	}
}

void deep_traverse_stack(int k, void visit(int), bool visited[], link adj[]) {
	stack<int> s;
	s.push(k);

	while (!s.empty()) {
		k = s.top();
		s.pop();
		if (!visited[k]) {
			visit(k);
			visited[k] = 1;

			for (link t = adj[k]; t != 0; t = t->next) {
				if (!visited[t->v]) {
					s.push(t->v);
				}
			}
		}
	}
}

void deep_traverse(int k, void visit(int), bool visited[], link adj[]) {
	visit(k);
	visited[k] = 1;

	for (link t = adj[k]; t != 0; t = t->next) {
		if (!visited[t->v]) {
			deep_traverse(t->v, visit, visited, adj);
		}
	}
}

void wide_search(link adj[]) {
	bool visited[V];
	for (int i = 0; i < V; i++) {
		visited[i] = 0;
	}
	wide_traverse(0, print_leaf, visited, adj);
}

void deep_search(link adj[]) {
	bool visited[V];
	for (int i = 0; i < V; i++) {
		visited[i] = 0;
	}
	deep_traverse(0, print_leaf, visited, adj);
}

void deep_search_stack(link adj[]) {
	bool visited[V];
	for (int i = 0; i < V; i++) {
		visited[i] = 0;
	}
	deep_traverse_stack(0, print_leaf, visited, adj);
}

int main() {

	/*int adj[V][V];
	fill_adjacency_matrix(adj);*/

	link adj_list[V];
	fill_adjacency_list(adj_list);

	deep_search(adj_list);
	cout << endl;

	wide_search(adj_list);
	cout << endl;

	deep_search_stack(adj_list);

	return 0;
}
