#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int getHash(char name[]){
	char temp = name[0];
	return temp % 3;
}

struct data{
	char name[20];
	int age;
	
	struct data* next;
	struct data* prev;
	
} *head[3], *tail[3];
 
struct data* createData(char name[], int age){
	
	struct data* curr = (data*)malloc(sizeof(data)); 
	curr -> age = age;
	strcpy(curr->name,name);
	curr->prev = NULL;
	curr->next = NULL;
	
	return curr;
} 

void push(struct data* curr){
	
	int index = getHash(curr->name);
	
	if(!head[index]){
		head[index] = tail[index] = curr;
	}else{
		tail[index] -> next = curr;
		curr -> prev = tail[index];
		tail[index] = curr;
	}
		
}

void pop(char name[20]){

	int index = getHash(name);
	
	if(!head[index]){
		
		return;
		
	} else if(head[index] == tail[index] && strcmp(head[index]->name,name)==0){
		
		struct data* temp = head[index];
		head[index] = tail[index] = NULL;
		return;
		
	}else if(strcmp(head[index]->name,name) == 0){
		struct data* temp = head[index];
		head[index] = head[index]->next;
		temp -> next = NULL;
		head[index] -> prev = NULL;
		
		free(temp);
	
		
	}else if (strcmp(tail[index]->name,name) == 0){
		struct data* temp = tail[index];
		tail[index] = tail[index] -> prev;
		temp -> prev = NULL;
		tail[index] -> next = NULL;
		
		free(temp);
		
		
	} else{
		struct data* temp = head[index];
		while(temp != NULL && strcmp(temp->name,name) != 0){
			temp = temp->next;
		}
		
		
		if(temp==NULL){
			return;
		}
		
		struct data* temp1 = temp->prev;
		struct data* temp2 = temp->next;
		
		temp -> next = temp -> prev = NULL;
		free(temp);
		temp1 -> next = temp2;
		temp2 -> prev = temp1;
	}
}

void view(){
	
	for(int i=0; i<3; i++){
		struct data* temp = head[i];
		
		printf("Index %d:  \n",i);
	
		while(temp != NULL){
			printf("%s - %d\n", temp->name, temp->age);
			temp = temp->next;
		}	
		puts("=====================");
	}
	
}



int main(){
	
	struct data* orang1 = createData("CC", 40);
	struct data* orang2 = createData("JE", 20);
	struct data* orang3 = createData("BE", 50);
	struct data* orang4 = createData("eX", 60);
	struct data* orang5 = createData("sX", 60);
	struct data* orang6 = createData("fX", 60);
	struct data* orang7 = createData("gX", 60);
	struct data* orang8 = createData("bX", 60);
	struct data* orang9 = createData("IX", 60);
	struct data* orang10 = createData("IX", 60);
	push(orang1);
	push(orang2);
	push(orang3);
	push(orang4);
	push(orang5);
	push(orang6);
	push(orang7);
	push(orang8);
	push(orang9);
	push(orang10);
	
	view();
	
	return 0;
}
