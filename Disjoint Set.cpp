#include<stdio.h>

int parent[100] = {0};
void makeset(int verticesCount){
	for(int i = 0; i < verticesCount;i++){
		parent[i]=i;
	}
	
}

int findParent(int vertex){
	if(parent[vertex] == vertex)
		return vertex;
	
	parent[vertex] = findParent(parent[vertex]);
	return findParent(parent[vertex]);
}

void joinVertex(int vertexA, int vertexB){
	// ancestor
	int ancestorA = findParent(vertexA);
	int ancestorB = findParent(vertexB);
	
	parent[ancestorA] = ancestorB;
	
}

void isSameSet(int vertexA, int vertexB){
	if(findParent(vertexA)==findParent(vertexB)){
		printf("true\n");
		
	}	
	else{
		printf("false\n");
	}
}

int main(){
	
	makeset(5);
	
	joinVertex(0,1);
	joinVertex(1,2);
	joinVertex(2,4);
	
	for(int i=0;i<5;i++){
		printf("%d",parent[i]);
	}
	
	isSameSet(3,0);
	
	return 0;
}
