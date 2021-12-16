#include<iostream>
#include <fstream>
#include <cmath>
#include <Windows.h>

using namespace std;

int main()
{
	SetConsoleOutputCP(65001);

	//Ввод файла в программу
	ifstream file("data18.txt");
	const int V = 9; 
	int D[V][V];     
	int E[V] = {};
	int rad = 10000; 
	int diametr = -1;

	// ввод матрицы смежности
	for (int i = 0; i < V; ++i)
	{
		for (int j = 0; j < V; ++j)
		{
			file >> D[i][j];
		}
	}

	//расчет кратчайших путей
	for (int k = 0; k < V; ++k)
	{
		for (int i = 0; i < V; ++i)
		{
			for (int j = 0; j < V; ++j)
			{
				if (i != j && D[i][k] != 0 && D[k][j] != 0)					
					if ((D[i][j] > (D[i][k] + D[k][j])) || D[i][j] == 0)	
						D[i][j] = (D[i][k] + D[k][j]);						
			}
		}
	}

	cout << "Матрица кратчайших путей\n";
	for (int i = 0; i < V; ++i)
	{
		for (int j = 0; j < V; ++j)
			cout << D[i][j] << " ";
		cout << endl;
	}

	//Расчет эксцентриситета
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			//Выбор максимума среди изначального значения и по матрице кратчайших путей
			E[i] = max(E[i], D[i][j]); 
		}
	}

	//for
	for (int i = 0; i < V; ++i)//Вывод кратчайших расстояний до самой дальней вершины от данной
	{
		cout << "Значение эксцентриситета для вершины D" << i + 1 << " = " << E[i] << endl;
	}//end for

	//for
	for (int i = 0; i < V; i++)
	{
		rad = min(rad, E[i]);
		diametr = max(diametr, E[i]);
	}//end for

	cout << "Вывод радиуса графа:" << rad << endl;

	cout << "Вывод диаметра графа:" << diametr << endl;

	for (int i = 0; i < V; i++)
	{
		if (E[i] == rad)
			cout << "центр - " << i + 1 << endl;
	}

	return 0;
}