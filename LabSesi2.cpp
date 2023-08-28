#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Mahasiswa{
	int umur;
	char nama[50];
	Mahasiswa* next;
}*head = NULL , *tail = NULL;

Mahasiswa* createNewMhs(int umur,char nama[]){
	Mahasiswa* newNode = (struct Mahasiswa*)malloc(sizeof(struct Mahasiswa));
	newNode->umur = umur;
	strcpy (newNode->nama,nama);
	newNode->next = NULL;
	
	return newNode;
}

void pushHead(int umur, char nama[]){
	
	Mahasiswa *newMhs = createNewMhs(umur,nama);
	
	if(!head){
		head = tail = newMhs;
	}
	else {
		newMhs->next = head;
		head = newMhs;
	}
}

void pushTail(int umur, char nama[]){
	
	Mahasiswa *newMhs = createNewMhs(umur,nama);
	
	if(!head){
		head = tail = newMhs;
	}
	else {
		tail->next = newMhs;
		tail = newMhs  ;
	}
}

void pushMid(int umur,char nama[]){
	
	Mahasiswa *newMhs = createNewMhs(umur,nama);
	
	if(!head){
		head = tail = newMhs;
	}
	else {
		if(head->umur > umur){
			pushHead(umur,nama);
		} else if(tail->umur < umur){
			pushTail(umur,nama);
			
		} else{
			Mahasiswa* curr = head;
			while (curr->next != NULL && curr->next->umur < umur){
				curr = curr->next;
			}
			
			newMhs -> next = curr -> next;
			curr->next = newMhs;
		}
	}
}

void popHead(){
	
	if(!head){
		return;
	}
	else{
		
		Mahasiswa* temp = head;
		
		if(head==tail){
			head = tail = NULL;
		}
		else{
			head = head->next;
		}
		
		free(temp);
	}
}

void popTail(){
	
	if(!head){
		return;
	}
	else{
		
		Mahasiswa* temp = head;
		
		if(head==tail){
			head = tail = NULL;
			free(temp);
		}
		else{
			while(temp->next != tail){
				temp = temp -> next;
			}
			
			free(temp->next);
			temp->next = NULL;
			
			tail = temp;
			 
		}
		
		free(temp);
	}
}

void popMid(int umur){
	
	if(!head){
		return;
	}
	else{
		
		Mahasiswa* curr = head;
		
		if(head == tail && head->umur == umur){
			head = tail = NULL;
			free(curr);
		}
		if(head->umur == umur){
			popHead();
		}
		else if(tail->umur == umur){
			popTail();
		}
		else{
			
			while(curr->next != NULL && curr->next->umur != umur){
				curr = curr->next;
			}
			
			Mahasiswa* temp = curr->next;
			curr->next= temp->next;
			
			free(temp);
		}
	}
	
}


void searchMhs(int umur){
	
	Mahasiswa* curr = head;
	
	while(curr!=NULL && curr->umur!= umur){
		curr = curr->next;
	}
	if(curr != NULL){
		printf("found");
	}
	else{
		printf("not found");
	}
}
void printAllMhs(){
	Mahasiswa *curr = head;
	
	while(curr != NULL){
		printf("%d - %s\n", curr->umur, curr->nama);
		curr = curr->next;
	}
}

int main(){
	pushHead(1, "lol");
	pushTail(5, "lol");
	pushTail(4, "lol");
	pushMid (3, "loli");
	pushTail (19,"lala");
	popHead();
	popTail();
	popMid(2);
	searchMhs(5);	
	printAllMhs();
	
}
