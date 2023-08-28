#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

int sum = 0;
struct data{
	char nama[200];
	char ID[10]; char FID[20];
	data *next;
	data *prev;
}*head, *tail;

data* createNode(char nama[],char ID[],char FID[]){
	data *newNode = (data*)malloc(sizeof(data));
	
	strcpy(newNode->ID,ID);
	strcpy(newNode->FID,FID);
	strcpy(newNode->nama,nama);	
	newNode->next=NULL;
	newNode->prev=NULL;
	
	return newNode;
}

void pushTail(char nama[],char ID[],char FID[]){
	
	data* node = createNode(nama,ID,FID);
	
	if(!head){
		head = tail = node;
	} 
	else{
		tail->next=node;
		node->prev=tail;
		tail = node;
	}
	
}


view(){
	struct data* curr = head;
	
	if(sum == 0){
		printf("No Data !\n\n");
	} else {
		while(curr != NULL){

			printf("%-10s    %-40s\n", curr->nama,curr->ID);
			
			curr = curr->next;	
			
			
		}
		
	}
}

void pushMid(char nama[],char ID[],char FID[]){
	
	data* node = createNode(nama,ID,FID);
	data* curr = head;
	
	if(!head){
		head = tail = node;
	} 
	else{
		if(curr->ID == FID ){
			pushTail(nama,ID,FID);
		}
		else if(curr->ID == FID){
			pushTail(nama,ID,FID);
		}
		else{
		
			
			while(curr->next != NULL && curr->next->ID != FID){
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
			data* temp = head;
			free(temp);
			head=tail=NULL;
		} else {
			data* temp = head;
			head = head->next;
			free(temp);
			
			head->prev = NULL;
			
		}
		
		
	}
}

int main(){
	int pilihan;
	
	mainmenu:
		do{
		system("cls");
		printf("_________________________\n");
		printf(" FT World Tour Concert\n");
		printf("_________________________\n\n");
		printf("      Name             Ticket ID\n");
		printf("__________________________________\n");
		view();
		printf("1. Register New Audience\n");
		printf("2. Enter the Concert Hall\n");
		printf("3. Search Queue Number\n");
		printf("4. Update Audience Data\n");
		printf("5. Exit\n");
		printf("Input : "); scanf("%d", &pilihan);			
		} while(pilihan < 1 && pilihan > 5);

		
	switch(pilihan){
		case(1):{
			char nama[100];
			int len;
			do{
				printf("Audience Name [2-20 characters]: ");
				scanf(" %[^\n]", nama); getchar();
				len = strlen(nama);
			} while(len<2 || len>20);
			
			char ID[20];
			int lens;
			do{
				printf("Ticket ID [5 digits number]: ");
				scanf(" %[^\n]", ID); getchar();
				lens = strlen(ID);
			} while(lens != 5);
			
			char ans[10];
			do{
				printf("Do you have a friend in the queue [yes/no]? ");
				scanf(" %[^\n]", ans); getchar();
			} while(strcmp(ans,"yes")!=0 && strcmp(ans,"Yes")!=0 && strcmp(ans,"no")!=0 && strcmp(ans,"No")!=0);
			
			char FID[10];
			int len2;
			if(strcmp(ans,"yes")==0 || strcmp(ans,"Yes")==0){
				do{
					printf("Friend's Ticket ID [5 digits number]: ");
					scanf( " %[^\n]", FID); getchar();
					len2 = strlen(FID);
				} while(len2 != 5);
				pushMid(nama,ID, FID);
				
			} else{
				pushTail(nama,ID,FID);
				
			}
			
			
			printf("ADD DATA SUCCESS !!!\n\n\n");
			sum += 1;
			
			
			getch();
			system("cls");
			goto mainmenu;
			
			
				
			break;
		}
		case(2):{
			if(sum == 0){
				printf("Data not found!\n");
				
			} else {
				printf("%s enter the Concert Hall\n", head->nama);
				popHead();
			}
			getch();
			system("cls");
			goto mainmenu;
			break;
		}
	}
}
