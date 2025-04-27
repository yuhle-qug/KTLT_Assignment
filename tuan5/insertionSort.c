// Name:Lê Quang Huy
// Student ID: 20237344
// Class: 752580
// Project: lab 1
// Date: 27/04/2025
#include<stdio.h> 
void insertionSort(float arr[], int n){
    int i; 
    int j;
    float last; 
    for(i = 0; i < n; i++){
        last = arr[i];
        j = i;
        while(arr[j-1] > last && j-1 >=0){
                arr[j] = arr[j-1];
                j = j -1;
                arr[j] = last; 
            }
        }
    printf("\nMang sau khi sap xep la: ");
    for(i = 0; i < n ; i++){
        printf("%f ", arr[i]);
    }
}
int main(){
    int i;
    int n;
    printf("Nhap kich thuoc cua mang: ");
    scanf("%d", &n);
    while(n<=0){
        printf("Kich thuoc mang khong hop le\n");
        printf("Nhap kich thuoc cua mang: ");
        scanf("%d", &n);
    }
    float arr[n];
    for ( i = 0; i < n; i++){
        printf("Nhap phan tu thu %d la: ", i+1);
        scanf("%f", &arr[i]);
    }
    printf("Mang da nhap la: ");
    for( i = 0; i<n; i++){
        printf("%f ", arr[i]);
    }
    insertionSort(arr, n);
}
