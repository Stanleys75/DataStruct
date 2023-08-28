#include<stdio.h>

int heap[100]; //max element 99
int count=0; //menghitung jumlah element yang ada dalam array

int getParentIdx(int idx)
{
	return idx/2;
}

int getLeftChildIdx(int idx)
{
	return idx*2;
}

int getRightChildIdx(int idx)
{
	return idx*2+1;
}

void upHeap(int idx){
	 if(idx<=1){
	 	return;
	 } //kalau dia sudah mencapai root
	 int parent=getParentIdx(idx);//idx/2
	 if(heap[parent]>heap[idx])
	 {
	 	int temp=heap[parent];
	 	heap[parent]=heap[idx];
	 	heap[idx]=temp;
	 	upHeap(parent);
	 }
}

void push(int val){
	count++;
	heap[count]=val;
	upHeap(count);
}

void downHeap(int idx){
	if(idx*2>count){
		return;	
	}
	
	int leftChild=getLeftChildIdx(idx);//index anak kiri
	int rightChild=getRightChildIdx(idx);//index anak kanan
	int smallest=idx; //menyimpan index node yang memiliki nilai terkecil antara node idx, anak kiri, dan anak kanannya
	if(leftChild<=count && heap[leftChild]<heap[smallest]){
		smallest=leftChild;
	}
	if(rightChild<=count && heap[rightChild]<heap[smallest]){
		smallest=rightChild;
	}
	if(smallest==idx){
		return;//leftchild dan rightchild memiliki nilai lebih besar, stop downheap
	}
	
	int temp=heap[idx];
	heap[idx]=heap[smallest];
	heap[smallest]=temp;
	
	downHeap(smallest);
	
}

void pop(){
	if(count<1)return;//mengecek kalau heapnya masih kosong
	printf("Data deleted is %d\n", heap[1]);
	heap[1]=heap[count]; 
	count--;
	downHeap(1);
}

void view(){
	for(int i=1; i<=count; i++)
	{
		printf("%d ", heap[i]);
	}
}


int main()
{
	push(80);
	push(20);
	push(15);
	push(5);
	view();
	puts("");
	pop();
	pop();
	pop();
	pop();
	push(10);
	push(5);
	view();
	return 0;
}
