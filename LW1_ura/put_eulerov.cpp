#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>

using namespace std;

vector<pair<int, int>> edges;

stack<int> st;
vector<int> result;

void addEdge(int u, int v)
{
	edges.push_back(make_pair(u, v));
}

void readMatrix(string str)
{
	// считывание файла
	ifstream fin(str);
	int sizeMatr, el;

	//считал размер матрицы смежности
	fin >> sizeMatr;
	cout << "\tsize: " << sizeMatr << endl;

	//считал саму матрицу смежности
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

bool isLinked(int n, int& index)
{
	for (int i = 0; i < edges.size(); i++)
	{
		if (edges[i].first == n)
		{
			index = i;
			return true;
		}
	}
	return false;
}

void euler(int n)
{
	st.push(n);
	while (!st.empty())
	{
		n = st.top();
		// индекс ребра с вершиной, связанной с n
		int index;
		if (isLinked(n, index))
		{
			//cout << "n: " << n << " edge index: " << index << endl;
			st.push(edges[index].second);
			edges.erase(edges.begin() + index);
		}
		else
		{
			//cout << "st.top() = " << st.top() << endl;
			result.push_back(st.top());
			st.pop();
		}
	}
	return;
}

bool isEuler(int& n)
{
	bool flag1 = false, flag2 = false;
	for (int j = 0; j < edges.size(); j++)
	{
		int sumIn = 0, sumOut = 0;
		for (int i = 0; i < edges.size(); i++)
		{
			if (edges[i].first == j)
				sumOut++;
			if (edges[i].second == j)
				sumIn++;
		}

		if (sumIn - sumOut == 1)
		{
			if (flag1)
				return false;
			flag1 = true;
		}
		if (sumIn - sumOut == -1)
		{
			if (flag2)
				return false;
			flag2 = true;
			n = j;
		}
	}
	return flag1 && flag2;
}

int main()
{
	// считывание матрицы смежности
	readMatrix("data1.txt");

	// начальный элемент
	int n;

	// проверка на существование эйлерова пути
	if (!isEuler(n))
	{
		cout << "Graph is not euler's\n";
		return 0;
	}
	else
	{
		cout << "Graph is euler's\n";
	}

	// вызвал метод поиска эйлерова цикла c вершины n
	euler(n);

	// инвертирование вектора
	reverse(result.begin(), result.end());

	// печать ответа
	// Вывод эйлерова пути
	cout << "answer: ";
	for (int i = 0; i < result.size(); i++)
		cout << result[i] + 1 << " ";

	return 0;
}