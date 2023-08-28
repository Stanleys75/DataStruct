#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node{
	char oprt;
	struct node *next;
} *head = NULL , *tail = NULL;

node *createNewNode(char oprt){
	struct node *newNode = (struct node*) malloc (sizeof(node));
	newNode -> oprt = oprt;
	newNode -> next = NULL;
	
	return newNode;
}

void insertFront(char oprt){
	
	node *newNode = createNewNode(oprt);
	
	if(!head){
		head = tail = newNode;
	} else {
		newNode -> next = head;
		head = newNode;
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
		temp -> next = NULL;
		free(temp);
	}
}

char Prec(char oprt){  // function untuk membandingkan tingkatan operator

	if(oprt == '*' || oprt == '/'){
		return 3;
	} else if (oprt == '+' || oprt == '-'){
		return 2;
	} else if(oprt == '^'){
		return 4;
	} else {
		return 0;
	}
	
}


void printLinkedList(){
	struct node *temp = head;
	
	while(temp){
		if(temp){
			printf("%c", temp->oprt);
		}	
		temp = temp->next;
		
	}	
	
}

int main(){
	
	char string[50] = "A+B*(C-D)/E";
	int len = strlen(string);
	
	for(int i=0;i<len;i++){	
		if(string[i] =='+' || string[i]=='-' || string[i]=='*' || string[i]=='/' || string[i]=='^' || string[i] =='(' || string[i] ==')' ){
			if(!head){
				insertFront(string[i]);
					
			} else if(string[i] == '('){
				insertFront(string[i]);
					
			} else if(string[i] == ')'){
					
				while(head -> oprt != '('){ 
					printf("%c " ,head -> oprt); 
					deleteFront();
				}			
				if(head -> oprt == '('){  
					deleteFront();
				}
						
			} else{
				while(Prec(string[i]) <= Prec(head -> oprt) && Prec(head -> oprt) > 0){ 
					printf("%c ", head -> oprt);
					deleteFront();
				}
				
				insertFront(string[i]);
			}
		}
		
		else {
			printf("%c ", string[i]);
		}
	}
	
	while(head){ 
		printf("%c ", head -> oprt);
		deleteFront();
	}
  	
	
	return 0;
}
