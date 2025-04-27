// Name:Lê Quang Huy
// Student ID: 20237344
// Class: 752580
// Project: lab 1
// Date: 27/04/2025
#include<stdio.h> 

void timkiem(float arr[], float x, int n){
    int i; 
    int found = 0;
    for(i = 0; i < n; i++){
        if(arr[i] == x){
            printf("Phan tu %f co trong mang, tai vi tri thu %d\n", x, i + 1);
            found = 1;
            break;
        }
    }
    if (found == 0){
        printf("Khong tim thay phan tu %f trong mang\n", x);
    }
}

void MinMax(float arr[], int n){
    int i; 
    float min = arr[0], max = arr[0];
    for (i = 0; i < n; i++){
        if(arr[i] < min){
            min = arr[i];
        }
        if(arr[i] > max){
            max = arr[i];
        }
    }
    printf("Phan tu nho nhat trong mang la %f\n", min);
    printf("Phan tu lon nhat trong mang la %f\n", max);
}

int main(){
    int n, i;
    
    printf("Nhap kich thuoc cua mang: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Kich thuoc mang phai lon hon 0!\n");
        return 1;
    }
    
    float arr[n];
    
    for (i = 0; i < n; i++){
        printf("Nhap phan tu thu %d: ", i + 1);
        scanf("%f", &arr[i]);
    }
    
    float x;
    printf("Nhap so can tim trong mang: ");
    scanf("%f", &x);
    
    timkiem(arr, x, n);
    MinMax(arr, n);
    
    return 0;
}