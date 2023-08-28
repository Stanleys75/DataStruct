#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

bool validasi(char a[]){
	int len = strlen(a);
	
	if(a[0] >= 'a'  &&  a[0] <= 'z' ){
		return false;
	}	
	int idx;
	int idxx = 1;
	for(int i=0;i<len;i++){
		if(a[i] >= 'a' && a[0] <= 'z'){
			idxx += 1;
			
		} else if(a[i] == ' '){
			idx += 1;
			break;
		}
		
	}
	
	
	if(idx==0){
		return false;
	}
	printf("%d", idxx);
	if(a[idxx+2] == NULL){
		return false;
	}  
	if(a[idxx+3] == NULL){
		return false;
	}  
	if(a[idxx+4] == NULL){
		return false;
	}  

	
	return true;
}

struct data{
	char item[100];
	char category[100];
	int price;
	char ingredients[100];
	int height;
	
	data* right;
	data* left;
};

int max(int a, int b){
	if(a>b){
		return a;
	}
	return b;
}

int getheight(struct data* temp){
	if(temp == NULL){
		return NULL;
	} else{
		return temp->height;
	}
}

int getbalance(struct data* temp){
	if(temp == NULL){
		return NULL;
	} else{
		return getheight(temp->left)-getheight(temp->right);
	}
}

struct data* create(char item[],char category[],int price,char ingredients[]){
	
	struct data* curr = (data*)malloc(sizeof(data));
	curr->height = 1;
	
	strcpy(curr->item,item);
	strcpy(curr->category,category);
	strcpy(curr->ingredients,ingredients);
	curr->price = price;
	
	curr->left = curr->right = NULL;
	
	return curr;
	
}

data* rightrotate(struct data* root){
	data* x = root->left;
	data* y = x->right;
	
	x->right = root;
	root->left = y;
	
	x->height = max(getheight(root->left),getheight(root->right)) + 1;
	root->height = max(getheight(root->left),getheight(root->right)) + 1;
	
	return x;
}

data* leftrotate(struct data* root){
	data* x = root->right;
	data* y = x->left;
	
	x->left = root;
	root->right = y;
	
	x->height = max(getheight(root->left),getheight(root->right)) + 1;
	root->height = max(getheight(root->left),getheight(root->right)) + 1;
	
	return x;
}

data* insert(struct data* root,char item[],char category[],int price,char ingredients[]){
	
	if(root == NULL){
		return create(item,category,price,ingredients);
	} if(strcmp(item,root->item)<0){
		root->left = insert(root->left,item,category,price,ingredients);
	} else {
		root->right = insert(root->right,item,category,price,ingredients);
	}
	
	if(root == NULL){
		return root;
	}
	root->height = max(getheight(root->left),getheight(root->right)) + 1;
	int balance = getbalance(root);
	
	if(balance > 1 && strcmp(item,root->left->item) < 0){
		return rightrotate(root);
	}
	if(balance > 1 && strcmp(item,root->left->item) > 0){
		root->left = leftrotate(root->left);
		return rightrotate(root);
	}
	if(balance < -1 && strcmp(item,root->left->item) > 0){
		return leftrotate(root);
	}
	if(balance < -1 && strcmp(item,root->left->item) < 0){
		root->right = rightrotate(root->right);
		return leftrotate(root);
	}
	
	return root;
}

data* deletion(struct data* root, char item[]){
	if(root == NULL){
		return NULL;
	} 
	if(strcmp(item,root->item)<0){
		root->left = deletion(root->left,item);
	} else if (strcmp(item,root->item)>0){
		root->right = deletion(root->right,item);
	} else {
		if(root->right == NULL && root->left == NULL){
			free(root);
			root = NULL;
		} else if(root->right != NULL && root->left == NULL){
			struct data* temp = root->right;
			*root = *temp;
			free(temp);
			temp = NULL;
		} else if(root->right == NULL && root->left != NULL){
			struct data* temp = root->left;
			*root = *temp;
			free(temp);
			temp = NULL;
		}  else if(root->right != NULL && root->left != NULL){
			struct data* temp = root->left;
			while(temp->right!=NULL){
				temp = temp->right;
			}
			
			strcpy(root->item,temp->item);
			strcpy(root->category,temp->category);
			strcpy(root->ingredients,temp->ingredients);
			root->price = temp->price;
			
			root->left = deletion(root->left,temp->item);
			
		} 
	}
	if(root == NULL){
		return root;
	}
	root->height = max(getheight(root->left),getheight(root->right)) + 1;
	int balance = getbalance(root);
	
	if(balance > 1 && strcmp(item,root->left->item) < 0){
		return rightrotate(root);
	}
	if(balance > 1 && strcmp(item,root->left->item) > 0){
		root->left = leftrotate(root->left);
		return rightrotate(root);
	}
	if(balance < -1 && strcmp(item,root->left->item) > 0){
		return leftrotate(root);
	}
	if(balance < -1 && strcmp(item,root->left->item) < 0){
		root->right = rightrotate(root->right);
		return leftrotate(root);
	}
	
	return root;
}

struct data* finddata(struct data* root, char item[]){
	if(root == NULL){
		return NULL;
	}
	if(strcmp(item,root->item)<0){
		finddata(root->left,item);
	} else if(strcmp(item,root->item)>0){
		finddata(root->right,item);
	} else if(strcmp(item,root->item)==0){
		return root;
	}
}

struct data* deleteAll(struct data* root){
	if(root!=NULL){
		deleteAll(root->left);
		deleteAll(root->right);
		root->left = root->right = NULL;
		free(root);
		root = NULL;
	}
	
	return root;
}

void viewpost(struct data* root){
	if(root!=NULL){
		viewpost(root->left);
		viewpost(root->right);
		printf("| %s   | %s   | %d  | %s  |\n", root->item,root->category,root->price,root->ingredients);
	
	}
}

void viewpre(struct data* root){
	if(root!=NULL){
		printf("| %s   | %s   | %d  | %s  |\n", root->item,root->category,root->price,root->ingredients);
		viewpre(root->left);
		viewpre(root->right);
		
	}
}

void viewin(struct data* root){
	if(root!=NULL){
		viewin(root->left);
		printf("| %s   | %s   | %d  | %s  |\n", root->item,root->category,root->price,root->ingredients);	
		viewin(root->right);
	
	}
}


int main(){
	struct data* root = NULL;
	
	char item1[100];
	char category1[100];
	int price1;
	
	
	menu:
		int opt;
		do{
			system("cls");
			printf("Menu:\n");
			printf("1. View Item\n");
			printf("2. Insert Item\n");
			printf("3. Delete Item\n");
			printf("4. Search Item\n");
			printf("5. Exit\n");
			printf("[1-5]\n");
			printf(">> ");
			
			scanf("%d", &opt);
		}while (opt<1 || opt>5);
	
	
	switch(opt){
		case(1):{
			char p[10];
			do{
				printf("Input order print[Pre | In | Post](Case sensitive): ");
				
				scanf(" %[^\n]", p);	
			}while (strcmp(p,"Pre")!=0 && strcmp(p,"In")!=0 && strcmp(p,"Post")!=0);
			
			if(strcmp(p,"Pre") == 0){
				viewpre(root);
				printf("Press enter to continue..");
				getch();
				goto menu;
			} else if(strcmp(p,"In") == 0){
				viewin(root);
				printf("Press enter to continue..");
				getch();
				goto menu;
			} else if(strcmp(p,"Post") == 0){
				viewpost(root);
				printf("Press enter to continue..");
				getch();
				goto menu;
			}
			
			break;
		}
		case(2):{
			
			do{
				printf("Input item name [10 - 35 characters, min. 2 words, capital]: ");
				scanf(" %[^\n]", item1);
			} while (validasi(item1)==false || (strlen(item1)<10 || strlen(item1)>35));
			
			do{
				printf("Input item price [50000 - 1000000]: ");
				scanf("%d", &price1);
			} while(price1<50000 || price1>1000000);
			
			do{
				printf("Input Item category [""Whole Cakes"" | ""Cup Cakes"" | ""Chocolate""]: ");
				scanf(" %[^\n]", category1);
			} while (strcmp(category1,"Whole Cakes") != 0 && strcmp(category1,"Cup Cakes") != 0 && strcmp(category1,"Chocolate") != 0);
			char ingredient[100];
			do{
				printf("Input item ingredients description [Vegan | Non Vegan]: ");
				scanf(" %[^\n]", ingredient);
			} while (strcmp(ingredient,"Vegan")!=0 && strcmp(ingredient,"Non Vegan")!=0);
			
			root = insert(root,item1,category1,price1,ingredient);
			
			printf("\n [New Item is Successfully Inserted]\n");
			printf("Press enter to continue..");
			getch();
			goto menu;
			break;
		}
		case(3):{
			printf("DELETE ITEM\n");
			if(root == NULL){
				goto menu;
			} else {
				char s[20];
				viewin(root);
				printf("\n\n input item name to be deleted: ");
				scanf(" %[^\n]", s);
				struct data* temp = finddata(root,s);
				if(temp == NULL){
					printf("Data no found\n");
					printf("Press enter to continue..");
					getch();
					goto menu;
				} else {
					printf("[Delete Successfully]\n");
					printf("Press enter to continue..");
					root = deletion(root,s);
					getch();
					goto menu;	
				}
			}
			break;
		}
		case(4):{
			printf("SEARCH ITEM BY NAME\n");			
			if(root == NULL){
				goto menu;
			} else {
				char ss[20];
				printf("Input item name to be searched: ");
				scanf(" %[^\n]", ss);
				struct data* temp = finddata(root,ss);
				if(temp == NULL){
					printf("Item is not found\n");
					printf("Press enter to continue..");
					getch();
					goto menu;
				} else {
					printf("Item is found\n");
					printf("Item Name : %s\n", temp->item);
					printf("Item Category : %s\n", temp->category);
					printf("Item Ingredients : %s\n", temp->ingredients);
					printf("Item Price : %d\n", temp->price);
					printf("Press enter to continue..\n");
					getch();
					goto menu;	
				}
			}
			
			break;
		}
		case(5):{
			
			break;
		}
	}
}
