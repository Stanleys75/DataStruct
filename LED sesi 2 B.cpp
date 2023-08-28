#include<stdio.h>
#include<stdlib.h>

struct node{
	int val;
	struct node *next;
	struct node *prev;
} *head = NULL , *tail = NULL;

node *createNewNode(int val){
	struct node *newNode = (struct node*) malloc (sizeof(node));
	newNode -> val = val;
	newNode -> next = NULL;
	newNode -> prev = NULL;
	
	return newNode;
}

void insertFront(int val){
	
	node *newNode = createNewNode(val);
	
	if(!head){
		head = tail =newNode;
	} else {
		newNode -> next = head;
		head -> prev = newNode;
		head = newNode;
	}
	
}

void insertBehind(int val){
	
	struct node *newNode = (struct node*) malloc (sizeof(node));
	newNode -> val = val;
	newNode -> next = NULL;
	if(!head){
		head = tail =newNode;
	} else {
		tail -> next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
	
}

void deleteFront(){
	
	if(!head){
		return;
	}else if(head==tail){
		free(head);
		head = tail = NULL;
	}else {
		node *temp = head;
		head = head -> next;
		head -> prev = NULL;
		temp -> next = NULL;
		free(temp);
	}
}

void deleteBehind(){
	
	if(!head){
		return;
	}else if(head==tail){
		free(head);
		head = tail = NULL;
	}else {
		node *temp = tail;
		tail = tail->prev;
		tail -> next = NULL;
		
		free(temp);
		
	}
}

void printLinkedList(){
	struct node *temp = head;
	
	while(temp != NULL){
		if(temp != tail){
		printf("%d -> ", temp->val);	
		} else {
			printf("%d -> NULL", temp->val);
		}
		temp = temp->next;
		
	}	
	
}

int main(){
	insertFront(10);
	insertFront(5);
	insertBehind(7);
	insertFront(20);
	insertBehind(25);
	printLinkedList();
	printf("\n");
	deleteFront();
	deleteFront();
	deleteBehind();
	printLinkedList();
	return 0;
}
