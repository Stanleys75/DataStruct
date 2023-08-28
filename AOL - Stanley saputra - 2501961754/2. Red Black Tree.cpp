#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

struct node{
    int number; 
    int colour; 
    
    node *parent;
	node *right; 
	node *left; 
};
node *root = NULL;
 
struct node* RBtree(struct node* curr,struct node* curr2){
	if(curr == NULL){
		return curr2;
	}
    else if (curr2->number < curr->number){
        curr->left = RBtree(curr->left, curr2);
        curr->left->parent = curr;
    }
    else if (curr2->number > curr->number){
        curr->right = RBtree(curr->right, curr2);
    	curr->right->parent = curr;
    }
    return curr;
}
 
void rightRotate(struct node* temp)
{
    node* left = temp->left;
    left->parent = temp->parent;
    temp->left = left->right;
    
    if(temp->left){
    	temp->left->parent = temp;
	}
    else if(temp->parent==NULL){
    	root = left;
	} 
    else if(temp == temp->parent->left){
    	temp->parent->left = left;
	}
    else{
        temp->parent->right = left;	
	}

    left->right = temp;
    temp->parent = left;
}

void leftRotate(struct node* temp){
	node* right = temp->right;
    temp->right = right->left;
    right->parent = temp->parent;
    
    if(temp->right){
   		temp->right->parent = temp;	
	}
	else if(temp == temp->parent->left){
    	temp->parent->left = right;
	} 
    else if(temp->parent==NULL){
        root = right;	
	} 
    else{
        temp->parent->right = right;
	}
	
    right->left = temp;
    temp->parent = right;
}
 
void change(node* root, node* child){
    node* head = NULL;
    node* temp = NULL;
 
    while((child->colour != 0) && (child != root)&& (child->parent->colour == 1)){
        head = child->parent;
        temp = child->parent->parent;
 
        if(head == temp->left){
            node* sibling = temp->right;
            if (sibling != NULL && sibling->colour == 1){
                temp->colour = 1;
                head->colour = 0;
                sibling->colour = 0;
                child = temp;
            }
            else{
                if(child == head->right){
                    leftRotate(head);
                    child = head;
                    head = child->parent;
                }
                int recolor = head->colour;
                rightRotate(temp);
                head->colour = temp->colour;
                temp->colour = recolor;
                child = head;
                
            }
        }
        
        else{
            node* sibling = temp->left;
            	if((sibling != NULL) && (sibling->colour == 1)){
                	temp->colour = 1;
                	head->colour = sibling->colour = 0;
               		child = temp;
            	}
            	else{
              		if(child == head->left){
                    	rightRotate(head);
                    	child = head;
                    	head = child->parent;
                	}
					else{
						int recolor = head->colour;
						leftRotate(temp);
                		head->colour = temp->colour;
                		temp->colour = recolor;
               			child = head;
               			
					}
            	}
        	}
    	}
    root->colour = 0;
}

void vieworder(node* temp){
    if (temp != NULL){
        vieworder(temp->left);
    	printf("%d ", temp->number);
    	vieworder(temp->right);	
    	
	}
	
}
 
int main(){
	
    int RBT[100] = {41,22,5,51,48,29,18,21,45,3};
	printf("Stanley saputra - 2501961754\n\n");
    for (int i = 0; i < 10; i++){
        node* curr = (struct node*)malloc(sizeof(struct node));
        curr->right = curr->left = curr->parent = NULL;
        curr->number = RBT[i];
        curr->colour = 1;

        root = RBtree(root, curr);
        change(root, curr);
        
    }
    printf("In order Traversal of Created Tree\n");
    
    vieworder(root);
 
    return 0;
}
