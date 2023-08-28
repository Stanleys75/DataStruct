#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

bool validation(char a[]){
	if(a[0] >= 'a' && a[0] <= 'z'){
		return false;
	}
	int l = strlen(a);
	int idx = 1;
	int idxx = 0;
	
	for(int i=0;i<l;i++){
		if(a[i] >= 'a' && a[i] <= 'z' ){
			idx+=1;
		} else if(a[i] == ' '){
			idxx = 1;
			break;
		}
	}
	
	return true;
}

struct data{
	char ID[30];
	char nama[30];
	char type[30];
	int price;
	
	int height;
	
	data* left;
	data* right;
};



int max(int a, int b){
	if(a>b) return a;
	return b;
}

int getheight(data* temp){
	if(temp == NULL){
		return 0;
	} else {
		return temp->height;
	}
}

int getbalance(data* temp){
	if(temp == NULL){
		return 0;
	} else {
		return getheight(temp->left) - getheight(temp->right);
	}
}

data* create(char ID[], char nama[], char type[], int price){
	struct data* curr = (data*)malloc(sizeof(data));
	
	strcpy(curr->ID,ID);
	strcpy(curr->nama,nama);
	strcpy(curr->type,type);
	curr->height = 1;
	curr->price = price;
	
	curr->left = curr->right = NULL;
	
	return curr;
}

data* rightrotate(struct data* root){
	data* x = root->left;
	data* y = x->right;
	
	x->right = root;
	root->left = y;
	
	x->height = max(getheight(x->left),getheight(x->right))+1;
	root->height = max(getheight(root->left),getheight(root->right))+1;
	
	return x;
}
data* leftrotate(struct data* root){
	data* x = root->right;
	data* y = x->left;
	
	x->left = root;
	root->right = y;
	
	x->height = max(getheight(x->left),getheight(x->right))+1;
	root->height = max(getheight(root->left),getheight(root->right))+1;
	
	return x;
}

struct data* insert(struct data* root,char ID[], char nama[], char type[], int harga){
	if(root == NULL){
		return create(ID,nama,type,harga);
	} 
	if(strcmp(ID,root->ID)<0){
		root->left = insert(root->left,ID,nama,type,harga);
	} else{
		root->right = insert(root->right,ID,nama,type,harga);
	}
	
	if(root == NULL){
		return root;
	}
	
	root->height = max(getheight(root->left),getheight(root->right))+1;
	int balance = getbalance(root);
	
	if(balance > 1 && strcmp(ID,root->left->ID) < 0){
		return rightrotate(root);
	}
	if(balance > 1 && strcmp(ID,root->left->ID) > 0){
		root->left = leftrotate(root->left);
		return rightrotate(root);
	}
	if(balance < -1 && strcmp(ID,root->left->ID) > 0){
		return leftrotate(root);
	}
	if(balance < -1 && strcmp(ID,root->left->ID) < 0){
		root->right = rightrotate(root->right);
		return leftrotate(root);
	}
	
	return root;
}

struct data* deletion(struct data* root, char ID[]){
	if(root == NULL){
		return NULL;
	} 
	if(strcmp(ID,root->ID)<0){
		root->left = deletion(root->left,ID);
	} else if (strcmp(ID,root->ID)>0){
		root->right = deletion(root->right,ID);
	} else {
		if(root->left == NULL && root->right == NULL){
			free(root);
			root=NULL;
		} else if(root->left != NULL && root->right == NULL){
			struct data* temp = root->left;
			*root = *temp;
			free(temp);
			temp=NULL;
		} else if(root->left == NULL && root->right != NULL){
			struct data* temp = root->right;
			*root = *temp;
			free(temp);
			temp=NULL;
		} else if (root->left != NULL && root->right != NULL){
			struct data* temp = root->left;
			while(temp->right != NULL){
				temp = temp->right;
			}
			strcmp(root->ID,temp->ID);
			strcmp(root->nama,temp->nama);
			strcmp(root->type,temp->type);
			root->price = temp->price;
			
			root->left = deletion(root->left, temp->ID);
		}
	}
	if(root == NULL){
		return root;
	}
	root->height = max(getheight(root->left),getheight(root->right))+1;
	int balance = getbalance(root);
	
	if(balance > 1 && strcmp(ID,root->left->ID) < 0){
		return rightrotate(root);
	}
	if(balance > 1 && strcmp(ID,root->left->ID) > 0){
		root->left = leftrotate(root->left);
		return rightrotate(root);
	}
	if(balance < -1 && strcmp(ID,root->left->ID) > 0){
		return leftrotate(root);
	}
	if(balance < -1 && strcmp(ID,root->left->ID) < 0){
		root->right = rightrotate(root->right);
		return leftrotate(root);
	}
	
	return root;
	
}

void pre(data* root){
	if(root!=NULL){
		printf("|%-10s|%-10s|%-10s|%d| ", root->ID, root->nama, root->type,root->price);
		pre(root->left);
		pre(root->right);
	}
}

void in(data* root){
	if(root!=NULL){
		in(root->left);
		printf("|%-10s|%-10s|%-10s|%d| ", root->ID, root->nama, root->type,root->price);
		in(root->right);
	}
}
void post(data* root){
	if(root!=NULL){
		post(root->left);
		post(root->right);
		printf("|%-10s|%-10s|%-10s|%d| ", root->ID, root->nama, root->type, root->price);
	}
}

struct data* find(struct data* root, char ID[]){
	if(root == NULL){
		return NULL;
	}
	if(strcmp(root->ID,ID) == 0){
		return root;
	} else if(strcmp(root->ID,ID) < 0){
		find(root->left,ID);
	} else if((strcmp(root->ID,ID) > 0)){
		find(root->right,ID);
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

int main(){
	struct data* root = NULL;
	
	int opt;
	menu:
		do{
			system("cls");
			printf("BLUEJACK FIVVER \n");
			printf("===================\n");
			printf("1. Add Project\n");
			printf("2. View All Project\n");
			printf("3. Delete Project\n");
			printf("4. Exit and Delete All Project\n");
			printf("Choose: ");
			scanf("%d", &opt);
		}while (opt<1||opt>4);
	
	switch(opt){
		case(1):{
			char nama1[30];
			char type1[30];
			int price1;
			char a[3];
			do{
				printf("Input Project ID [PRXXX . X-> number][must uniqur]: ");
				scanf("%s", a);
				
			} while(a[0] == NULL && a[1]== NULL && a[2]==NULL);
			
			do{
				printf("Input Project Name [Min 3 Characters][start with capital]: ");
				scanf(" %[^\n]", nama1);
			} while (validation(nama1)==false || strlen(nama1) < 3);
			
			do{
				printf("Input Project Type ['Website' | 'Mobile Apps'][Case sensitive]: ");
				scanf(" %[^\n]", type1);
				
			} while(strcmp(type1,"Website") != 0 && strcmp(type1,"Mobile Apps") != 0);
			
			do{
				printf("Input Project Price [more than 5 $]: ");
				scanf("%d", &price1);	
			} while (price1 <= 5);
			
			char ID1[10] = "PR";
			strcat(ID1,a);
			
			root = insert(root,ID1,nama1,type1,price1);
			
			printf("\nProject ID         : %s\n", ID1);
			printf("Project Name       : %s\n", nama1);
			printf("Project Type       : %s\n", type1);
			printf("Project Price      : %d\n", price1);
			printf("press enter to continue\n");
			getch();
			goto menu;
			
			break;
		}
		case(2):{
			if(root == NULL){
				printf("No Data Project !\n");
				printf("press enter to continue\n");
				getch();
				goto menu;
			} else{
				char b[10];
				do{
					printf(" Input [Pre | In |Post]: ");
					scanf(" %[^\n]", b);
				}while(strcmp(b,"Pre") != 0 && strcmp(b,"In") != 0 && strcmp(b,"Post") != 0);
				
				if(strcmp(b,"Pre") == 0){
					printf("\n");
					pre(root);
					printf("\npress enter to continue\n");
					getch();
					goto menu;
				} else if(strcmp(b,"In") == 0){
					printf("\n");
					in(root);
					printf("\npress enter to continue\n");
					getch();
					goto menu;
				} else if(strcmp(b,"Post") == 0){
					printf("\n");
					post(root);
					printf("\npress enter to continue\n");
					getch();
					goto menu;
				} 
				
				
			}
			break;
		}
		case(3):{
			char d[20];
			if(root==NULL){
				printf("No Data Project !\n");
				printf("press enter to continue\n");
				getch();
				goto menu;
			} else{
				in(root);
				menud:	
					printf("\n\nChoose Project ID: ");
					scanf(" %[^\n]",&d);
				
				
				struct data* temp = find(root,d);
				if(temp == NULL){
					goto menud;
				} else {
					root = deletion(root,d);
					goto menu;	
				}
			}
			
			break;
		}
		case(4):{
			root = deleteAll(root);
			goto menu;
			break;
		}
	}
	
	
	return 0;
}
