#include<stdio.h>
#include<stdlib.h>

struct data{
	int id;
	int age;
	int h;
	struct data* left;
	struct data* right;
};

struct data* create(int id,int age){
	struct data* curr = (struct data*)malloc(sizeof(data));
	curr-> id = id;
	curr->age = age;
	curr->left = curr->right = NULL;
	curr->h=1;
	
	return curr;
}

int max(int a, int b){
	if(a>b) return a;
	return b;
}

int getHeight(struct data* temp){
	if(temp == NULL){
		return 0;
	}else {
		return temp->h;
	}
}

int getBalance(struct data* temp){
	if(temp == NULL){
		return 0;
	} else {
		return getHeight(temp->left)-getHeight(temp->right);
	}
}

struct data* rotateL(struct data* temp){
	struct data* tempR = temp->right;
	struct data* tempRL = temp->left;
	
	tempR->left = temp;
	temp->right = tempRL;
	
	temp->h = 1 + max(getHeight(temp->left),getHeight(temp->right));
	tempR->h = 1 + max(getHeight(tempR->left),getHeight(tempR->right));
	
	return tempR;
}

struct data* rotateR(struct data* temp){
	struct data* tempL = temp->left;
	struct data* tempLR = temp->right;
	
	tempL->right = temp;
	temp->left = tempLR;
	
	temp->h = 1 + max(getHeight(temp->left),getHeight(temp->right));
	tempL->h = 1 + max(getHeight(tempL->left),getHeight(tempL->right));
	
	return tempL;
}

struct data* insert(struct data* temp,int id, int age){
	if(temp == NULL){
		return create(id,age);
	} else if(id < temp->id){
		temp->left=insert(temp->left,id,age);
	}else if(id > temp->id){
		temp->right=insert(temp->right,id,age);
	}
	
	temp->h = 1 + max(getHeight(temp->left),getHeight(temp->right));
	
	int balance = getBalance(temp);
	
	if(balance < -1 && id < temp->right->id){
		return rotateL(temp);
	}
	
	if(balance < -1 && id > temp->right->id){		
		temp->right = rotateR(temp->right);
		return rotateL(temp);
	}
	
	if(balance > 1 && id < temp->left->id){
		return rotateR(temp);
	}
	
	if(balance > 1 && id > temp->left->id){		
		temp->left = rotateL(temp->left);
		return rotateR(temp);
	}
	
	return temp;
}

void pre(struct data* temp){
	if(temp != NULL){
		printf("%d - %d\n", temp->id, temp->h);
		pre(temp->left);
		pre(temp->right);
	} 
}

int main(){
	
	struct data* root = NULL;
	root = insert(root,30,10);
	pre(root);
	puts("==================");
	
	root = insert(root,20,20);
	pre(root);
	puts("==================");
	
	root = insert(root,15,30);
	pre(root);
	puts("==================");
	
	
	return 0;
}
