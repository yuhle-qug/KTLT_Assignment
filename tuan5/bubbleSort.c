#include<stdio.h> 
#include <stdbool.h>

void bubbleSort(float arr[], int n){
    int i; 
    int j; 
    bool swapped;
    //input: 3 2 1 5 
    //n = 4
    for (i = 0; i < n-1; i++){
        swapped = false; 
        for (j = 0; j < n - i - 1; j++){
            if (arr[j] > arr[j+1]){
                float tmp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = tmp; 
                swapped = true;
            }
        }
        if (swapped == false){
            break;
        }
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
    bubbleSort(arr, n);
    printf("\nMang sau khi sap xep la: "); 
    for(i = 0; i < n ; i++){
        printf("%f ", arr[i]);
    }
    printf("\n");
}