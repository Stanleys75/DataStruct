#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 3
struct nodes{
	int val;
	char nama[20];
	struct nodes *next;
}*head[SIZE]={NULL}, *tail[SIZE]={NULL};

int hashFunction(char nama[])
{
	int len=strlen(nama);
	int count=0;
	for(int i=0; i<len; i++)
	{
		count+=nama[i];
	}
	return count%SIZE;
}

void pushHash(int val, char nama[])
{
	int hashVal=hashFunction(nama);
	struct nodes *newNode=(struct nodes*)malloc(sizeof(struct nodes));
	newNode->next=NULL;
	newNode->val=val;
	strcpy(newNode->nama, nama);
	if(head[hashVal]==NULL)
	{
		head[hashVal]=tail[hashVal]=newNode;
	}
	else
	{
		tail[hashVal]->next=newNode;
		tail[hashVal]=newNode;
	}
}

int searchHash(char nama[])
{
	int hashVal=hashFunction(nama);
	struct nodes *ptr=head[hashVal];
	while(ptr!=NULL)
	{
		if(strcmp(ptr->nama, nama)==0)
			return hashVal;
		ptr=ptr->next;
	}
	return -1;
}

void printHash()
{
	struct nodes *ptr;
	for(int i=0; i<SIZE; i++)
	{
		if(head[i]!=NULL)
		{
			printf("[%2d] ", i);
			ptr=head[i];
			while(ptr!=NULL)
			{
				if(ptr!=tail[i])
					printf("%s(%d)--> ", ptr->nama, ptr->val);
				else
					printf("%s(%d)--> NULL\n", ptr->nama, ptr->val);
				ptr=ptr->next;
			}
		}
	}
}

int main()
{
	int menu, val, res;
	char nama[100];
	
	do{
		system("cls");
		printf("Hash with chaining\n");
		printf("==================\n\n");
		printHash();
		puts("");
		printf("1. Insert new value to hash table\n");
		printf("2. Search value\n");
		printf("3. Exit\n");
		printf("Input menu: ");scanf("%d",&menu);getchar();
		switch(menu)
		{
			case 1:
				printf("Insert your name: "); gets(nama);
				printf("Insert your score: "); scanf("%d", &val);getchar();
				pushHash(val, nama);
				printf("Data has been inserted..\n");
				getchar();
				break;
			case 2:
				printf("Insert name to be searched: "); gets(nama);
				res=searchHash(nama);
				if(res==-1)
					printf("Name %s is not found in the hash table\n", nama);
				else
					printf("Name %s is found at index %d\n", nama, res);
				getchar();
				break;
		}
	}while(menu!=3);
	return 0;
}
