#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#define SIZE 50

struct data{
	char ID[51];
	char name[100];
	int age;
	char ticket[100];
	int days;
	int price;
	struct data *next;
}*head[SIZE], *tail[SIZE];

data *createnode(char tempID[],char nama[],int umur, char tiket[], int hari, int price){
	data *newnode = (data*)malloc(sizeof(data));
	strcpy(newnode->name,nama);
	strcpy(newnode->ticket,tiket);	
	strcpy(newnode->ID,tempID);		
	newnode->days = hari;
	newnode->age = umur;
	newnode->price = price;
	newnode->next = NULL;
	
	return newnode;
}

int hash(char X[]){
	int key=0;
	int len = strlen(X);
	key = X[len-3] + X[len-2] - X[len-1] - 1;
	
	return key%SIZE;
}

void insert(char tempID[],char nama[],int umur, char tiket[], int hari, int price ){
	data *insertdata = createnode(tempID,nama,umur,tiket,hari,price);
	int idx = hash(tempID);
	
	if(head[idx]==NULL){
		head[idx]=tail[idx]=insertdata;
	}
	else{
		tail[idx]->next=insertdata;
		tail[idx]=insertdata;
	}
}

void view(){
	int tot=0;
	for(int i=0;i<SIZE;i++){
		if(head[i]==NULL){
			tot = tot+1;
		}
	}
	
	if(tot!=SIZE){
		for(int i=0; i<SIZE; i++){
			struct data *ptr = head[i];
			while(ptr != NULL){
				printf("Bluejack Cruise Ticket\n");
				printf("=============================\n");
				printf("            %s               \n",ptr->ID);
				printf("=============================\n");
				printf("Name	: %s\n",ptr->name);
				printf("Age	: %d\n",ptr->age);
				printf("Class	: %s\n",ptr->ticket);
				printf("Days	: %d\n",ptr->days);
				printf("Price	: $%d\n\n",ptr->price);
				
				ptr = ptr->next;
			}
		}
	}
	else{
		printf("\n\n\tThere is no ticket!\n\n\n");
	}
}
 
void del(char tempID[]){
	int idx = hash(tempID);
	
	if(head[idx]!=NULL){
	if(!head[idx]){
		return;
	}	
	else if(strcmp(head[idx]->ID,tempID)==0){
			struct data *temp = head[idx];
			
			char ans;
			do{
				printf("Delete %s? [Y/N] : ",head[idx]->ID);
				scanf(" %c",&ans);
			}while(ans != 'Y' && ans != 'y' && ans != 'N' && ans !='n');
			
			if(ans =='Y' || ans =='y'){
				printf("Successfully Delete %s\n",head[idx]->ID);
				head[idx] = head[idx]->next;
				temp->next = NULL;
				free(temp);
				temp = NULL;
				
			
				return;
			}
			else{
				return;
			}
		}
		
		else{
			struct data* curr = head[idx];
			
			while(curr->next!=NULL && strcmp(curr->next->ID,tempID)!=0){
				curr = curr->next;
			}
			if(curr->next==NULL){
				printf("Failed to Delete because the Data doesnt exist\n");
				return;
			}
			
			char ans;
			do{
				printf("Delete %s? [Y/N] : ",curr->next->ID);
				scanf(" %c",&ans);
			}while(ans != 'Y' && ans != 'y' && ans != 'N' && ans !='n');
			
			if(ans =='Y' || ans =='y'){
				
				printf("Successfully Delete %s\n",curr->next->ID);
				data *temp = curr->next;	
				curr->next = temp->next;
				
				free(temp);
				temp = NULL;
				
				
				return;
			}
			else{
				return;
			}
		}
	} 
	else{
		printf("Failed to Delete because the Data doesnt exist\n");
	}
}

int main(){
	
	int opt;
	menu:
		system("cls");
	do{
		printf("Bluejack Cruise\n");
		printf("==================\n");
		printf("1. Buy Cruise Ticket\n");
		printf("2. View All Cruise Ticket\n");
		printf("3. Delete Cruise Ticket\n");
		printf("4. Exit\n");
		scanf("%d",&opt);
	}while(opt<1||opt>4);
	
	switch(opt){
		case 1:{
			system("cls");
			char name[100];
			int age, days;
			char tiket[100];
			
			printf("BUY CRUISE TICKET FORM\n");
			printf("=======================\n");
			do{
				printf("Input Your name : ");
				scanf(" %[^\n]",&name);
			}while(strlen(name)<5 || strlen(name)>20);
			
			do{
				printf("Input your age : ");
				scanf("%d",&age);
			}while(age<0 || age>100);
			
			do{
				printf("Input Your ticket class : ");
				scanf(" %[^\n]",&tiket);
			}while(strcmp(tiket,"First Class")!=0 && strcmp(tiket,"Business Class")!=0 && strcmp(tiket,"Economy Class")!=0);
			
			do{
				printf("Input Days : ");
				scanf("%d",&days);
			}while(days<1 || days>15);
			
			char tempID[100];
			char tempangka[100];
			int price;
			
			if(strcmp(tiket,"First Class")==0){
				strcpy(tempID,"FC");
				price = 500 * days;
			}
			else if(strcmp(tiket,"Business Class")==0){
				strcpy(tempID,"BC");
				price = 400 * days;
			}
			else if(strcmp(tiket,"Economy Class")==0){
				strcpy(tempID,"EC");
				price = 300 * days;
			}
			sprintf(tempangka,"%d%d%d",rand()%10,rand()%10,rand()%10);
			strcat(tempID,tempangka);
			
			printf("Successfully Insert\n");
			printf("=======================\n");
			printf("Ticket ID	: %s\n",tempID);
			printf("Total Price	: $%d\n",price);
			insert(tempID,name,age,tiket,days,price);
			
			printf("Press enter to continue . . . ");
			getch();goto menu;
			break;
		}
		case 2:{
			system("cls");
			view();
			printf("Press Enter to Continue...");
			getch();goto menu;
			break;
		}
		case 3:{
			view();
			char delID[100];
			printf("Input product ID to delete : ");
			scanf("%s",delID);
			
			del(delID);
			printf("Press Enter to Continue...");
			getch();goto menu;
			break;
		}
		case 4:{
			system("cls");
			printf("\n\nTHANK YOU\n\n");
			break;
		}
	}
	return 0;
}
