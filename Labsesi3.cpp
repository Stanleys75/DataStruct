#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Mahasiswa{
	int age;
	char name[50];
	Mahasiswa *prev, *next;
}*head=NULL,*tail=NULL;

Mahasiswa* createNode(int age,char name[]){
	
	Mahasiswa* newNode = (Mahasiswa*)malloc(sizeof(Mahasiswa));
	newNode -> age = age;
	strcpy(newNode->name, name);
	newNode -> prev = NULL;
	newNode -> next = NULL;
	
	return newNode;
}

void pushHead(int age,char name[]){
	
	Mahasiswa* node = createNode(age,name);
	
	if(!head){
		head = tail = node;
	} 
	else{
		head->prev=node;
		node->next=head;
		head = node;
	}
	
}

void pushTail(int age,char name[]){
	
	Mahasiswa* node = createNode(age,name);
	
	if(!head){
		head = tail = node;
	} 
	else{
		tail->next=node;
		node->prev=tail;
		tail = node;
	}
	
}

void pushMid(int age,char name[]){
	
	Mahasiswa* node = createNode(age,name);
	
	if(!head){
		head = tail = node;
	} 
	else{
		if(age < head->age){
			pushHead(age,name);
		}
		else if(age > tail->age){
			pushTail(age,name);
		}else {
			Mahasiswa* curr = head;
			
			while(curr->next != NULL && curr->next->age <= age){
				curr = curr->next;
			}
			
			curr->next->prev = node;
			node->prev = curr;
			node->next = curr->next;
			curr->next = node;
			
		} 
		
	}
	
}

void popHead(){
	
	if(!head){
		return;
	} else{
		if(head==tail){
			Mahasiswa* temp = head;
			free(temp);
			head=tail=NULL;
		} else {
			Mahasiswa* temp = head;
			head = head->next;
			free(temp);
			
			head->prev = NULL;
			
		}
		
		
	}
}

void popTail(){
	
	if(!head){
		return;
	} else{
		if(head==tail){
			Mahasiswa* temp = head;
			free(temp);
			head=tail=NULL;
		} else {
//			Mahasiswa* temp = head;
//			
//			while(temp->next!=tail){
//				temp = temp->next;
//			}
//			
//			free(tail);
//			temp->next=NULL;
//			tail = temp;
			
			Mahasiswa* temp = tail;
			
			tail=tail->prev;
			free(temp);
			tail->next = NULL;
		}
		
		
	}
}

void popMid(int age){
	
	if(!head){
		return;
	} else{
		if(head==tail && head->age == age){
			Mahasiswa* temp = head;
			free(temp);
			head=tail=NULL;
		} else if(head->age==age) {
			popHead();
		} else if(tail->age==age){
			popTail();
		} else {
			Mahasiswa* temp = head;
			
			while(temp != NULL && temp->age!=age){
				temp= temp->next;
			}
			
			temp->next->prev=temp->prev;
			temp->prev->next=temp->next;
			free(temp);
			
		}
		
		
	}
}

void printAll(){
	
	Mahasiswa* curr = head;
	
	while(curr){
		printf("%d %s\n", curr->age,curr->name);
		curr = curr->next;
	}
		
	
}

void search(int age){
	Mahasiswa* curr = head;
	
	while(curr != NULL && curr->age!=age){
		curr = curr->next;
	}	
	
	if(curr != NULL){
		printf("Found: %d %s\n", curr->age, curr->name);
	} else {
		printf("Not Found");
	}
	
}

int main(){
	pushHead(4, "Tom");
	popHead();
	pushTail(20, "lala");
	pushHead(90, "Jerry");
	pushHead(15, "Clarissa");
	pushHead(9, "Jimmy");
	pushTail(23, "lili");
	pushMid(65, "Mary");
	popMid(20);
	popTail();
	
	printAll();
	search(90);
	search(1);
	
	return 0;
}
