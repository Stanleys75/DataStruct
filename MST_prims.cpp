#include <limits.h>
#include <stdio.h>
#define N 5

int MST[N][2]; //menampung path MST
int parent[N]; //menampung parent dari vertex yang memiliki nilai terkecil
int value[N]; //menampung nilai terkecil
int visited[N];//menandai vertex yang sudah divisit

int minValue(int value[], int visited[])
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < N; v++)
		if (visited[v]==0 && value[v] < min)
		{
			min = value[v];
			min_index = v;
		}
	return min_index;
}

void primMST(int start, int graph[N][N])
{
	for (int i = 0; i <N; i++)
	{
		value[i]=INT_MAX;//value[i]=100
		visited[i]=0;
		parent[i]=0;
	}
	
	//mengubah slot yang bernilai 0 menjadi nilai max
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			if(graph[i][j]==0)
				graph[i][j]=INT_MAX;//graph[i][j]=100;
		}
	}

	int u=start;
	int k=0;
	visited[start]=1;
	for (int count = 0; count < N-1; count++) {
		for (int v = 0; v < N; v++)
		{
			if (graph[u][v]<INT_MAX && visited[v] == 0 && graph[u][v] < value[v])
				parent[v] = u, value[v] = graph[u][v];
		}
		u = minValue(value, visited); //find vertex with the smallest value
		visited[u] = 1;
		MST[k][0]=parent[u];
		MST[k][1]=u;
		k++;
	}
}

void printMST()
{
	int sumCost=0;
	for(int i=0; i<N-1; i++)
	{
		printf("%d - %d = %d\n", MST[i][0], MST[i][1], value[MST[i][1]]);
		sumCost+=value[MST[i][1]];
	}
	printf("Total cost is: %d\n", sumCost);
}


int main()
{
	/* Let us create the following graph
		2 3
	(0)--(1)--(2)
	| / \ |
	6| 8/ \5 |7
	| /	 \ |
	(3)-------(4)
			9		 */
	int graph[N][N] = { { 0, 2, 0, 6, 0 },
						{ 2, 0, 3, 8, 5 },
						{ 0, 3, 0, 0, 7 },
						{ 6, 8, 0, 0, 9 },
						{ 0, 5, 7, 9, 0 } };

	primMST(0, graph);
	printMST();

	return 0;
}

