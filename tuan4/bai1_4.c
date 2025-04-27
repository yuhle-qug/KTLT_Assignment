// Name:Lê Quang Huy
// Student ID: 20237344
// Class: 752580
// Project: lab 1
// Date: 27/04/2025
#include<stdio.h> 

void NumAppend(int arr[],int n){
    int i, j; 
    int max = 100;
    int tmp[max];
    for (i = 0; i < max; i++){
        tmp[i] = 0;     
    }
    for (i = 0; i < n; i++){
        if(arr[i] > 0 && arr[i] < max){
            tmp[arr[i]]++;
        }
        
    }
    for( i = 0; i < max;i++ ){
        if(tmp[i] >0){
            printf("\nPhan tu %d xuat hien %d lan", i, tmp[i]);
        }
    }
    int maxNum = tmp[0];
    int ele = 0;
    for (i = 1; i < max; i++){
        if (tmp[i] > maxNum){
            maxNum = tmp[i];
            ele = i;
        }
    }
    printf("\nPhan tu %d xuat hien nhieu nhat voi %d lan", ele, maxNum);
}
int main(){
    int n; 
    int i;
    printf("Nhap kich thuoc cua mang: ");
    scanf("%d", &n);
    int arr[n];
    for (i = 0; i<n; i++){
        printf("Nhap phan tu thu %d: ", i+1);
        scanf("%d", &arr[i]);
        if(arr[i] < 0 || arr[i] > 100){
            printf("Phan tu khong hop le, vui long nhap lai: ");
            i--;
        }
    }
    printf("Mang da nhap la: "); 
    for (i = 0; i<n; i++){
        printf("%d ", arr[i]);
    }
    NumAppend(arr, n);
    return 0;
}