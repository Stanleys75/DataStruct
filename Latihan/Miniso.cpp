#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 100

struct data{
	char namabarang[101];
	char category[10];
	int harga;
	int stock;
	
	data *next;
	
} *head[SIZE];

data *createNode(char namabarang[],char category[],int harga,int stock){
	data *newNode = (data*)malloc(sizeof(data));
	strcpy(newNode->namabarang, namabarang);
	strcpy(newNode->category, category);
	newNode->harga = harga;
	newNode->stock = stock;
	newNode->next = NULL;
	
	return newNode;
}

int hash(char ID[]){
	int key = 0;
	
	key = (ID[0]*(ID[3] + ID[1] - ID[2]));
	
	return key%SIZE;
}

void insert(char namabarang[],int harga,int stock,char category[], char ID[]){
	data* newNode = createNode(namabarang,category,harga,stock);
	
	int idx = hash(ID);
	
	if(head[idx] == NULL){
		head[idx] = newNode;
	} else {
		int baseIdx = idx;
		while(head[idx] != NULL){
			idx = (idx + 1) % SIZE;
			if(idx = baseIdx){
				break;
			}
		}
		if(idx == baseIdx){
			printf("Data is already full !\n");
			
		}else if(head[idx] == NULL){
			head[idx] = newNode;
		}
	}
	
	
}





//int numID = 0;
//void productID(char category[]){
//
//	char ID[4];
//	
//	if(category[0] == 'H'){
//		ID[0]=category[0];
//		numID += 1;
//		printf("%c%.3d\n",ID[0],numID);
//	}
//	if(category[0] == 'F'){
//		ID[0]=category[0];
//		numID += 1;
//		printf("%c%.3d\n",ID[0],numID);
//	}
//	if(category[0] == 'D'){
//		ID[0]=category[0];
//		numID += 1;
//		printf("%c%.3d\n",ID[0],numID);
//	}
//}

void List(){
	
	int sum = 0;
	
	for(int i=0; i<100; i++){
		struct data* temp = head[i];
		if(temp != NULL){
			sum += 1;
		}
	}
	
	if(sum == 0){
		printf("No Product Yet\n");
	}
	
	for(int i=0; i<100; i++){
		struct data* temp = head[i];
		while(temp != NULL){
			printf("Product ID : %c%d");
			printf("=====================");
			printf("Product Name : %s");
			printf("Product Price : %d");
			printf("Product Stock : %d");
			printf("Expired Date : %.2d/%.2d/%.2d", rand()%30+1,rand()%12+1, rand()% 6 + 20);
			temp = temp->next;
		}
	}
	
	sum = 0;
}




bool cekCategory(char valcategory[]){
	char validcategory[5];
	
	for(int i = 0; i < 6; i++){
		validcategory[i] = valcategory[i];
	}if(strcmp(validcategory, "Health") == 0){
		return true;
	}
	
	for(int i = 0; i < 4; i++){
		validcategory[i] = valcategory[i];
	}if(strcmp(validcategory, "Food") == 0){
		return true;
	}
	
	for(int i = 0; i < 7; i++){
		validcategory[i] = valcategory[i];
	}if(strcmp(validcategory, "Digital") == 0){
		return true;
	}
	
	return false;
}

int main(){
	int pilihan;
	
	
	mainmenu:
		do{
			List();printf("\n");
			printf("MINI SO\n");
			printf("========\n");
			printf("1. Add New Product\n");
			printf("2. Delete Product\n");
			printf("3. Exit\n");
			printf("Choose [1-3] > ");	
			
			scanf("%d", &pilihan);
			
		} while(pilihan < 1|| pilihan > 3);
		
		
	switch(pilihan){
		
		case(1): {
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
				
		
			bool validasi = false;
			char Category[10];
			do{
				printf("Insert Product Category [Health | Food | Digital] (case sensitive) : ");
				scanf(" %[^\n]", Category); getchar();
				validasi = cekCategory(Category);
			}while(validasi == false);
		
			char ID[5];
			int sumID;
			sumID += 1;
			char angka[1];
		
			angka[0] = sumID;
		
			char satuan[10] = "00";
			char puluhan[10] = "0";
			char ratusan[10] = "";
		
			if(Category[0] == 'H'){
				ID[0]=Category[0];
				if(sumID < 10){
					strcpy(ID,satuan);
					strcpy(ID,angka);
				} else if(sumID >= 10 && sumID < 100){
					strcpy(ID,puluhan);
					strcpy(ID,angka);
				
				} else if(sumID >= 100 && sumID < 1000){
					strcpy(ID,angka);
				}
			}
		
			else	if(Category[0] == 'F'){
				ID[0]=Category[0];
				if(sumID < 10){
					strcpy(ID,satuan);
					strcpy(ID,angka);
				} else if(sumID >= 10 && sumID < 100){
					strcpy(ID,puluhan);
					strcpy(ID,angka);
				} else if(sumID >= 100 && sumID < 1000){
					strcpy(ID,angka);
				}
			}
			else if(Category[0] == 'D'){
				ID[0]=Category[0];
				if(sumID < 10){
					strcpy(ID,satuan);
					strcpy(ID,angka);
				} else if(sumID >= 10 && sumID < 100){
					strcpy(ID,puluhan);
					strcpy(ID,angka);
				} else if(sumID >= 100 && sumID < 1000){
					strcpy(ID,angka);
				}
			}	
	
		
		
			
		
			printf("Successfully Added New Product");
			system("cls");
			goto mainmenu;	
			insert(NamaBarang,Harga,Stock,Category,ID);
			
			break;
		}
			
			
		case(2):
		{
			
			break;
		}	
		
		case(3):{
			exit(0);
			getchar();getchar();
			break;
		}
	}
		
		
	
	return 0;
}
