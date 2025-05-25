// Name:Lê Quang Huy
// Student ID: 20237344
// Class: 752580
// Project: lab 1
// Date: 25/05/2025
#include<stdio.h> 
#include<math.h>

float avgDistance(float arr[], int n){
    int i,j;
    float sumDistance = 0;
    int count = 0;
    if (n <2){
        return 0;
    }
    for (i = 0; i < n-1; i++){
        for (j = i + 1; j < n; j++){
            sumDistance += fabs(arr[i] - arr[j]);
            count ++;
        }
    }
    if (count == 0){
        return 0;
    }
    return sumDistance / count;
}
int main(){
    int n;
    int i;
    printf("Nhap so phan tu trong mang: ");
    scanf("%d", &n); 

    if (n <= 0) {
        printf("So phan tu phai lon hon 0.\n");
        return 1; 
    }

    float arr[n];
    for (int i = 0; i < n; i++){
        printf("Nhap phan tu thu %d: ", i + 1);
        scanf("%f", &arr[i]);
    }
    printf("Trung binh cong khoang cach giua cac phan tu trong mang la: %f", avgDistance(arr, n));
}