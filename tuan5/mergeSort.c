// Name:Lê Quang Huy
// Student ID: 20237344
// Class: 752580
// Project: lab 1
// Date: 27/04/2025
#include<stdio.h> 
void merge(int arr[], int l, int m , int r){
    int i,j,k;
    //kich thuoc 2 mang L va R
    int n1 = m - l +1; 
    int n2 = r - m;
    //tao 2 mang L va R 
    int L[n1], R[n2];
    // chia mang arr thanh 2 mang L va R 
    // i = n1 - 1 => l + i = l + n1 - 1 = l + m - l + 1 - 1 = m
    for (i = 0; i < n1; i++){
        L[i] = arr[l + i];
    }
    // j = n2 - 1 => m + 1 + j = m + 1 + n2 -1 = m + n2 = m + r - m = r   
    for (j = 0; j < n2; j++){
        R[j] = arr[m + 1 + j];
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    } 
    
}
void mergeSort(int arr[], int l, int r){
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}
int main() {
    int i,size; 
    printf("Nhap kich thuoc mang: ");
    scanf("%d", &size);
    while(size<=0){
        printf("Kich thuoc mang khong hop le\n");
        printf("Nhap kich thuoc cua mang: ");
        scanf("%d", &size);
    }
    int arr[size];
    printf("Nhap cac phan tu trong mang\n");
    for ( i = 0; i < size; i++){
        printf("Nhap phan tu thu %d la: ", i + 1);
        scanf("%d", &arr[i]);
    }
    printf("Mang vua nhap la: ");
    for ( i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    mergeSort(arr, 0, size - 1);
    printf("Mang sau khi sap xep bang mergeSort la: ");

    for ( i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
}