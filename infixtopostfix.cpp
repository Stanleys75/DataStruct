#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
	char val;
	struct node *next;
}*head=NULL, *tail=NULL;

int getPrio(char a)
{
	if(a=='(')
		return 0;
	else if(a=='+' || a=='-')
		return 1;
	else if(a=='*' || a=='/')
		return 2;
}
void pushHead(char val)
{
	struct node *newNode=(struct node*)malloc(sizeof(struct node));
	newNode->val=val;
	newNode->next=NULL;
	
	if(head==NULL)
		head=tail=newNode;
	else
	{
		newNode->next=head;
		head=newNode;
	}
}

void popHead()
{
	if(head->val!='(')
		printf("%c", head->val);	
	struct node *ptr=head;
	if(head==tail)
		head=tail=NULL;
	else{
		head=head->next;
	}
	free(ptr);
}


int main()
{
	char string[50]="A+B*(C-D)/E";
	int len=strlen(string);
	struct node *ptr_run=head;
	for(int i=0; i<len; i++)
	{
		if(string[i]=='(')
			pushHead(string[i]);
		else if(string[i]==')')
		{
			while(head->val!='(')
			{
				popHead();	
			}
			popHead();
		}
		else if(string[i]=='+' ||string[i]=='-' ||string[i]=='*' ||string[i]=='/' ||string[i]=='^')
		{
			
			if(head==NULL)//kalau stacknya kosong
				pushHead(string[i]);
			else
			{
					while(head!=NULL && getPrio(head->val)>=getPrio(string[i]))
					{
						popHead();
					}
					pushHead(string[i]);
			}	
		}
		else // string yang dibaca merupakan operand
		{
			printf("%c", string[i]);
		}
	}
	while(head!=NULL)
	{
		popHead();
	}
	
	return 0;
}
