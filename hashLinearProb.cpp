#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define size 10
struct data{
	char name[20];
}*dt[11]={NULL};

int hashFunction(char name[])
{
	int len=strlen(name);
	int sum=0;
	for(int i=0; i<len; i++)
	{
		sum+=name[i];
	}
	sum=sum%size;
	return sum;
}

void insertHash(char name[])
{
	int hashVal=hashFunction(name);
	struct data *newHash=(struct data*)malloc(sizeof(struct data));
	strcpy(newHash->name, name);
	int start=hashVal+1;
	//printf("hashVal: %d\n", hashVal);
	if(dt[hashVal]==NULL)
	{
		dt[hashVal]=newHash;
		printf("Name %s has been added into hashtable at index %d\n", name, hashVal);
	}
	else
	{
		while(start!=hashVal)
		{
			if(dt[start]==NULL)
			{
				dt[start]=newHash;
				printf("Name %s has been added into hashtable at index %d\n", name, start);
				return;
			}
			start++;
			start%=size;
				
		}
		printf("Hash table is full\n");
	}
}

void deleteHash(char name[])
{
	int hashVal=hashFunction(name);
	int start=hashVal+1;

	if(dt[hashVal]==NULL || strcmp(name, dt[hashVal]->name)==0)
	{
		while(start!=hashVal)
		{
			if(strcmp(name, dt[start]->name)==0)
			{
				free(dt[start]);
				dt[start]=NULL;
				return;
			}
			start++;
			start%=size;
		}
		printf("Data %s is not found in the hash table\n", name);
	}
	else if(strcmp(name, dt[hashVal]->name)==0)
	{
		free(dt[hashVal]);
		dt[hashVal]=NULL;
	}
}

void searchHash(char name[])
{
	int hashVal=hashFunction(name);
	int start=hashVal+1;
	
	if(dt[hashVal]==NULL || strcmp(name, dt[hashVal]->name)==0)
	{
		while(start!=hashVal)
		{
			if(dt[start]!=NULL && strcmp(name, dt[start]->name)==0)
			{
				printf("Name %s is found at index %d\n", name, start);
				return;
			}
			start++;
			start%=size;
		}
		printf("Data %s is not found in the hash table\n", name);
	}
	else if(strcmp(name, dt[hashVal]->name)==0)
	{
		printf("Name %s is found at index %d\n", name, hashVal);
	}
}

void printHashTable()
{
	for(int i=0; i<size; i++)
	{
		if(dt[i]!=NULL)
			printf("[%2d]%-s\n", i, dt[i]->name);
	}
	puts("");
}

int main()
{
	int menu;
	char name[20];
	do{
		system("cls");
		printf("Linear Probing Hash Table\n");
		printf("=========================\n\n");
		printHashTable();
		printf("1. Insert hash\n");
		printf("2. Search hash\n");
		printf("3. Delete hash\n");
		printf("4. Exit\n");
		printf("Insert menu: "); scanf("%d", &menu); getchar();
		switch(menu)
		{
			case 1:
				printf("Insert new data: "); gets(name);
				insertHash(name);
				getchar();
				break;
			case 2:
				printf("Insert data to be searched: "); gets(name);
				searchHash(name);
				getchar();
				break;
			case 3:
				printf("Insert data to be deleted: "); gets(name);
				deleteHash(name);
				getchar();
				break;
		}
	}while(menu!=4);
	return 0;
}
