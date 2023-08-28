#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data{
	int id;
	char name[100];
	struct data* left;
	struct data* right;	
};

struct data* create(int id,char name[]){
	struct data* curr = (data*)malloc(sizeof(data));
	curr->id = id;
	curr->left = curr->right = NULL;
	strcpy(curr->name , name);
	return curr;
}

struct data* insert(struct data* temp, struct data* curr){
	
	if(temp == NULL){
		return curr;
	} else if (curr->id < temp->id){
		temp->left = insert(temp->left,curr);
	} else if (curr->id > temp->id){
		temp->right= insert(temp->right,curr);
	}
	
	return temp;
}

struct data* search(struct data* temp,int id){
	if(temp == NULL){
		return NULL;
	}
	if(temp -> id == id){
		return temp;
	} else if (id < temp->id){
		return search(temp->left,id);
	} else if (id > temp->id){
		return search(temp->right,id);
	}
	
}

struct data* update(struct data* temp,int currentID, char name[]){
	struct data* myAccount = search(temp,currentID);
	if(myAccount == NULL){
		return NULL;
	}
	strcpy(myAccount->name , name);
	
	
	return myAccount;

}

//preorder
void pre(struct data* temp){
	if(temp == NULL){
		return;
	}
	printf("%10d %20s\n", temp->id,temp->name);
	pre(temp->left);
	pre(temp->right);
}	
//inorder
void in(struct data* temp){
	if(temp == NULL){
		return;
	}
	in(temp->left);
	printf("%10d %20s\n", temp->id,temp->name);
	in(temp->right);
}	
//postorder
void post(struct data* temp){
	if(temp == NULL){
		return;
	}
	post(temp->left);
	post(temp->right);
	printf("%10d %20s\n", temp->id,temp->name);
}	

struct data* pop(struct data* temp ,int deleteId){
	
	if (temp == NULL){
		return NULL;
	}else if (temp->id < deleteId){
		temp->right = pop(temp->right, deleteId);
	} else if(temp->id > deleteId){
		temp->left = pop(temp->left, deleteId);
	} else if (temp->id == deleteId){
		
		// jika tidak punya anak sama sekali
		if (temp->left == NULL && temp->right ==NULL){
			free(temp);
			temp = NULL;
			
		// jika dia punya satu anak
		} else if(temp->left == NULL || temp->right == NULL){
			struct data* curr;
			
			// jika anaknya dikiri
			if(temp->left!=NULL){
				curr = temp->left;
			} else{
				curr = temp->right;
			}
			
			*temp = *curr; // copy value
			free(curr);
			
		// jika punya 2 anak
		} else {
			//successor = node paling kecil dari anak kanan
			
			struct data* curr;
			
//			curr = temp->right;
//			while(curr->left != NULL){
//				curr = curr->left;
//			}
			
			//predecessor = node paling besar dari anak kiri
			
			curr = temp->left;
			while(curr->right != NULL){
				curr = curr -> right;
			}

			// beda sama yang copy pointer yang ini gak ambil anak anaknya
			temp -> id = curr -> id;
			strcpy(temp->name , curr->name);
			
			//successor
//			temp->right = pop(temp->right,curr->id);
			
			//predecessor
			
			temp -> left = pop(temp->left , curr->id);

		}
	}
	
	return temp;
}

struct data* popAll(struct data* temp){
	
	while(temp != NULL){
		temp = pop(temp, temp->id);
	}
	
	return temp;
}
int main(){
	struct data* root = NULL;
	struct data* orang1 = create(100,"JE");
	struct data* orang2 = create(50,"CC");
	struct data* orang3= create(75,"EA");
	struct data* orang4= create(40,"SS");
	struct data* orang5= create(150,"AL");
	struct data* orang6= create(125,"AD");
	struct data* orang7= create(175,"DW");
	
	root = insert(root,orang1);
	root = insert(root,orang2);
	root = insert(root,orang3);
	root = insert(root,orang4);
	root = insert(root,orang5);
	root = insert(root,orang6);
	root = insert(root,orang7);
//	printf("POST ____________\n");
//	post(root);
//	printf("\n");
//	printf("PRE ______________\n");
//	pre(root);
//	printf("\n");
	printf("IN ______________\n");
	in(root);
	
	
//	struct data* myID = search(root, 23);
//	if(myID == NULL){
//		printf("Tydak ketemu dek");
//	} else {
//		puts("HEHE its me");
//	}
//	
//	
//	puts("================================");
//	update(root, 150, "CT");
	printf("\n");
//	root = pop (root, 175);
//	root = pop (root, 150);
	root = pop (root, 100);
	pre(root);
	
	
	root = popAll(root);
	printf("Hasil akhir:");
	pre(root);
	return 0;
}
