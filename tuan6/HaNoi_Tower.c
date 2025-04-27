// Name:Lê Quang Huy
// Student ID: 20237344
// Class: 752580
// Project: lab 1
// Date: 27/04/2025
#include<stdio.h>
void Tower(int n , char a, char b, char c ){
	if(n==1){
		printf("t%c -> %c\n",a,c);
		return;
	}
	Tower(n-1,a,c,b);
	Tower(1,a,b,c);
	Tower(n-1,b,a,c);
	}
int main(){
	char a='A', b='B', c='C';
	int n;
	printf("Nhap n: ");
	scanf("%d",&n);
	Tower(n,a,b,c);
}