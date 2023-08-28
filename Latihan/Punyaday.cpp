#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 1007

struct Buku{
	char ID[105];
	char judul[55];
	char penulis[30];
	char ISBN[15];
	int halaman;
};Buku* table[SIZE];

int sumInsert = 0;

Buku* createNode(char IDbuku[], char title[], char author[], char numISBN[], int pagenumber){
	Buku* newNode = (Buku*)malloc(sizeof(Buku));
	strcpy(newNode->ID, IDbuku);
	strcpy(newNode->judul, title);
	strcpy(newNode->penulis, author);
	strcpy(newNode->ISBN, numISBN);
	newNode->halaman = pagenumber;
	return newNode;
}

int hash(char IDbuku[]){
	int key = 0;
	for(int i = 0; i < strlen(IDbuku); i++){
		key = key + IDbuku[i];
	}
	return key%SIZE;
}

void viewDelete(int index){
	printf("Book Id: %s\n", table[index]->ID);
	printf("Book Title: %s\n", table[index]->judul);
	printf("Book Author: %s\n", table[index]->penulis);
	printf("Book ISBN: %s\n", table[index]->ISBN);
	printf("Page Number: %d\n", table[index]->halaman);
}

void deletes(char IDbuku[]){
	int index = hash(IDbuku);
	
	if(table[index] != NULL && strcmp(table[index]->ID, IDbuku) == 0){
		viewDelete(index);
		char jawaban = ' ';
		do{
			printf("Are you sure [y/n]? ");
			scanf(" %c", &jawaban);
		}while(jawaban != 'y' && jawaban != 'n');
		if(jawaban == 'y'){
			free(table[index]);
			table[index] = NULL;
			printf("Delete success !\n");
			getchar();
			return;
		}else{
			return;
		}
	}else{
		int baseIdx = index;
		do{
			if(table[index] != NULL && strcmp(table[index]->ID, IDbuku) == 0){
				viewDelete(index);
				char jawaban = ' ';
				do{
					printf("Are you sure [y/n]? ");
					scanf(" %c", &jawaban);
				}while(jawaban != 'y' && jawaban != 'n');
				if(jawaban == 'y'){
					free(table[index]);
					table[index] = NULL;
					printf("Delete success !\n");
					getchar();
					return;
				}else{
					return;
				}			
			}
			index = (index + 1) % SIZE;
		}while(index != baseIdx);
		printf("Book not found. \n");
		getchar();
	}
}

void inserts(char IDbuku[], char title[], char author[], char numISBN[], int pagenumber){
	Buku* toInsert = createNode(IDbuku, title, author, numISBN, pagenumber);
	int idx = hash(IDbuku);
	
	if(table[idx] == NULL){
		table[idx] = toInsert;
	}else{
		int baseIdx = idx;
		while(table[idx] != NULL){
			idx = (idx + 1) % SIZE;
			if(idx = baseIdx){
				break;
			}
		}
		if(idx == baseIdx){
			printf("Book is already full !\n");
			
		}else if(table[idx] == NULL){
			table[idx] = toInsert;
		}
	}
}

void view(){
	int b = 0;
	for(int i = 0; i < SIZE; i++){
		if(table[i] == NULL){
			b = b + 1;
		}
	}
	
	if(b != SIZE){
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("| Book ID                     | Book Title                                      | Book Author                   | ISBN                    | Page Number        |\n");
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		for(int i = 0;  i < SIZE; i++){
			if(table[i] == NULL){
				continue;
			}else{
				printf("| %s  %27s %48s  %35s  %16d                 |\n", table[i]->ID, table[i]->judul, table[i]->penulis, table[i]->ISBN, table[i]->halaman);
				printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			}
			puts("");
		}
		puts("");
	}else{
		printf("\nThere is no book(s)\n");
	}
}

bool cekJudul(char valJudul[]){
	
	for(int i = 0; i < SIZE; i++){
		if(strcmp(table[i]->judul, valJudul) == 0){
			return false;
			break;
		}
	}
	return true;
}

bool cekPenulis(char valPenulis[]){
	char validPenulis[5];
	
	for(int i = 0; i < 3; i++){
		validPenulis[i] = valPenulis[i];
	}if(strcmp(validPenulis, "Mr.") == 0){
		return true;
	}
	
	for(int i = 0; i < 4; i++){
		validPenulis[i] = valPenulis[i];
	}if(strcmp(validPenulis, "Mrs.") == 0){
		return true;
	}
	
	return false;
}

bool cekISBN(char valISBN[]){
	for(int  i = 0; i < strlen(valISBN); i++){
		if(valISBN[i] < 48 || valISBN[i] > 57){
			return false;
		}
	}
	return true;
}

int main(){
	

	mainmenu:
		int nomor;
		do{
			for(int i = 0; i < 30; i++){
				printf("\n");
			}
			printf("Bluejack Library\n");
			printf("=================\n");
			printf("1. View Book\n");
			printf("2. Insert Book\n");
			printf("3. Remove Book\n");
			printf("4. Exit\n");
			printf(">>");
			scanf("%d", &nomor);
		}while(1 > nomor || 4 < nomor);
		
	switch(nomor)
	{
		case(1):
			view();
			printf("\n");
			printf("Press Enter to continue ...");getchar();
			getchar(); goto mainmenu;
			break;
		
		case(2):
			{
			//Judul
			char tempJudul[55];
			bool validJudul = false;
			do{
				printf("Input book title[5-50][unique]: ");
				scanf(" %[^\n]", &tempJudul);
			}while(strlen(tempJudul) < 5 || strlen(tempJudul) > 50);
			
			//Penulis
			char tempPenulis[30];
			bool validPenulis = false;
			do{
				printf("Input author name[3-25][Mr. |Mrs. ]: ");
				scanf(" %[^\n]", &tempPenulis);
				validPenulis = cekPenulis(tempPenulis);
			}while(validPenulis == false || strlen(tempPenulis) < 3 || strlen(tempPenulis) > 25);
			
			//ISBN
			char tempISBN[15];
			bool validISBN = false;
			do{
				printf("Input ISBN[10-13][numeric]: ");
				scanf(" %[^\n]", &tempISBN);
				validISBN = cekISBN(tempISBN);
			}while(validISBN == false || strlen(tempISBN) < 10 || strlen(tempISBN) > 13);
			
			//Halaman
			int tempHalaman = 0;
			do{
				printf("Input page number[>= 16]: ");
				scanf("%d", &tempHalaman);
				getchar();
			}while(tempHalaman < 16);
			
			
			//Book ID
			sumInsert = sumInsert + 1;
			char tempID[101];
			char satuan[10] = "B0000";
			char puluhan[10] = "B000";
			char ratusan[10] = "B00";
			char ratusanribu[10] = "B0";
			char puluhanribu[10] = "B";
			char strip = '-';
			char urutan[10];
			
			if(sumInsert < 10){
				strcpy(tempID, satuan);
			}else if(sumInsert >= 10 && sumInsert < 100){
				strcpy(tempID, puluhan);
			}else if(sumInsert >= 100 && sumInsert < 1000){
				strcpy(tempID, ratusan);
			}else if(sumInsert >= 1000 && sumInsert < 10000){
				strcpy(tempID, ratusanribu);
			}else{
				strcpy(tempID, puluhanribu);
			}
			
			sprintf(urutan, "%d", sumInsert);
			strcat(tempID, urutan);
			strncat(tempID, &strip, 1);
			strcat(tempID, tempISBN);
			strncat(tempID, &strip, 1);
			
			char truePenulis[5];
			for(int i = 0; i < strlen(tempPenulis); i++){
				if(tempPenulis[i-1] == ' '){
					if(tempPenulis[i] >= 'a' && tempPenulis[i] <= 'z'){
						truePenulis[0] = tempPenulis[i] - 32;
					}
					strncat(tempID, &truePenulis[0], 1);
					break;
				}
			}
			
			char trueJudul[5];
			if(tempJudul[0] >= 'a' && tempJudul[0] <= 'z'){
				trueJudul[0] = tempJudul[0] - 32;
			}
			strncat(tempID, &trueJudul[0], 1);
			
			inserts(tempID, tempJudul, tempPenulis, tempISBN, tempHalaman);
			
			printf("\nInsert success !\n");
			
			printf("\n");
			printf("Press Enter to continue ...");
			getchar(); goto mainmenu;
			break;
			}
		
		case(3):
			//Delete
			char deleteID[105];
			printf("Input book id to delete: ");
			scanf(" %[^\n]", &deleteID);
			
			deletes(deleteID);
			printf("Press Enter to continue ...");
			getchar(); goto mainmenu;
			break;
			
		case(4):
			break;	
	}	
		
	return 0;

}
