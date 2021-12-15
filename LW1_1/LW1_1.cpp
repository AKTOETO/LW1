#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>

using namespace std;

vector<pair<int, int>> edges;

vector<int> visited_nodes;
vector<int> answer;

void printEdges()
{
	cout << "\tedges:\n";
	for (int i = 0; i < edges.size(); i++)
	{
		cout << " " << i + 1 << ") "
			<< edges[i].first + 1 << " -> "
			<< edges[i].second + 1 << endl;
	}
	cout << endl;
}

template<typename  T>
void printVec(vector<T> v)
{
	for (T n : v)
		cout << ((n >= 0) ? (n + 1) : n) << " ";
	cout << endl;
}

void addEdge(int u, int v)
{
	edges.push_back(make_pair(u,v));
}

void readMatrix(string str)
{
	ifstream fin(str);
	int sizeMatr, el;

	// считал размер матрицы смежности
	fin >> sizeMatr;
	cout << "\tsize: " << sizeMatr << endl;

	// считал саму матрицу смежности
	for (int i = 0; i < sizeMatr; i++)
	{
		for (int j = 0; j < sizeMatr; j++)
		{
			fin >> el;
			if (el)
			{
				addEdge(i, j);
				cout << " added edge: " << i + 1 << " -> " << j + 1 << endl;
			}
		}
	}
	cout << "count of edges: " << edges.size() << endl;
}

void euler(int n)
{

	// выход, если закончились рёбра
	if (edges.size() == 0)
	{
		visited_nodes.push_back(n);
		return;
	}

	// проверка на отсутствие ребер из вершины n
	if (n == -1)
	{
		answer.push_back(visited_nodes[visited_nodes.size() - 1]);
		visited_nodes.pop_back();
		n = visited_nodes[visited_nodes.size() - 1];
	}
	else
	{
		// добавление текущей точки в массив посещенных точек
		visited_nodes.push_back(n);
	}

	//следующая точка
	int node = -1;

	// поиск точки, в которую мы можем попасть из текущей точки
	for (int i = 0; i < edges.size(); i++)
	{
		if (edges[i].first == n)
		{
			node = edges[i].second;
			edges.erase(edges.begin() + i);
			break;
		}
	}

	// печать вектора посезенных элементов
	cout << "visited_nodes: ";
	printVec(visited_nodes);
	cout << "answer: ";
	printVec(answer);

	// Печать рёбер
	printEdges();

	// Расчет следующего пути
	euler(node);
	return;
}

bool isEuler()
{
	// Проверка равенства полусумм входа и выхода
	for (int j = 0; j < edges.size(); j++)
	{
		int sumIn = 0, sumOut = 0;
		for (int i = 0; i < edges.size(); i++)
		{
			if (edges[i].first == j)
				sumIn++;
			if (edges[i].second == j)
				sumOut++;
		}
		if (sumIn != sumOut)
			return false;
	}
	return true;
}

int main()
{
	// считывание матрицы смежности
	readMatrix("data.txt");

	// TODO добавить проверку на существование эйлерова цикла
	if (!isEuler())
	{
		cout << "Graph is not euler's\n";
		return 0;
	}

	// вызвал метод поиска эйлерова цикла c вершины 0
	euler(2);

	// Вывод эйлерова цикла
	reverse(visited_nodes.begin(), visited_nodes.end());
	answer.insert(answer.end(), visited_nodes.begin(), visited_nodes.end());
	reverse(answer.begin(), answer.end());

	// печать ответа
	cout << "answer: ";
	printVec(answer);

	return 0;
}