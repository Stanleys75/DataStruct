#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#define SIZE 120

struct data{
	char nama[100];
	char ID[100];
	char Rnama[199];
	char Rdesc[199];
	char Rjob[100];
	int age; int number;
	int Rmember;
	int Rtool;
	
	data *next;
	
} *head[SIZE], *tail[SIZE];

data *createNode(char nama[], char ID[], char Rnama[], char Rdesc[],char Rjob[], int age,int Rtool,int Rmember,int number){
	data *newNode = (data*)malloc(sizeof(data));
	
	strcpy(newNode->nama,nama);
	strcpy(newNode->ID,ID);
	strcpy(newNode->Rnama, Rnama);
	strcpy(newNode->Rdesc,Rdesc);
	strcpy(newNode->Rjob,Rjob);
	newNode -> age = age;
	newNode -> Rmember = Rmember;
	newNode -> Rtool = Rtool;
	newNode -> number = number;
	newNode ->next = NULL;
	
	return newNode;
}

int hash (char ID[]){
	int key = 0;
	key = ID[0] + ID[1] + ID[2] + ID[3] + ID[4];
	
	return key%SIZE;
}

int number = 0;

void view(){
	int sum;
	system("cls");
	
	for(int i=0;i<SIZE;i++){
		if(head[i] == NULL){
			sum += 1;
		}
	}
	
	if(sum!=SIZE){
		for(int i=0;i<SIZE;i++){
			struct data *ptr = head[i];
			
			while(ptr!=NULL){
				printf("\n");
				printf("Research Number %d\n", ptr->number);
				printf("Research ID: %s\n", ptr->ID);
				printf("Research Name: %s\n", ptr->Rnama);
				printf("research Description: %s\n", ptr->Rdesc);
				printf("Leader Name: %s\n", ptr->nama);
				printf("Leader Job: %s\n", ptr->Rjob);
				printf("Research Member: %d\n", ptr->Rmember);
				printf("Tools used: %d\n", ptr->Rtool);
				
				ptr = ptr->next;
			}
		}
	} else {
		printf("There is no research.\n");return;
	}
	
	
}

void insert(char nama[], char ID[], char Rname[], char Rdesc[],char Rjob[], int age,int Rtool,int Rmember,int number){
	data *insertdata = createNode(nama,ID,Rname,Rdesc,Rjob,age,Rtool,Rmember,number);
	
	int idx = hash(ID);
	
	if(head[idx] == NULL){
		head[idx]=tail[idx]=insertdata;
	} else{
		tail[idx]->next = insertdata;
		tail[idx] = insertdata;
	}
}

void deletes(char ID[]){
	int idx = hash(ID);
	
	if(head[idx]!=NULL){
		if(!head[idx]){
			return;
		}
		else if(strcmp(head[idx]->ID,ID) == 0){
			struct data *temp = head[idx];
			head[idx] = head[idx]->next;
			free(temp);
			temp = NULL;
			printf("Successfully deleted\n");
		} else {
			struct data *curr = head[idx];
			
			while(curr->next!=NULL && strcmp(curr->next->ID,ID)!= 0){
				curr = curr->next;
			}
			
			if(curr->next == NULL){
				printf("NOT FOUND! Can't delete\n");
			}
			
			struct data* temp = curr ->next;
			curr->next=temp->next;
			free(temp);
			temp = NULL;
			printf("Successfully deleted\n");
		}
		
		
	} else {
		printf("NOT FOUND! Can't delete\n");
		
	}
	
}


int main(){
	int pilihan;
	
	mainmenu:
		system("cls");
		printf("Scitek Lab\n");
		printf("=====================\n");
		printf("1. Add Research\n");
		printf("2. View Research\n");
		printf("3. Delete Research\n");
		printf("4. Exit\n");
		printf("Option: ");
		do{
			scanf("%d", &pilihan);	
		}while(pilihan < 1 || pilihan > 4);
		
	switch(pilihan){
		case(1):{
			system("cls");
			
			int len;
			char nama[100];
			do{
				printf("Insert your leader name[min 5 char]: ");
				scanf(" %[^\n]", nama);
				len = strlen(nama);
			} while(len < 5);
			
			int age;
			do{
				printf("Insert your leader age[25 - 60]: ");
				scanf("%d", &age);
			}while (age<25 || age>60);
			
			char Rjob[100];
			do{
				printf("Insert your jobdesk [Gather Sample | Researching Sample | Documentation]: ");
				scanf(" %[^\n]", Rjob);
			}while (strcmp(Rjob, "Gather Sample") != 0 && strcmp(Rjob, "Researching Sample") != 0 && strcmp(Rjob, "Documentation") != 0);
			
			int p;
			char Rnama[190];
			char Rnama2[100];
			char b[100] = " ";
			do{
				printf("Input research name [ends with ""Research""]: ");
				scanf("%s ",Rnama); scanf(" %[^\n]",Rnama2);
				
				
			} while (strcmp(Rnama2,"Research") != 0);
			strcat(Rnama,b);
			strcat(Rnama,Rnama2);
			
			char Rdesc[100];
			int lent;
			do{
				printf("Input research description [length between 10 - 50]: ");
				scanf(" %[^\n]", Rdesc);
				lent = strlen(Rdesc);
			} while (lent<10 || lent>50);
			
			int Rmember;
			do{
				printf("Input amount of research members [more than 5]: ");
				scanf("%d", &Rmember);
			} while(Rmember<=5);
			
			int Rtool;
			do{
				printf("Input amount of tools that has been used [more than 0]: ");
				scanf("%d", &Rtool);
			} while(Rtool<0);
			
			number += 1;
			char ID[100];
			char num[199];
			strcpy(ID, "RE");
			sprintf(num , "%d%d%d", rand()%10, rand()%10, rand()%10);
			
			strcat(ID,num);
			
			printf("Successfully Add a new research!\n");
			
			insert(nama,ID,Rnama,Rdesc,Rjob,age,Rtool,Rmember,number);
			printf("Press enter to continue...\n");
			getch(); goto mainmenu;
			
			
			
			break;
		} 
		
		case(2):{
			
			
			view();
			printf("Press enter to continue...\n");
			
			getch(); goto mainmenu;
			break;
		}
		case(3):{
			
			view();
			char IDDel[10];
			printf("Input ID you want to delete: ");
			scanf(" %[^\n]",IDDel);
			deletes(IDDel);
			printf("Press enter to continue...\n");
			getch(); goto mainmenu;
			break;
		}
		case(4):{
			printf("Thank you");
			break;
		}
	}
	
	return 0;
}
