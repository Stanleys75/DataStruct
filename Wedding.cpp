#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

bool webValidation(char web[]){
	int len = strlen(web);
	

	if(web[0] != 'w' || web[1] != 'w' || web[2] != 'w' || web[3] != '.'){
		return false;
	}
	if(web[len-6] != '.' || web[len-5] != 'w' || web[len-4] != 'o' || web[len-3] != '.' || web[len-2] != 'i' || web[len-1] != 'd'){
		return false;
	}

	for(int i=0; i<len; i++){
		if(web[i] == ' '){
			return false;
		}
		
	}
	return true;
	
}

struct data{
	char nama[30];
	long long int fee;
	char location[30];
	int crew;
	char website[100];
	int height;
	
	data* left;
	data* right;
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

struct data* create(char nama[],long long int fee,char location[],int crew,char website[]){
	data* curr = (data*)malloc(sizeof(data));
	
	strcpy(curr->nama,nama);
	curr->fee = fee;
	strcpy(curr->location,location);
	curr->crew = crew;
	strcpy(curr->website,website);
	curr->height = 1;
	
	curr->left = curr->right = NULL;
	
	return curr;
}

data* rightrotate(struct data* root){
	data* x = root->left;
	data* y = x->right;
	
	x->right = root;
	root->left = y;
	
	root->height = max(getheight(root->left),getheight(root->right)) + 1;
	x -> height = max(getheight(root->left),getheight(root->right)) + 1;
	
	return x;
}

data* leftrotate(struct data* root){
	data* x = root->right;
	data* y = x->left;
	
	x->left = root;
	root->right = y;
	
	root->height = max(getheight(root->left),getheight(root->right)) + 1;
	x -> height = max(getheight(root->left),getheight(root->right)) + 1;
	
	return x;
}

struct data* insert(struct data* root,char nama[],long long int fee,char location[],int crew,char website[]){
	if(root==NULL){
		return create(nama,fee,location,crew,website);
	} else if(strcmp(nama,root->nama)<0){
		root->left = insert(root->left,nama,fee,location,crew,website);
	} else{
		root->right = insert(root->right,nama,fee,location,crew,website);
	}
	
	if(root == NULL){
		return root;
	}
	root->height = max(getheight(root->left),getheight(root->right)) + 1;
	int balance = getbalance(root);
	
	if(balance > 1 && strcmp(nama,root->left->nama) < 0){
		return rightrotate(root);
	}
	if(balance > 1 && strcmp(nama,root->left->nama) > 0){
		root->left = leftrotate(root->left);
		return rightrotate(root);
	}
	if(balance < -1 && strcmp(nama,root->right->nama) > 0){
		return leftrotate(root);
	}
	if(balance < -1 && strcmp(nama,root->right->nama) < 0){
		root->right = leftrotate(root->right);
		return leftrotate(root);
	}
	
	return root;
}

struct data* deletion(struct data* root,char nama[]){
	if(root==NULL){
		return NULL;
	} else if(strcmp(nama,root->nama)<0){
		root->left = deletion(root->left,nama);
	} else if (strcmp(nama,root->nama)>0){
		root->right = deletion(root->right,nama);
	} else{
		if(root->left == NULL && root->right == NULL){
			free(root);
			root = NULL;
		} else if(root->left != NULL && root->right == NULL){
			struct data* temp = root->left;
			*root = *temp;
			free(temp);
			temp = NULL;
			
		}else if(root->left == NULL && root->right != NULL){
			struct data* temp = root->right;
			*root = *temp;
			free(temp);
			temp = NULL;
			
		}else if(root->left != NULL && root->right != NULL){
			struct data* temp = root->left;
			while(temp->right != NULL){
				temp = temp->right;
			}
			strcpy(root->nama,temp->nama);
			root->fee = temp->fee;
			strcpy(root->location,temp->location);
			root->crew = temp->crew;
			strcpy(root->website,temp->website);
			
			root->left = deletion(root->left, temp->nama);
			
		}
	}
	if(root == NULL){
		return root;
	}
	root->height = max(getheight(root->left),getheight(root->right)) + 1;
	int balance = getbalance(root);
	
	if(balance > 1 && strcmp(nama,root->left->nama) < 0){
		return rightrotate(root);
	}
	if(balance > 1 && strcmp(nama,root->left->nama) > 0){
		root->left = leftrotate(root->left);
		return rightrotate(root);
	}
	if(balance < -1 && strcmp(nama,root->left->nama) < 0){
		return leftrotate(root);
	}
	if(balance < -1 && strcmp(nama,root->left->nama) > 0){
		root->right = leftrotate(root->right);
		return leftrotate(root);
	}
	
	return root;
}

struct data* deleteAll(struct data* root){
	if(root!=NULL){
		deleteAll(root->left);
		deleteAll(root->right);
		root->right = root->left =NULL;
		free(root);
		root = NULL;
	}	
	return root;
}

struct data* find(struct data* root, char nama[]){
	if(root == NULL){
		return NULL;
	} 
	if(strcmp(nama,root->nama) == 0){
		return root;
	} else if(strcmp(nama,root->nama)<0){
		return find(root->left,nama);
		
	} else {
		return find(root->right,nama);
	}
	
}

void viewin(struct data* root){
	if(root!=NULL){
		viewin(root->left);
		printf("|  %s  |  %lld  |  %s  |  %d  |   %s   |\n", root->nama,root->fee,root->location,root->crew, root->website);
		viewin(root->right);	
	}
}

void viewpre(struct data* root){
	if(root!=NULL){
		printf("|  %s  |  %lld  |  %s  |  %d  |   %s   |\n", root->nama,root->fee,root->location,root->crew, root->website);
		viewpre(root->left);
		viewpre(root->right);
		
	}
}

void viewpost(struct data* root){
	if(root!=NULL){
		viewpost(root->left);
		viewpost(root->right);
		printf("|  %s  |  %lld  |  %s  |  %d  |   %s   |\n", root->nama,root->fee,root->location,root->crew, root->website);
	}
}

int main(){
	struct data* root = NULL;
	char nama1[30];
	long long int fee1;
	char location1[30];
	int crew1;
	char website1[100];
	int opt;
	
	menu:
		do{
			system("cls");
			printf("WO WEDDING ORGANIZER");
			puts("\n\n");
			printf("1. Add Available Wedding Organizer\n");
			printf("2. Choose Available Wedding Organizer\n");
			printf("3. Book All Wedding Organizer\n");
			printf("4. View Available Wedding Organizer\n");
			printf(">> ");
			scanf("%d", &opt);
			
		} while(opt<1 || opt>4);
	
	switch(opt){
		case(1):{
		
			do{
				printf("Wedding Organizer Nama [3 - 25 characters]: ");
				scanf(" %[^\n]", nama1);
			} while (strlen(nama1)<3 || strlen(nama1)>25);
			
			do{
				printf("Wedding Organizer Fee [1,000,000 - 50,000,000]: ");
				scanf("%lld", &fee1);
			} while(fee1< 1000000 || fee1 > 50000000);
			
			do{
				printf("Wedding Organizer Location [4 - 30 characters]: ");
				scanf(" %[^\n]", location1);				
			} while(strlen(location1) < 4 || strlen(location1) > 30);
			
			do{
				printf("Wedding Organizer Total Crew [2 - 2,000]: ");
				scanf(" %d", &crew1);
			} while(crew1 < 2 || crew1 > 2000);
			
			do {
				printf("Wedding Organizer Website [13 - 25 characters]: ");
				scanf(" %[^\n]", website1);
			}while (webValidation(website1) == false || (strlen(website1) < 13 || strlen(website1) > 25) );
			
			char a;
			do{
				printf("Confirm Insert [y / n]: ");
				scanf(" %c", &a);		
			} while (a != 'y' && a != 'n');
			
			if(a == 'y'){
				
				root = insert(root,nama1,fee1,location1,crew1,website1);
				printf("Insert Success!");
				goto menu;
			} else {
				goto menu;
			}
			
			
			
			break;
		}
		case(2):{
			if(root == NULL){
				printf("All Wedding Organizer is fully booked...\n");
				printf("Press enter to continue...");
				getch();
				goto menu;
			
			} else {
				printf("Which Wedding Organizer that you want to choose [Name]? ");
				char f[30];
				scanf(" %[^\n]", f);
				data* temp = find(root,f);
				if(temp == NULL){
					printf("Wedding Organizer doesn't exists\n");
					printf("Press enter to continue...");
					getch();
					goto menu;
				} else{
					printf("Are you sure %s is the one for you\n", temp->nama);
					char b;
					do{
						printf("Confirm Lie Planner [y / n]: ");
						scanf(" %c", &b);
					} while(b != 'y' && b != 'n');
					
					if(b == 'y'){
						root = deletion(root,f);
						printf("Reservation for Lie Planner Success\n");
						goto menu;
					} else {
						goto menu;
					}
				}
			}
			break;
		}
		case(3):{
			if(root == NULL){
				printf("All Wedding Organizer is fully booked...\n");
				printf("Press enter to continue...");
				getch();
				goto menu;
			} else {
				printf("Are you going to book us all??! YAYYY!!\n ");
				char c;
				do{
					printf("Confirm Book All [y / n]: ");
					scanf(" %c", &c);
				} while(c != 'y' && c != 'n');
					
				if(c == 'y'){
					root = deleteAll(root);
					printf("Reservation for All Wedding oraganizer succed\n");
					goto menu;
				} else {
					goto menu;
				}
				
			}
			break;
		}
		case(4):{
			if(root == NULL){
				printf("All Wedding Organizer is fully booked...\n");
				printf("Press enter to continue...");
				getch();
				goto menu;
			} else {
				int e;	
				view:
					do{
					system("cls");
					printf("In which way do you want to look at the data?\n");
					printf("1. PreOrder\n");
					printf("2. InOrder\n");
					printf("3. PostOrder\n");
					printf("4. back\n");
				
					printf(">> ");
					scanf("%d", &e);
					} while (e<1 || e>4);
					
				switch(e){
					case(1):{
						viewpre(root);
						getch();
						goto view;
						break;
					}
					case(2):{
						viewin(root);
						getch();
						goto view;
						break;
					}
					case(3):{
						viewpost(root);
						getch();
						goto view;
						break;
					}
					case(4):{
						goto menu;
						break;
					}
				}
			
			}
			break;
		}
		case(5):{
			
			break;
		}
	}
	return 0;
}
