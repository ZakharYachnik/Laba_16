#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <vector>
#include <iterator>
#include <windows.h>
#include<iostream>

using namespace std;


struct AdjListNode
{
	int dest;
	int weight;
	struct AdjListNode* next;
};

struct AdjList
{
	struct AdjListNode* head;
};

struct Graph
{
	int V;
	struct AdjList* array;
};

struct AdjListNode* newAdjListNode(int, int);
struct Graph* createGraph(int);
void addEdge(struct Graph*, int, int, int);
void printGraph(struct Graph*);
void delEdge(struct Graph*, int);
void delNode(struct Graph*, int);
void printAdjMatrix(struct Graph*);
void printMenu();

int* arrayDelNode;

struct AdjListNode* newAdjListNode(int dest, int weight)
{
	struct AdjListNode* newNode = (AdjListNode*)malloc(sizeof(struct AdjListNode));
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createGraph(int V)
{
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->V = V;
	graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
	int i;
	for (i = 1; i < V; i++)
	{
		graph->array[i].head = NULL;
	}
	arrayDelNode = (int*)malloc(V * sizeof(int));
	memset(arrayDelNode, 0, V * sizeof(int));
	return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight)
{
	struct AdjListNode* newNode = newAdjListNode(dest, weight);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
}

void printGraph(struct Graph* graph)
{
	int v;
	for (v = 1; v < graph->V; ++v)
	{
		struct AdjListNode* pCrawl = graph->array[v].head;
		if (arrayDelNode[v])
		{
			continue;
		}
		cout << "������� " << v << " ������� � ���������: " << endl << endl;


		if (!pCrawl)
		{
			cout << "��� ������� �� ������� � ������� ���������" << endl;
		}
		while (pCrawl)
		{
			cout << "--> ������� �" << pCrawl->dest << " (��� �����: " << pCrawl->weight << ")" << endl;
			pCrawl = pCrawl->next;
		}
		cout << endl;
	}
}

void delEdge(struct Graph* graph, int nEdge)
{
	struct AdjListNode* del, * prevDel, * tmp;
	int counter = 0;
	for (int i = 1; i < graph->V; i++)
	{
		prevDel = NULL;
		del = graph->array[i].head;
		while (del && del->weight != nEdge)
		{
			prevDel = del;
			del = del->next;
		}
		if (del)
		{
			if (prevDel)
			{
				tmp = del;
				prevDel->next = del->next;
				free(del);
				counter++;
			}
			else
			{
				tmp = del;
				graph->array[i].head = del->next;
				free(del);
				counter++;
			}
		}
	}
	if (counter)
	{
		cout << "����� �" << nEdge << " �������!" << endl;
	}
	else
	{
		printf("� ����� ��� ������ �����!\n");
	}
}

void delNode(struct Graph* graph, int nNode)
{
	struct AdjListNode* tmp, * del, * prevDel;
	if (nNode >= 0 && nNode < graph->V)
	{
		if (arrayDelNode[nNode])
		{
			cout << "������� ��� �������!" << endl;
			return;
		}
		if (graph->array[nNode].head)
		{
			del = graph->array[nNode].head;
			while (del)
			{
				tmp = del;
				del = del->next;
				free(tmp);
			}
			graph->array[nNode].head = NULL;
		}

		arrayDelNode[nNode] = 1;
		for (int i = 1; i < graph->V; i++)
		{
			prevDel = NULL;
			if (arrayDelNode[i])
			{
				continue;
			}
			del = graph->array[i].head;
			while (del && del->dest != nNode)
			{
				prevDel = del;
				del = del->next;
			}
			if (del)
			{
				if (prevDel)
				{
					tmp = del;
					prevDel->next = del->next;
					free(del);
				}
				else
				{
					tmp = del;
					graph->array[i].head = del->next;
					free(del);
				}
			}
		}
		cout << "������� �" << nNode << " �������!" << endl;
	}
	else
	{
		cout << "����� ������� �� ����������!" << endl;
	}
}

void printAdjMatrix(struct Graph* graph)
{
	int size = graph->V;
	int** adjMatrix = (int**)malloc(size * sizeof(int));
	for (int i = 1; i < size; i++)
	{
		adjMatrix[i] = (int*)malloc(size * sizeof(int));
	}

	for (int i = 1; i < size; i++)
		for (int j = 1; j < size; j++)
			adjMatrix[i][j] = 0;

	for (int i = 1; i < size; i++)
	{
		struct AdjListNode* node = graph->array[i].head;
		if (arrayDelNode[i])
		{
			continue;
		}
		while (node)
		{
			adjMatrix[i][node->dest] = 1;
			node = node->next;
		}
	}

	cout << "������� ���������:" << endl << endl;
	cout << "    ";
	for (int i = 1; i < size; i++)
	{
		if (arrayDelNode[i])
		{
			continue;
		}
		cout << i << " ";

	}
	cout << endl << "  --";
	for (int i = 1; i < size; i++)
	{
		if (arrayDelNode[i])
		{
			continue;
		}
		cout << "--";

	}
	cout << endl;
	for (int i = 1; i < size; i++)
	{
		if (arrayDelNode[i])
		{
			continue;
		}
		cout << i << "|  ";
		for (int j = 1; j < size; j++)
		{
			if (arrayDelNode[j])
			{
				continue;
			}
			cout << adjMatrix[i][j] << " ";

		}

		cout << endl;
	}
}



void printMenu()
{
	cout << endl;
	cout << "-------------------------------------------------";
	cout << "\n| 1.������� ����                                |\n";
	cout << "-------------------------------------------------\n";
	cout << "| 2.������� ���� � ������� 1                   |\n";
	cout << "-------------------------------------------------\n";
	cout << "| 3.������� ������� � ������� 3                 |\n";
	cout << "-------------------------------------------------\n";
	cout << "| 4.������� ���� �� �����                       |\n";
	cout << "-------------------------------------------------\n";
	cout << "| 5.������� ������� ���������                   |\n";
	cout << "-------------------------------------------------\n";
	cout << "| 6.����� �� ���������                          |\n";
	cout << "-------------------------------------------------\n\n";

}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	printMenu();
	int choice;
	int nNode = 3;
	int nEdge = 1;
	bool flag = true;
	struct Graph* graph = NULL;
	cout << "��� �����: " << endl;
	while (true)
	{
		cin >> choice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(3000, '\n');
		}
		else
		{
			break;
		}
	}
	while (choice != 6)
	{
		switch (choice)
		{
		case 1:
		{
			if (!graph)
			{
				graph = createGraph(6);

				addEdge(graph, 1, 2, 2);

				addEdge(graph, 1, 3, 3);

				addEdge(graph, 1, 4, 1);

				addEdge(graph, 2, 4, 1);

				addEdge(graph, 2, 5, 3);

				addEdge(graph, 2, 3, 4);

				addEdge(graph, 3, 4, 1);

				addEdge(graph, 3, 5, 2);

				addEdge(graph, 4, 5, 2);

				cout << "���� ������!" << endl;
			}
			else
			{
				cout << "���� ��� ����������!" << endl;
			}
		}
		break;
		case 2:
		{
			if (graph)
			{
				if (nEdge == 1)
				{
					delEdge(graph, nEdge);
					nEdge++;
				}
				else
				{
					cout << "����� ��� �������!" << endl;
				}
			}
			else
			{
				cout << "���� �� ����������!" << endl;
			}
		}
		break;
		case 3:
		{
			if (graph)
			{
				if (nNode == 3)
				{
					delNode(graph, nNode);
					nNode++;
				}
				else
				{
					cout << "������� ��� �������!" << endl;
				}
			}
			else
			{
				cout << "���� �� ����������!" << endl;
			}
		}
		break;
		case 4:
			if (graph)
			{
				printGraph(graph);
			}
			else
			{
				cout << "���� �� ����������!" << endl;
			}
			break;
		case 5:
			if (graph)
			{
				printAdjMatrix(graph);
			}
			else
			{
				cout << "���� �� ����������!" << endl;
			}
			break;
		}
		printMenu();
		cout << "��� ����� " << endl;
		while (true)
	{
		cin >> choice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(3000, '\n');
		}
		else
		{
			break;
		}
	}
	}
}

