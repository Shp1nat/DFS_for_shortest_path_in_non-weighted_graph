#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#define SIZE 10 //Количество вершин в графе
using namespace std;
class Matrix
{
private:
	int graph[SIZE][SIZE]; //граф
public:
	Matrix()
	{
		int b[SIZE][SIZE] = {
		{0, 1, 1, 0, 1, 0, 0, 0, 1, 1},
		{0, 0, 1, 1, 0, 1, 0, 0, 1, 0},
		{0, 1, 0, 0, 1, 0, 0, 0, 1, 0},
		{1, 0, 1, 0, 1, 1, 1, 1, 0, 0},
		{0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 0, 1, 1, 0, 1},
		{1, 1, 0, 1, 0, 0, 0, 0, 1, 0},
		{0, 1, 0, 1, 0, 1, 1, 0, 1, 0},
		{0, 1, 1, 0, 1, 0, 0, 0, 0, 1},
		{0, 0, 1, 1, 0, 1, 1, 1, 0, 0},
		};
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				graph[i][j] = b[i][j];
	}
	void AddToMatrix(int _i, int _j, int _temp)
	{
		graph[_j][_i] = _temp;
		if (_i == _j) graph[_j][_i] = 0;
	}
	int GetFromMatrix(int _i, int _j)
	{
		return graph[_i][_j];
	}
	vector <int> DFS(int _start, int _end)
	{
		bool visited[SIZE]; //Массив пройденных врешин
		int ways[SIZE]; //Массив родительских вершин
		for (int i = 0; i < SIZE; i++)
			visited[i] = 0;
		stack <int> s1;
		visited[_start] = 1;
		ways[_start] = -1;
		s1.push(_start);
		while (!s1.empty())
		{
			int unit = s1.top();
			s1.pop();
			visited[unit] = 1;
			for (int i = 0; i < SIZE; i++)
			{
				if ((visited[i] == 0) && (graph[unit][i] == 1))
				{
					s1.push(i);
					ways[i] = unit;
				}
			}
		}
		int dne = _end;
		int _count = 0;
		do {
			_count++;
			dne = ways[dne];
		} while (dne != ways[_start]);
		int* rev = new int[_count];
		int i = 0;
		rev[i] = _end;
		i++;
		do {
			rev[i] = ways[_end];
			i++;
			_end = ways[_end];
		} while (_end != _start);
		i--;
		vector <int> ForOutput;
		while (i >= 0)
		{
			ForOutput.push_back(rev[i]);
			i--;
		}
		return ForOutput;
	}
};
Matrix CreateMatrix(Matrix m)
{
	cout << "\nВведите матрицу 10 на 10: " << endl;
	int temp = 0;
	for (int j = 0; j < SIZE; j++)
		for (int i = 0; i < SIZE; i++)
		{
			cin >> temp;
			m.AddToMatrix(i, j, temp);
		}
	return m;
}
void OutputMatrix(Matrix m)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			cout << setfill(' ') << setw(5) << m.GetFromMatrix(i, j);
		cout << endl;
	}
}
void OutputWay(vector <int> _vector)
{
	cout << "Путь: ";
	for (unsigned i = 0; i < _vector.size(); i++)
	{
		cout << _vector[i] + 1 << " ";
	}
	cout << endl;
}
int main()
{
	setlocale(LC_ALL, "");
	Matrix M;
	int start, end, choice;
	cout << "Будете вводить собственную матрицу(1) или взять готовую(0)?: ";
	cin >> choice;
	if (choice)
		M = CreateMatrix(M);
	OutputMatrix(M);
	while (true)
	{
		cout << "Из какой вершины начинается путь?: ";
		cin >> start;
		cout << "До какой точки рассчитать маршрут?: ";
		cin >> end;
		if ((start == end) || (start > SIZE) || (end > SIZE)) cout << "Ошибка!\n";
		else
			OutputWay(M.DFS(start - 1, end - 1));
	}
	return 0;
}