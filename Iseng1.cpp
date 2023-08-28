#include<stdio.h>
#include<stdlib.h>
#include<string.h>

bool emailValidation(char email[]){
	int len = strlen(email);
	
	if(email[0] == '@' || email[0] == '.'){
		return false;
	}
	if(email[len-1] == '@' || email[len-1] == '.'){
		return false;
	}
	if(email[len-4] != '.' && email[len-3] != 'c'&& email[len-2] != 'o'&& email[len-1] != 'm'){
		return false;
	}
	int atCount = 0;
	int atIdx = 0;
	for(int i=0; i<len; i++){
		if(email[i] == '@'){
			atIdx = i;
			atCount++;
			if(email[i-1] == '.' || email[i+1] == '.'){
				return false;
			}
		}
	}
	if(atCount != 1){
		return false;
	}
	for(int i=0; i<atIdx; i++){
		bool lowerLetter = email[i] >= 'a' && email[i] <= 'z';
		bool upperLetter = email[i] >= 'A' && email[i] <= 'Z';
		bool numeric = email[i] >= '0' && email[i] <= '9';
		
		bool uniqueChar = lowerLetter || upperLetter || numeric;
		if(uniqueChar == false){
			return false;
		}
	}
	
	for(int i = 0; i<len;i++){
		bool lowerLetter = email[i] >= 'a' && email[i] <= 'z';
		bool upperLetter = email[i] >= 'A' && email[i] <= 'Z';
		bool numeric = email[i] >= '0' && email[i] <= '9';
		bool isAt = email[i] >= '@';
		bool isDot = email[i] == '.';
		bool notUniqueChar = lowerLetter || upperLetter || numeric ||isAt || isDot;
		
		if(notUniqueChar == false) {
			return false;
		}
		
		return true;
	}
	
}

struct Node{
	char title[30]; //key
	char genre[30];
	char email[30];
	int stock;	
	Node* left;
	Node* right;
	int height;
	
};


int height(Node* node){
	if (node == NULL) {
		return 0;
	}
	return node->height;
}

int max(int a, int b){
	if(b>a){
		return b;	
	}
	return a;
}

Node* root = NULL;
Node* createNode(char title[],char genre[],char email[], int stock){
	Node* newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->title,title);
	strcpy(newNode->genre,genre);
	strcpy(newNode->email,email);
	newNode->stock = stock;
	newNode->left = newNode->right = NULL;
	newNode->height = 1;
	
	return newNode;
}

Node* rightRotate(Node* root){
	Node* x = root->left;
	Node* y = x->right;
	
	x->right = root;
	root->left = y;
	
	root->height = max(height(root->left),height(root->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;
	
	return x;
}

Node* leftRotate(Node* root){
	Node* x = root->right;
	Node* y = x->left;
	
	x->left = root;
	root->right = y;
	
	root->height= max(height(root->left),height(root->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;
	
	return x;
}

Node* insertion(Node* root, char title[],char genre[],char email[], int stock){
	if(root == NULL) {
		return createNode(title,genre,email,stock);
	}
	
	if (strcmp(title, root->title) < 0){
		root->left = insertion(root->left,title,genre,email,stock);
	}	else{
		root->right = insertion(root->right,title,genre,email,stock);
	}
	
	root->height = max(height(root->left),height(root->right)) + 1;
	
	int balance = height(root->left) - height(root->right);
	
	// berdasarkan balance akan melakukan rotasi dengan konsdisi beritkut
	
	//ll case
	
	if(balance>1 && strcmp(title,root->left->title) < 0){
		// right rotate
		return rightRotate(root);
	}
	
	//lR case
	if(balance>1 && strcmp(title,root->left->title) > 0){
		//left rotate
		//right rotate
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	
	//RR case
	if(balance<-1 && strcmp(title,root->right->title) > 0){
		// left rotate
		return leftRotate(root);
	}
	
	//RL case
	if(balance<-1 && strcmp(title,root->right->title) < 0){
		// right rotate
		// left rotate
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	
	return root;
}


Node* deletion(Node* root, char title[]){
	//kalau misal dia udah sampai ujung dan gak ketemu
	if(root == NULL){
		return NULL;
	}
	if(strcmp(title, root->title) < 0){
		root->left = deletion(root->left,title);
	}
	else if(strcmp(title, root->title) > 0){
		root->right = deletion(root->right,title);
	}
	else{
		if(root->left == NULL && root->right==NULL){
			free(root);
			root=NULL;
			
		} else if(root->left != NULL && root->right == NULL){
			Node* temp = root->left;
			*root = *temp;
			free(temp);
			temp = NULL;
			
		} else if(root->left == NULL && root->right != NULL){
			Node* temp = root->right;
			*root = *temp;
			free(temp);
			temp = NULL;
			
		} else if(root->left != NULL && root->right != NULL){
			Node* temp = root->left;
			while(temp->right != NULL){
				temp = temp->right;
			}
			
			strcpy(root->title, temp->title);
			strcpy(root->genre, temp->genre);
			strcpy(root->email, temp->email);
			root->stock = temp->stock;
			
			root->left = deletion(root->left, temp->title);
		}
	}
	
	if(root == NULL){
		return root;
	}
	root->height = max(height(root->left),height(root->right)) + 1;
	
	int balance = height(root->left) - height(root->right);
	
	// berdasarkan balance akan melakukan rotasi dengan konsdisi beritkut
	
	//ll case
	
	if(balance>1 && strcmp(title,root->left->title) < 0){
		// right rotate
		return rightRotate(root);
	}
	
	//lR case
	if(balance>1 && strcmp(title,root->left->title) > 0){
		//left rotate
		//right rotate
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	
	//RR case
	if(balance<-1 && strcmp(title,root->right->title) > 0){
		// left rotate
		return leftRotate(root);
	}
	
	//RL case
	if(balance<-1 && strcmp(title,root->right->title) < 0){
		// right rotate
		// left rotate
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	
	return root;
}

Node* deleteAll(Node* root){
	if(root != NULL){
		deleteAll(root->left);
		deleteAll(root->right);
		root->right = root->left = NULL;
		free(root);
		root = NULL;
	}
}

void viewInOrder(Node* root){
	if(root!=NULL){
		viewInOrder(root->left);
		printf("|%-25s|%-15s|%-15s|%-10d| \n", 
				root->title, root->genre, root->email, root->stock);
		viewInOrder(root->right);
		
	}
}

void viewPreOrder(Node* root){
	if(root!=NULL){
		
		printf("|%-25s|%-15s|%-15s|%-10d| \n", 
				root->title,root->genre,root->email,root->stock);
		viewPreOrder(root->left);
		viewPreOrder(root->right);
		
	}
}

void viewPostOrder(Node* root){
	if(root!=NULL){
		viewPostOrder(root->left);
		viewPostOrder(root->right);
		printf("|%-25s|%-15s|%-15s|%-10d| \n", 
				root->title,root->genre,root->email,root->stock);
		
		
	}
}

Node* findNode (Node* root, char title[]){
	if(root == NULL){
		return NULL;
	}
	if (strcmp(title, root->title) == 0){
		return root;
	}
	if(strcmp(title, root->title)<0){
		findNode(root->left,title);
	} else{
		findNode(root->right,title);
	}
}

int main(){
//	root = insertion(root, "tes satu", "genre satu", "email", 50);
//	root = insertion(root, "tes 2", "genre 2", "email", 50);
//	root = insertion(root, "tes 3", "genre 3", "email", 500);
//	viewInOrder(root);
//	root = deletion(root,"tes 3");
//	viewInOrder(root);

	int menu = -1;
	char temptitle[30]; 
	char tempgenre[30];
	char tempemail[30];
	int tempstock;
	
	do{
		do{
			puts("");
			puts("GAME SHOP");
			puts("1. Insert Game");
			puts("2. View Game");
			puts("3. Update Stock");
			puts("4. Exit");
			printf(">> ");
			scanf("%d", &menu); getchar();
		}while (menu<1||menu>4);
		
		switch(menu){
			case 1:
				do{
					printf("input game title [5-25 chars][unique]: ");
					scanf("%[^\n]",temptitle); getchar();
				} while(findNode(root,temptitle)!=NULL || strlen(temptitle)<5 || strlen(temptitle)>25);
				do{
					printf("input game genre [Action | RPG | Adventure | Card Game]: ");
					scanf("%[\n]", tempgenre); getchar();
					
				} while (strcmp(tempgenre,"Action")!=0 && strcmp(tempgenre,"RPG")!=0 && strcmp(tempgenre,"Adventure")!=0 &&strcmp(tempgenre,"Card Game")!=0);
				do{
					printf("input email: ");
					scanf("%[^\n]", tempemail); getchar();
				} while (emailValidation(tempemail)==false);
				do{
					printf("Input game stock [at least 1]: ");
					scanf("%d", &tempstock); getchar();
				} while (tempstock<1);
				root = insertion(root,temptitle,tempgenre,tempemail,tempstock);
				puts("Insert Success !!");
				
				
				
				break;
			
			case 2:
				viewInOrder(root);
				break;
			case 3:
				printf("Input Game Title: ");
				scanf("%d", temptitle); getchar();
				Node* toUpdate = findNode(root,temptitle);
				if(toUpdate==NULL){
					puts("Game not found");
				} else {
					printf("Game title: %s \n", toUpdate->title);
					printf("Game genre: %s \n", toUpdate->genre);
					printf("Game email: %s \n", toUpdate->email);
					printf("Game stock: %s \n", toUpdate->stock);
					do{
						printf("Input Update Type: ");
						scanf("%s", temptype); getchar();
						
					} while(strcmpi(temptype, "add")!= 0 &&strcmpi(temptype, "remove")!= 0);
					do{
						if(strcmpi(temptype, "add")== 0){
							printf("Input qty to add: ");
						}else {
							printf("Input qty to remove: ");
						}
						scanf("%d", &tempstock); getchar();
						
						if(strcmpi(temptype, "add")== 0){
							toUpdate->stock += tempstock;
							break;
							
						}else if(strcmpi(temptype, "remove")== 0) {
							toUpdate->stock -= tempstock;
							break;
						}
						
					} while(true);
					
					puts("AFTER UPDATE");
					printf("Game title: %s \n", toUpdate->title);
					printf("Game genre: %s \n", toUpdate->genre);
					printf("Game email: %s \n", toUpdate->email);
					printf("Game stock: %s \n", toUpdate->stock);
					if(toUpdate->stock == 0){
						printf("%s is removed from warehouse.\n", toUpdate->title);
						root = deletion(root,toUpdate->title);
					}
				}
				
				break;			
			case 4:
				printf("EXIT");
				root = deleteAll(root);
				break;
		}
	} while(menu!=4);
	
	
	return 0;
}
