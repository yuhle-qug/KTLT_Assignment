// Name:Lê Quang Huy
// Student ID: 20237344
// Class: 752580
// Project: lab 1
// Date: 27/04/2025
#include <stdio.h>

void heapify(int arr[], int n, int i) {
    int largest = i; 

    int l = 2 * i + 1; 
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }

    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

// Main function to do heap sort
void heapSort(int arr[], int n) {

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0]; 
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}


// Driver's code
int main() {
    int i;
    int n;
    printf("Nhap kich thuoc cua mang: ");
    scanf("%d", &n);
    while(n<=0){
        printf("Kich thuoc mang khong hop le\n");
        printf("Nhap kich thuoc cua mang: ");
        scanf("%d", &n);
    }
    int arr[n];
    for ( i = 0; i < n; i++){
        printf("Nhap phan tu thu %d la: ", i+1);
        scanf("%d", &arr[i]);
    }
    printf("Mang da nhap la: ");
    for( i = 0; i<n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    heapSort(arr, n);
    printf("Mang sau khi sap xep bang heapSort la: ");

    for ( i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
}