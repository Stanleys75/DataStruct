#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 100
#include<conio.h>

struct data{
	char namabarang[100];
	char category[100];
	char ID[10];
	int harga;
	int stock;
	
	data *next;
} *node[SIZE], *tail[SIZE];

data *createNode(char namabarang[], int harga, int stock, char category[], char ID[]){
	data *newNode = (data*)malloc(sizeof(data));
	strcpy(newNode->namabarang, namabarang);
	strcpy(newNode->category, category);
	strcpy(newNode->ID, ID);
	newNode->harga = harga;
	newNode->stock = stock;
	newNode->next = NULL;
	
	return newNode;
}

int hash(char X[]){
	int key=0;
	key = X[0]*(X[3] + X[1] - X[2]);
	
	return key%SIZE;
}

void view(){
int tot = 0;

	for(int i = 0; i < SIZE; i++){
		if(node[i] == NULL){
			tot = tot + 1;
		}
	}
	
	if(tot!=SIZE){
		for(int i=0; i<SIZE; i++){
			struct data* temp = node[i];
			while(temp!=NULL){
				printf("Product ID: %s\n",temp->ID);
				printf("==============\n");
				printf("Product Name: %s\n",temp->namabarang);
				printf("Product Price: %d\n",temp->harga);
				printf("Product Stock: %d\n",temp->stock);
				if(strcmp(temp->category,"Digital")==0){
					printf("Expired Date: -\n\n");
				}
				else{
					printf("Expired Date: %.2d/%.2d/%.2d\n\n", rand()%30+1, rand()%12+1, rand()%6+20);
				}
				
				temp = temp->next;
			}
		}
	}
	else{
		printf("No Product Yet");
	}
}

void insert(char namabarang[], int harga, int stock,char category[], char tempID[] ){
	data *insertData = createNode(namabarang,harga,stock,category,tempID);
	
	int idx = hash(tempID);
	
	if(node[idx]==NULL){
		node[idx] = tail[idx]= insertData;
	} else {
		tail[idx] -> next = insertData;
		tail[idx] = insertData;
	}
}

void del(char ID[]){
	int idx = hash(ID);
	
	if(node[idx] != NULL){
		
		if(!node[idx]){
			return;
		
		} else if(strcmp(node[idx]->ID,ID) == 0){
			struct data* temp = node[idx];
			
			char answer;
			do{
				printf("Sure to delete %s [Y/N] (Case Incensitive)? : ",node[idx]->ID);
				scanf(" %c",&answer);
			}while(answer!='Y' && answer!='y' && answer!='N' && answer!='n');
		
			if(answer == 'Y' || answer == 'y'){
				node[idx] = node[idx]->next;
				temp -> next = NULL;
				free(temp);
				temp = NULL;
				printf("Successfully Delete product\n");
				getch();
				return;
			}
			else{
				return;
			}

		}else{
			struct data* curr = node[idx];
			
			while(curr->next != NULL && strcmp(curr->next->ID,ID) != 0){
				curr = curr->next;
			}
		
			if(curr->next==NULL){
				printf("No data found. \n");
				getch();
				return;
			}
			
			char answer;
			do{
				printf("Sure to delete %s [Y/N] (Case Incensitive)? : ",curr->next->ID);
				scanf(" %c",&answer);
			}while(answer!='Y' && answer!='y' && answer!='N' && answer!='n');
		
			if(answer == 'Y' || answer == 'y'){
				data* temp = curr->next;
				curr->next= temp->next;	
			
				free(temp);
				temp = NULL;
				printf("Successfully Delete product\n");
				getch();
				return;
			}
			else{
				return;
			}
		}
		
	}else{
	
		printf("No data found. \n");
		getch();
	}		
}


int sum = 1;

int main(){	
	int pilihan;
		
	mainmenu:	
		do{	
			system("cls");
			view();
			printf("\n\n");
			
			printf("Mini So\n");
			printf("========\n");
			printf("1. Add New Product\n");
			printf("2. Delete Product\n");
			printf("3. Exit\n");
			printf("Choose [1-3] > ");	
			
			scanf("%d", &pilihan);
			
		} while(pilihan < 1 || pilihan > 3);
		
	switch(pilihan){
		case(1):{
			system("cls");
			char NamaBarang[100];

			int len;
		
			do{
				printf("Insert Product Name [Product name must be more than 5 characters]: ");
				scanf(" %[^\n]", NamaBarang); 
				len = strlen(NamaBarang);
			
			}while(len < 5);
	
			
		
			int Harga;	
			do{
			printf("Insert Product Price [1 - 150000 (inclusive)]: ");
	
			scanf("%d",&Harga);	
			
			}while((Harga < 1 ) || (Harga > 150000));
		
		
			
			int Stock;
		
			do{
				printf("Insert Product Stock [more than 0]: ");
				scanf("%d", &Stock);
			
			}while(Stock <= 0);
				
				
			char category[10];
			do{
				printf("Insert Product Category [Health | Food | Digital] (case sensitive) : ");
				scanf(" %[^\n]", category); getchar();
				
			}while(strcmp(category,"Health")!=0 && strcmp(category,"Digital")!=0 && strcmp(category,"Food")!=0);
			
			
			
			char tempID[10];
			char satuan[10] = "00";
			char puluhan[10] = "0";
			char urutan[10];

			if(strcmp(category,"Health")==0){
            	strcpy(tempID,"H");
            	if(sum<10){
            		strcat(tempID,satuan);
				}
				else if(sum>=10 && sum<100){
					strcat(tempID,puluhan);
				}
					sprintf(urutan,"%d",sum);
					strcat(tempID,urutan);
					sum = sum+1;
			}
			else if(strcmp(category,"Food")==0){
				strcpy(tempID,"F");
            	if(sum<10){
            		strcat(tempID,satuan);
				}
				else if(sum>=10 && sum<100){
					strcat(tempID,puluhan);
				}
					sprintf(urutan,"%d",sum);
					strcat(tempID,urutan);
					sum = sum+1;
			}
			else if(strcmp(category,"Digital")==0){
			strcpy(tempID,"D");
            	if(sum<10){
            		strcat(tempID,satuan);
				}
				else if(sum>=10 && sum<100){
					strcat(tempID,puluhan);
				}
					sprintf(urutan,"%d",sum);
					strcat(tempID,urutan);
					sum = sum+1;
			}
			insert(NamaBarang,Harga,Stock,category,tempID);
			printf("\n");
			printf("Successfully added new product\n");
			getch(); goto mainmenu;
			
			
			
			break;
		}
		case(2):{
			char delID[100];
    		printf("Input Product ID to delete: ");
    		scanf(" %[^\n]",delID);
    		
    		del(delID);
    		printf("Press any to continue...");
    		getch(); goto mainmenu;
			
			break;
		}
			
			
		case(3):{
			system("cls");
    		printf("\n\n\nHave a nice day, Goodluck :)\n\n\n");
			break;
		}
			
		
	}
	
	
	return 0;
}
