#include<stdio.h>

int heap[100];
int datacounter = 1;

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void check(int size, int i){
	if(datacounter == 1) return;
	
	int min = i;
	int l = i * 2;
	int r = i * 2 + 1;
	
	if(l < size && heap[l] < heap[min]){
		min = l;
	}
	if(r < size && heap[r] < heap[min]){
		min = r;
	}
	if(min != i){
		swap(&heap[i],&heap[min]);
		check(size,min);
	}
}

void insert(int x){
	if(datacounter == 1){
		heap[datacounter] = x;
		datacounter++;
	}
	else{
		heap[datacounter] = x;
		datacounter++;
		
		for(int i=(datacounter-1)/2 ; i>=0;i--){
			check(datacounter,i);
		}
	}
	
}

int pop(){
	if(datacounter == 1) return 0;
	
	int data = heap[1];
	
	heap[1] = heap[datacounter-1];
	heap[datacounter - 1] = 0;
	datacounter--;
	
	for(int i=(datacounter-1)/2; i>=0;i--){
		check(datacounter,i);
	}
	
	return data;
}

void view(){
	for(int i=1; i<datacounter; i++){
		printf("%d\n" , heap[i]);
	}
}

int main(){
	insert(300);
	insert(200);
	insert(100);
	pop();
	pop();
	
	
	view();
	return 0;
}
