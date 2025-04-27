// Name:Lê Quang Huy
// Student ID: 20237344
// Class: 752580
// Project: lab 1
// Date: 27/04/2025
#include<stdio.h> 

void nhanVoHuong(int n, const int arr1[], const int arr2[]){
    int i; 
    int k;
    int result;
    for ( i = 0; i< n; i++){
        result += arr1[i]*arr2[i];
    }
    printf("Tich vo huong cua vecto A va B la: ");
    printf("%d", result);
    printf("\n");
}
void nhanCoHuong(const int arr1[], const int arr2[]){
    int i; 
    int result[3];
    result[0] = arr1[1] * arr2[2] - arr1[2] * arr2[1];
    result[1] = arr1[2] * arr2[0] - arr1[0] * arr2[2];
    result[2] = arr1[0] * arr2[1] - arr1[1] * arr2[0];
    printf("Tich co huong cua vecto 3 chieu A va B la: ");
    for (i = 0; i < 3; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");
}
int main(){
    int n;
    int i;

    printf("So chieu cua vecto la: ");
    scanf("%d", &n);

    int arr1[n];
    int arr2[n];

    printf("Nhap vecto A\n");
    for (i = 0; i < n; i++) {
        printf("Phan tu thu %d la: ", i + 1);
        scanf("%d", &arr1[i]);
    }

    printf("Vecto A: ( ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr1[i]);
    }
    printf(")\n");

    printf("Nhap vecto B\n");
    for (i = 0; i < n; i++) {
        printf("Phan tu thu %d la: ", i + 1);
        scanf("%d", &arr2[i]);
    }
    printf("Vecto B: ( ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr2[i]);
    }
    printf(")\n");
    if(n==3){
        nhanCoHuong(arr1, arr2);
    }
    nhanVoHuong(n, arr1, arr2);
    return 0; 
}