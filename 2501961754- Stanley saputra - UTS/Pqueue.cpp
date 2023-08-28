#include<stdio.h>
#include<stdlib.h> 
#include<string.h>

struct data{
    int umur;
    char nama[30];
	char kondisi[100];
    data *next;
}*head, *tail; 

data *createnode(int umur, char nama[], char kondisi[]){
	data *newnode = (data*)malloc(sizeof(data));
	
	strcpy(newnode->nama,nama);
	strcpy(newnode->kondisi,kondisi);
	newnode->umur = umur;
	newnode->next = NULL;
	
	return newnode;
}

void pushHead(char nama[],int umur, char kondisi[]){
	
	data *newnode = createnode(umur,nama,kondisi);
	
	if(!head){
		head = tail = newnode;
	}
	else {
		newnode->next = head;
		head = newnode;
	}
}

void pushTail(char nama[],int umur, char kondisi[]){
	
	data *newnode = createnode(umur,nama,kondisi);
	
	if(!head){
		head = tail = newnode;
	}
	else {
		tail->next = newnode;
		tail = newnode  ;
	}
}

void pushMid(char nama[],int umur, char kondisi[]){
	
	data *newnode = createnode(umur,nama,kondisi);
	
	if(!head){
		head = tail = newnode;
	}
	else {
		if(strcmp(newnode->kondisi,"severe")==0){
			pushHead(nama,umur,kondisi);
		} else if(strcmp(newnode->kondisi,"light")==0){
			pushTail(nama,umur,kondisi);
			
		} else{
			data* curr = head;
			while (curr->next != NULL && strcmp(curr->next->kondisi,"severe")== 0){
				curr = curr->next;
			}
			
			newnode -> next = curr;
			curr = newnode;
		}
	}
}
int nomor = 1;
void view(){
	
	if(head==NULL){
		printf("Queue is empty\n\n");
	} else {
		printf("No    Patient Name        Age      Condition\n");
	}
	struct data *curr = head;
	
	while(curr!= NULL){
		
		printf("%d         %s             %d           %s\n\n",  nomor,curr->nama,curr->umur,curr->kondisi);
		
	curr = curr->next;
	nomor++;
	}
	
	
	nomor = 1;
}


void popHead(){
	
	if(!head){
		return;
	}
	else{	
		data* temp = head;
		
		if(head==tail){
			head = tail = NULL;
		}
		else{
			head = head->next;
		}
		
		free(temp);
	}
}


int main(){
	
	mainmenu:
		printf("SUNIB Foundation COVID-19 Treatment Service\n\n\n");
		view();
		printf("1. Insert New Patient\n");
		printf("2. Serve Patient\n");
		printf("3. Exit\n");
		int pilihan;
		printf("Input the menu number: ");
		scanf("%d", &pilihan);
		
	switch(pilihan){
		
		case(1):{
		
			char nama[200];
			printf("Input New Patient Name: ");
			scanf(" %[^\n]",nama);	
			int umur;
			printf("Input New Patient Age: ");
			scanf("%d", &umur);
			char kondisi[200];
			do{
				printf("Input New Patient Condition [light|medium|severe]: ");
				
				scanf(" %[^\n]", kondisi);
			} while (strcmp(kondisi,"light")!=0 && strcmp(kondisi,"medium")!=0 && strcmp(kondisi,"severe")!=0);
			
			if(strcmp(kondisi,"light")==0){
				printf("patient data seria has been inputted to the system as green tag\n");
			} else if(strcmp(kondisi,"medium")==0){
				printf("patient data seria has been inputted to the system as yellow tag\n");
			}if(strcmp(kondisi,"severe")==0){
				printf("patient data seria has been inputted to the system as red tag\n");
			}
			
			pushMid(nama,umur,kondisi);
			goto mainmenu;
			break;
		}
		case(2):{
			printf("The next queue: \n");
			printf("Patient Name: %s\n", head->nama);
			printf("Age : %d\n", head->umur);
			printf("Condition %s\n", head->kondisi);
			popHead();
			goto mainmenu;
			break;
			
			
			
		}
		case(3):{
			break;
		}
		
	}
	
	
		
		
		
		
		
		
	
}
