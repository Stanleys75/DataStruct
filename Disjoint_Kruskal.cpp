#include <stdio.h>

#define MAX_N 100

struct Edge{
	int source;
	int destination;
	int cost;
};

Edge edges[1000];

int Parent[MAX_N + 5];

void make_set(int n){
	for(int i=1 ; i<=n ; i++){
		Parent[i] = i;
	}
}

int find_parent(int a){
	if( Parent[a] == a ) 
		return a;
	return find_parent(Parent[a]);
}

void merge(int a, int b){
	Parent[find_parent(a)] = find_parent(b);
}

int is_same_set(int a, int b){
	return find_parent(a) == find_parent(b);
}

int main(){
	
	int vertexCount;
	int edgeCount;
	
//	Input number of vertex and edge
	scanf("%d %d", &vertexCount, &edgeCount);
	
//	Create all vertex
	make_set(vertexCount);
	
//	Input all edges
	for( int i=0 ; i<edgeCount ; i++ ){
		int source;
		int destination;
		int cost;		
		scanf("%d %d %d", &source, &destination, &cost);
		
//		Register edges to array
		edges[i].source = source;
		edges[i].destination = destination;
		edges[i].cost = cost;
	}
	
//	Sort based on cost ascending
	for(int i=0 ; i<edgeCount-1 ; i++){
		for(int j=edgeCount-1 ; j>i ; j--){
			if( edges[j].cost < edges[j-1].cost ){
				Edge temp = edges[j];
				edges[j] = edges[j-1];
				edges[j-1] = temp;
			}
		}
	}
	
//	Check sort result
	for(int i=0 ; i<edgeCount ; i++){
		printf("%d - %d = %d\n", edges[i].source, edges[i].destination, edges[i].cost);
	}
	
//	Kruskal ALgorithm
	int MSTCost = 0;
	for( int i=0 ; i<edgeCount ; i++ ){
		if( is_same_set(edges[i].source, edges[i].destination) ){
			continue;
		}
		MSTCost += edges[i].cost;
		merge(edges[i].source, edges[i].destination);
		printf("Chosen Edge: %d - %d (%d)\n", edges[i].source, edges[i].destination, edges[i].cost);
	}
	
	printf("MST Cost: %d\n", MSTCost);
	
//	make_set(8);
//	
//	merge(1, 2);
//	merge(2, 3);
//	
//	merge(4, 6);
//	merge(5, 6);
//	merge(4, 7);
//	
//	printf("1 and 3: %d\n", is_same_set(1, 3));
//	printf("7 and 6: %d\n", is_same_set(7, 6));
//	printf("1 and 7: %d\n", is_same_set(1, 7));

	
	return 0;
}
