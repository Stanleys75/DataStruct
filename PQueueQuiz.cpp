#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct patient{
	char nama[50];
	int age;
	char condition[20];
	int prio;
	struct patient *prev, *next;
}*head=NULL, *tail=NULL;

void insertPQueue(char nama[], int age, char condition[], int prio)
{
	struct patient *newPatient=(struct patient*)malloc(sizeof(struct patient));
	strcpy(newPatient->nama, nama);
	strcpy(newPatient->condition, condition);
	newPatient->age=age;
	newPatient->prio=prio;
	newPatient->prev=newPatient->next=NULL;
	struct patient *ptr=head;
	if(head==NULL)
	{
		head=tail=newPatient;
	}
	else if(prio<head->prio || (prio==head->prio && age>head->age))
	{
		head->prev=newPatient;
		newPatient->next=head;
		head=newPatient;
	}
	else if(prio>tail->prio || (prio==tail->prio && age<=tail->age))
	{
		tail->next=newPatient;
		newPatient->prev=tail;
		tail=newPatient;
	}
	else
	{
		while(ptr->next!=NULL && ptr->next->prio<=prio)
		{
			if(ptr->next->prio==prio && ptr->next->age<age)
				break;
			ptr=ptr->next;
		}
			
			
		newPatient->prev=ptr;
		newPatient->next=ptr->next;
		ptr->next->prev=newPatient;
		ptr->next=newPatient;
	}
	
}

void servePatient()
{
	struct patient *ptr=head;
	if(ptr!=NULL)
	{
		printf("The next queue:\n");
		printf("Patient Name: %s\n", ptr->nama);
		printf("Age: %d years\n", ptr->age);
		printf("Condition: %s\n", ptr->condition);
	}
	else
	{
		printf("Queue is empty\n");
		return;
	}
	
	if(head==tail)
	{
		free(ptr);
		head=tail=NULL;
	}
	else
	{
		head=head->next;
		head->prev=NULL;
		free(ptr);
	}
	
}

void printData()
{
	struct patient *ptr=head;
	int count=0;
	if(ptr!=NULL)
	{
		printf("||No.|Patient Name        |Age     |Condition           ||\n");
		printf("----------------------------------------------------------\n");
	}
	else
	{
		printf("Queue is empty\n");
	}
	
	while(ptr!=NULL && count<5)
	{
		count++;
		printf("||%-2d.|%-20s|%2d years|%-20s||\n", count, ptr->nama, ptr->age, ptr->condition);
		ptr=ptr->next;
	}
}

int main()
{
	int menu, age, prio;
	char nama[50], condition[20];
	do{
		system("cls");
		printf("SUNIB Foundation COVID-19 Treatment Service\n");
		printf("=*****************************************=\n\n");
		printData();
		puts("");
		printf("1. Insert new patient\n");
		printf("2. Serve patient\n");
		printf("3. Exit\n");
		printf("Input the menu number: ");scanf("%d",&menu); getchar();
		switch(menu)
		{
			case 1:
				printf("Insert new patient name: "); gets(nama);
				printf("Insert new patient age: "); scanf("%d", &age); getchar();
				printf("Insert new patient condition [light|medium|severe]: "); gets(condition);
				if(strcmp(condition, "light")==0)
				{
					prio=3;
					printf("Patient data %s has been inputted to the system as green tag\n", nama);
				}
				else if(strcmp(condition, "medium")==0)
				{
					prio=2;
					printf("Patient data %s has been inputted to the system as yellow tag\n", nama);
				}
				else if(strcmp(condition, "severe")==0)
				{
					prio=1;		
					printf("Patient data %s has been inputted to the system as red tag\n", nama);
				}
				insertPQueue(nama, age, condition, prio);
				getchar();
				break;
			case 2:
				servePatient();
				getchar();
				break;
		}
	}while(menu!=3);
	return 0;
}
