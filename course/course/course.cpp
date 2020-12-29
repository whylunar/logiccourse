// course.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <queue>
#include <locale.h>
#include <malloc.h>
#include <windows.h>

using namespace std;

struct Edges {
	int u, v, w;
};

const int inf = 1000000000;
const int Vmax = 1000;
const int Emax = Vmax * (Vmax - 1) / 2;
int i, j, n, e, start;
Edges edge[Emax];
int d[Vmax];
FILE* save;

//алгоритм Беллмана-Форда
void bellman_ford(int n, int s)
{
	save = fopen("save.txt", "a");
	fseek(save, 0L, SEEK_END);
	int i, j;

	for (i = 0; i < n; i++) d[i] = inf;
	d[s] = 0;

	for (i = 0; i < n - 1; i++)
		for (j = 0; j < e; j++)
			if (d[edge[j].u] > d[edge[j].v] + edge[j].w)
				d[edge[j].u] = d[edge[j].v] + edge[j].w;

	for (i = 0; i < n; i++)
		if (d[i] == inf)
		{
			printf("%d -> %d - Нет пути\n", start, i + 1);
			fprintf(save, "%d -> %d - Нет пути\n", start, i + 1);
		}
		else
		{
			printf("%d -> %d -  %d\n", start, i + 1, d[i]);
			fprintf(save, "%d -> %d -  %d\n", start, i + 1, d[i]);
		}
	fclose(save);
}

void rand_Zap_vz_or(int** Matrix, int n)
{
	srand(time(NULL));
	printf("Взвешаный орентированный граф\n");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				Matrix[i][j] = 0;
			}
			if (i < j)
			{
				if (rand() % 100 > 50)
				{
					Matrix[i][j] = rand() % 10;
					if (rand() % 100 > 50)
						Matrix[j][i] = 0;
					else
						Matrix[j][i] = Matrix[i][j];
				}
				else
					if (rand() % 100 > 50)
					{
						Matrix[j][i] = rand() % 10;
						Matrix[i][j] = 0;
					}
					else
					{
						Matrix[i][j] = 0;
						Matrix[j][i] = 0;
					}
			}
		}
}

void rand_Zap_vz_nor(int** Matrix, int n)
{
	srand(time(NULL));
	printf("Взвешаный неорентированный граф\n");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				Matrix[i][j] = 0;
			}
			if (i < j)
			{
				if (rand() % 100 > 50)
					Matrix[i][j] = rand() % 10;
				else
					Matrix[i][j] = 0;
				Matrix[j][i] = Matrix[i][j];
			}
		}
}


void print_G(int** Matrix, int n)
{
	save = fopen("save.txt", "w");
	fprintf(save, "  ");
	printf("  ");
	for (int i = 0; i < n; i++)
	{
		printf("%3d", i + 1);
		fprintf(save, "%3d", i + 1);
	}

	printf("\n\n");
	fprintf(save, "\n\n");
	for (int i = 0; i < n; i++) {
		printf("%2d", i + 1);
		fprintf(save, "%2d", i + 1);
		for (int j = 0; j < n; j++) {

			printf("%3d", Matrix[i][j]);
			fprintf(save, "%3d", Matrix[i][j]);
			
		}
		printf("\n");
		fprintf(save, "\n");
	}
	printf("\n");
	fprintf(save, "\n");
	fclose(save);
}





int main()
{
	setlocale(LC_CTYPE, "rus");
	srand(time(NULL));
	int menu1;
	printf(" 1. Ввести массив с клавиатуры. \n 2. Создание массива произвольного размера, вводимого с клавиатуры. \n ");
	printf("\n\nВыберите пункт меню: ");
	scanf("%d", &menu1);
	while (menu1 > 2)
	{
		printf("\nТакого пункта меню нет. Выберите пункт меню: ");
		scanf("%d", &menu1);
	}

	switch (menu1)
	{
	case 1:
		{
		int i, j, n, type;

		printf("\n Тип вводимого графа:\n 1. Ориентированный\n 2. Неориентированный \n Выберите тип - ");
		scanf("%d", &type);
		while (type > 2)
		{
			printf("\n Номер такого типа не существует\n Выберите тип заново - ");
			scanf("%d", &type);
		}

		printf(" Введите количество вершин графа - ");
		scanf_s("%d", &n);

		int** G = (int**)malloc(n * sizeof(int*)); 
		for (int i = 0; i < n; i++)
		{
			G[i] = (int*)malloc(n * sizeof(int));
		}

		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				G[i][j] = 0;
			}
		}

		if (type == 1)
		{
			for (i = 0; i < n; i++)
			{
				for (j = i + 1; j < n; j++)

				{
					
					
						printf(" Введите расстояние из %d в %d - ", i + 1, j + 1);
						scanf_s("%d", &G[i][j]);

						while (G[i][j] < 0)
						{
							printf("\n");
							printf(" Введите положительное расстояние из %d в %d - ", i + 1, j + 1);
							scanf_s("%d", &G[i][j]);
						}
						
						printf(" Введите расстояние из %d в %d - ", j + 1, i + 1);
						scanf_s("%d", &G[j][i]);

						while (G[j][i] < 0)
						{
							printf("\n");
							printf(" Введите положительное расстояние из %d в %d - ", j + 1, i + 1);
							scanf_s("%d", &G[j][i]);
						}
					
				}
			}
		}
		if (type == 2)
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = i + 1; j < n; j++)

				{
					printf(" Введите расстояние из %d в %d - ", i + 1, j + 1);
					scanf_s("%d", &G[i][j]);
					while (G[i][j] < 0)
					{
						printf("\n");
						printf(" Введите положительное расстояние из %d в %d - ", i + 1, j + 1);
						scanf_s("%d", &G[i][j]);
					}
					G[j][i] = G[i][j];
				}
			}
		}
		printf("\n\n");

		print_G(G, n);
		

		int w = 0;
		e = 0;
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
			{
				w = G[i][j];
				if (w != 0)
				{
					edge[e].v = i;
					edge[e].u = j;
					edge[e].w = w;
					e++;
				}
			}

		printf("Введите стартовую вершину: ");
		scanf("%d", &start);
		printf("\n ");

		printf("Список кратчайших путей: ");
		printf("\n\n ");
		bellman_ford(n, start - 1);

		

		system("pause");

		break;
		}

		case 2:
		{
			int i, j, n, type;
			printf("\n Тип вводимого графа:\n 1. Ориентированный\n 2. Неориентированный \n Выберите тип - ");
			scanf("%d", &type);
			while (type > 2)
			{
				printf("\n Номер такого типа не существует\n Выберите тип заново - ");
				scanf("%d", &type);
			}

			printf(" Введите количество вершин графа - ");
			scanf_s("%d", &n);

			int** G = (int**)malloc(n * sizeof(int*));
			for (int i = 0; i < n; i++)
			{
				G[i] = (int*)malloc(n * sizeof(int));
			}

			if (type == 1)
				rand_Zap_vz_or(G, n);

			if (type == 2)
				rand_Zap_vz_nor(G, n);

			print_G(G, n);
			
			

			int w = 0;
			e = 0;

			for (i = 0; i < n; i++)
				for (j = 0; j < n; j++)
				{
					w = G[i][j];
					
					if (w != 0)
					{
						edge[e].v = i;
						edge[e].u = j;
						edge[e].w = w;
						e++;
					}
				}

			printf("Введите стартовую вершину: ");
			scanf("%d", &start);
			printf("\n ");
			
			printf("Список кратчайших путей: ");
			printf("\n\n ");
			bellman_ford(n, start - 1);

			system("pause");

			break;
		}
	}
}

