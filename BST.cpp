#include<stdio.h>
#include<stdlib.h>

struct node{
	int val;
	int count;
	struct node *left, *right;
};

struct node *insertNewNode(struct node *curr, int val)
{
	if(curr==NULL)
	{
		struct node *newNode=(struct node*)malloc(sizeof(struct node));
		newNode->val=val;
		newNode->left=NULL;
		newNode->right=NULL;
		newNode->count=1;
		curr=newNode;
	}
	else if(val<curr->val)
	{
		curr->left=insertNewNode(curr->left, val);
	}
	else if(val>curr->val)
	{
		curr->right=insertNewNode(curr->right, val);
	}
	else
	{
		curr->count++;
	}
	return curr;
}

struct node *findLeftRightMost(struct node *curr)
{
	while(curr->right!=NULL)
		curr=curr->right;
	return curr;
}

struct node *deleteNode(struct node *curr, int val)
{
	if(curr==NULL)
	{
		printf("Value %d is not found in the tree\n", val);
	}
	else
	{
		if(val<curr->val)
		{
			curr->left=deleteNode(curr->left, val);
		}
		else if(val>curr->val)
		{
			curr->right=deleteNode(curr->right, val);
		}
		else if(val==curr->val && curr->count>1)
		{
			curr->count--;
		}
		else
		{
			if(curr->left==NULL && curr->right==NULL)
			{
				free(curr);
				curr=NULL;
			}
			else if(curr->left==NULL)
			{
				struct node *temp=curr;
				curr=curr->right;
				free(temp);
			}
			else if(curr->right==NULL)
			{
				struct node *temp=curr;
				curr=curr->left;
				free(temp);
			}
			else
			{
				struct node *temp=findLeftRightMost(curr->left);
				curr->val=temp->val;
				curr->count=temp->count;
				curr->left=deleteNode(curr->left, temp->val);
			}
		}
	}
	return curr;
}

void search(struct node *curr, int val)
{
	if(curr==NULL)
		printf("Value %d is not found in the tree\n", val);
	else if(val<curr->val)
		search(curr->left, val);
	else if(val>curr->val)
		search(curr->right, val);
	else
	{
		if(curr->count>1)
			printf("There are %d node %d found in the tree\n", curr->count, val);
		else
			printf("There is only %d node %d found in the tree\n", curr->count, val);	
	}
}

void inOrder(struct node *curr)
{
	if(curr!=NULL)
	{
		inOrder(curr->left);
		printf("%d : %d\n", curr->val, curr->count);
		inOrder(curr->right);
	}
}

int main()
{
	struct node *root=NULL;
	int val;
	int menu;
	do{
		system("cls");
		printf("Binary Search Tree\n");
		printf("===================\n\n");
		inOrder(root);
		puts("");
		printf("1. Insert new node\n");
		printf("2. Search node\n");
		printf("3. Delete node\n");
		printf("4. Exit\n");
		printf("Insert menu: "); scanf("%d", &menu); getchar();
		switch(menu)
		{
			case 1:
				printf("Insert new value: "); scanf("%d", &val); getchar();
				root=insertNewNode(root, val);
				printf("New node has been added..\n");
				getchar();
				break;
			case 2:
				printf("Insert value to be searched: "); scanf("%d", &val); getchar();
				search(root, val);
				getchar();
				break;
			case 3:
				printf("Insert value to be deleted: "); scanf("%d", &val); getchar();
				root=deleteNode(root, val);
				getchar();
				break;
		}
	}while(menu!=4);
	return 0;
}
