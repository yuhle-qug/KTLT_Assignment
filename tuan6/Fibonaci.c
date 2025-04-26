#include<stdio.h> 

int Fibonaci(int n){
    if (n==0 || n==1){
        return n;
    }
    return Fibonaci(n-1) + Fibonaci(n-2);
}
int main(){
    int n;
    printf("Nhap so n:"); 
    scanf("%d", &n);
    while(n<0){
        printf("Nhap so n:"); 
        scanf("%d", &n);    
    }
    Fibonaci(n);
    printf("Fibonaci(%d) = %d", n, Fibonaci(n));
}
