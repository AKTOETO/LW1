#include <vector>
#include <iostream>
#include <stack>

using namespace std;

struct edge {
    int to;
    bool deleted;
};

const int maxn = 1e5;
vector<edge> edges;
stack<int> g[maxn];

void addEdge(int u, int v) {
    g[u].push(edges.size());
    edges.push_back({ v, false });
    g[u].push(edges.size());
    edges.push_back({ u, false });
}

void euler(int v) {
    //cout << !g[v].empty() << endl;
    while (!g[v].empty()) {
        int e = g[v].top();
        g[v].pop();
        if (!edges[e].deleted) {
            edges[e].deleted = true;
            euler(e);
        }
    }
    cout << v << " ";
}

int main()
{
    addEdge(1, 4);
    addEdge(1, 5);
    addEdge(1, 2);
    addEdge(2, 7);
    addEdge(2, 8);
    addEdge(3, 5);
    addEdge(3, 6);
    addEdge(4, 7);
    addEdge(4, 8);
    addEdge(5, 7);
    addEdge(5, 8);
    addEdge(6, 7);
    addEdge(6, 8);
    addEdge(7, 1);
    addEdge(7, 9);
    addEdge(8, 3);
    addEdge(8, 9);
    addEdge(9, 4);
    addEdge(9, 6);
    //cout << !g[1].empty() << endl;

    euler(1);
    
	return 0;
}
