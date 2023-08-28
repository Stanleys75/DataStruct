#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

struct data{
	int number;
	int height;
	
	struct data* left;
	struct data* right;
};

int max(int a, int b){
    if(a>b) {
    	return a;	
	}
    return b;
}

int getHeight(struct data* temp){
    if(temp == NULL){
        return 0;
    }
	else{
        return temp->height;
    }
}

int getBalance(struct data* temp){
    if(temp == NULL){
        return 0;
    }
	else{
        return getHeight(temp->left)-getHeight(temp->right);
    }
}

data* leftRotate(data* temp){
    data* x = temp->right;
    data* y = x->left;

    x->left = temp;
    temp->right = y;

    temp->height = max(getHeight(temp->left),getHeight(temp->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

data* rightRotate(data* temp){
    data* x = temp->left;
    data* y = x->right;

    x->right = temp;
    temp->left = y;

    temp->height = max(getHeight(temp->left),getHeight(temp->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

struct data* create(int number){
	data* curr = (data*)malloc(sizeof(data));
	
	curr->number = number;
	curr->height = 1;
	curr->left = curr->right = NULL;
	
	return curr;
}

struct data* insert(struct data *root,int number){
	if(root == NULL){
		return create(number);
	}
	else if(number < root->number){
		root->left=insert(root->left,number);
	}
	else if(number > root->number){
		root->right=insert(root->right,number);
	}
	
	root->height = max(getHeight(root->left),getHeight(root->right))+1;
	int balance = getBalance(root);
	
	if(balance>1 && number < root->left->number){
		root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if(balance > 1 && number > root->left->number){
        return rightRotate(root);
    }

	if(balance < -1 && number < root->right->number){
		root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    if(balance < -1 && number > root->right->number){
    	
        return leftRotate(root);
    }

    return root;
}

void viewInOrder(data *root){
    if(root!=NULL){
        viewInOrder(root->left);
        printf("%d ",root->number);
        viewInOrder(root->right);
        
    }
}

void viewPreOrder(data *root){
    if(root!=NULL){
        printf("%d ",root->number);
        viewPreOrder(root->left);
        viewPreOrder(root->right);
        
    }
}

void viewPostOrder(data *root){
    if(root!=NULL){
        viewPostOrder(root->left);
        viewPostOrder(root->right);
        printf("%d ",root->number);
        
    }
}

data* deletion(data* root, int number){
	if(root==NULL){
		return NULL;
	}
	if(number < root->number){
		root->left=deletion(root->left,number);
	}
	else if(number > root->number){
		root->right=deletion(root->right,number);
	}
	else{
		if(root->left == NULL && root->right == NULL){
			free(root);
			root = NULL;
			return root;
		} 
		else if(root->left != NULL && root->right == NULL){
			data* temp = root->left;
			*root = *temp;
			free(temp);
			root = NULL;	
		}
		else if(root->left != NULL && root->right != NULL){
			data* temp = root->left;
			while(temp->right != NULL){ 
				temp = temp->right;
			}
			root->number=temp->number;
			
			root->left = deletion(root->left,temp->number);
		}
	}
	
	root->height = max(getHeight(root->left),getHeight(root->right))+1;
	int balance = getBalance(root);	
	
	if(root == NULL){
		return root;
	}
	
	if(balance>1 && getBalance(root->left)>=0){
        return rightRotate(root);
    }

    else if(balance > 1 && getBalance(root->left)<0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
	
	else if(balance < -1 && getBalance(root->right)<=0){
        return leftRotate(root);
    }
	
	else if(balance < -1 && getBalance(root->right)>0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

data *search (data *root, int number){
    if(!root){
        return NULL;
    }
    else if(number < root->number){
        search(root->left,number);
    } 
	else if(number > root->number){
        search(root->right,number);
    } else {
    	return root;
	}
    
}

int main(){
	data* root = NULL;
	int pilihan;
	
	root = insert(root, 6);
	root = insert(root, 27);
	root = insert(root, 19);
	root = insert(root, 11);
	root = insert(root, 36);
	root = insert(root, 14);
	root = insert(root, 81);
	root = insert(root, 63);
	root = insert(root, 75);
	
	mainmenu:
	system("cls");
	do{
		printf("  AOL Data Structure  \n");
		printf("    Stanley saputra   \n");
		printf("      2501961754    \n");
		printf("=======================\n");
		printf("1. Insertion\n");
		printf("2. Deletion\n");
		printf("3. Traversal\n");
		printf("4. Exit\nChoose: ");
		scanf("%d",&pilihan);
	}while(pilihan<1||pilihan>4);
	
	switch(pilihan){
		case (1):{
			int number;
			
			printf("\nInsert: ");
			scanf("%d",&number);
			
			printf("\nSuccessfully Inserted!");
			root = insert(root,number);
			
			printf("\nPress enter to continue...");
			getch(); 
			goto mainmenu;
			break;
		}
		case (2):{
			system("cls");
			if(root == NULL){
				printf("There's No Data");
				printf("\nPress enter to continue...");
				getch();goto mainmenu;
			}

			else{
				printf("All Data: ");
				viewInOrder(root);
				
				int src;
				printf("\n\nDelete: ");
				scanf("%d",&src);
				data *found = search(root,src);
				
				if(found!=NULL){
					printf("Data Found");
					printf("\nValue %d was deleted",src);
					root = deletion(root,src);
					printf("\nPress enter to continue...\n\n");
					getch();goto mainmenu;
					
				}
				else{
					printf("Data not Found");
					printf("\nPress enter to continue...\n\n");
					getch();goto mainmenu;
				}
			}
		break;
		}
		
		case (3):{
			system("cls");
			if(root == NULL ){
				printf("There's No Data\n");
			}
			else{
				printf("PreOrder: ");
				viewPreOrder(root);
				printf("\nInOrder: ");
				viewInOrder(root);
				printf("\nPostOrder: ");
				viewPostOrder(root);
			}
			
			printf("\n\nPress enter to continue...\n\n");
			getch(); goto mainmenu;
			break;
		}
		
		case (4):{
			system("cls");
			printf("Thank You :)");
			break;
		}
	}
	
	return 0;
}
