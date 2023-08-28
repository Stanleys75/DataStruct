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

int main(){
	char item1[100];
	
	do{
		printf("Input item name [10 - 35 characters, min. 2 words, capital]: ");
		scanf(" %[^\n]", item1);
	} while (validasi(item1)==false);
}
