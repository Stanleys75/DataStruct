#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 100
#include<conio.h>

struct data{
	int harga;
	char category[100];
	char namabarang[100];
	int stock;
	char ID[10];
	
	data* next;
} *node[SIZE];

data *createnode(char namabarang[], int harga, int stock, char category[], char ID[]){
	data *newNode = (data*)malloc(sizeof(data));
	strcpy(newNode->namabarang, namabarang);
	strcpy(newNode->category, category);
	strcpy(newNode->ID, ID);
	newNode->harga = harga;
	newNode->stock = stock;
	newNode->next = NULL;
	
	return newNode;
}

int hash(char x[]){
	int key = 0;
	key = (x[0]*(x[3]+x[1]-x[2]));
	
	return key%SIZE;
}

//void view
//void insert
//void delete


int sum;

int main(){
	
	int pilihan;
	// codingan yang disamping saya udah buat sendiri kak, yang ini cuman buat uji coba recordnya aja
	mainmenu:
		
		do{
			
			system("cls");
			
			printf("Mini So\n");
			printf("=======\n");
			printf("1. Add New Product\n");
			printf("2. Delete Product\n");
			printf("3. Exit\n");
			printf("Choose [1-3] > ");
		
			scanf("%d", &pilihan);
			
		} while(pilihan<1 || pilihan>3);
		
		
	switch(pilihan){
		case(1):{
			system("cls");
			
			char namabarang[100];
			int len;
			
			do{
				printf("Insert Product Name [Product name must be more than 5 characters] : ");
				scanf(" %[^\n]", namabarang);
				len = strlen(namabarang);
			} while(len<5);
			
			
			int harga;
			
			do{
				printf("Insert Product Price [1 - 150000 (inclusive)] : ");
				scanf("%d", &harga);
			} while(harga<1 || harga>150000);
			
			int stock;
			
			do{
				printf("Insert Product Stock [More than 0] : ");
				scanf("%d", &stock);
			} while(stock <= 0);
			
			char category[100];
			
			do{
				printf("Insert Product Category [Food | Health | Digital] : ");
				scanf(" %[^\n]",category);
			} while(strcmp(category,"Food") != 0 && strcmp(category,"Health") != 0 && strcmp(category,"Digital") != 0);
			
			char tempID[10];
			char satuan[10] = "00";
			char puluhan[10] = "0";
			char urutan[10];
			
			if(strcmp(category,"Health") == 0){
				strcpy(tempID , "H");
				
				if(sum<10){
					strcat(tempID,satuan);
				} else if(sum>=10 && sum <100){
					strcat(tempID, puluhan);
				}
				
				sprintf(urutan, "%d", sum);
				strcat(tempID,urutan);
				sum += 1;
			} else if(strcmp(category,"Food") == 0){
				strcpy(tempID , "F");
				
				if(sum<10){
					strcat(tempID,satuan);
				} else if(sum>=10 && sum <100){
					strcat(tempID, puluhan);
				}
				
				sprintf(urutan, "%d", sum);
				strcat(tempID,urutan);
				sum += 1;
			} else if(strcmp(category,"Digital") == 0){
				strcpy(tempID , "D");
				
				if(sum<10){
					strcat(tempID,satuan);
				} else if(sum>=10 && sum <100){
					strcat(tempID, puluhan);
				}
				
				sprintf(urutan, "%d", sum);
				strcat(tempID,urutan);
				sum += 1;
			}
			
			insert(namabarang,harga,stock,category,tempID);
			printf("\nSuccessfully Added New Product\n");
			getch();
			goto mainmenu;
			break;
		}
		
		case(2):{
			char delID[100];
			
			
			break;
		}
		case(3):{
			system("cls");
			printf("\n\n\n Have a nice day Good Luck :)\n\n\n")
			break;
		}
	}
		
		// saya recordnya sampe sini aja ya kak, pegel saya ngodingnya ngulang 2 kali ;)
		// makasih kak
	
	
	return 0;
}
