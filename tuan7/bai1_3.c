// Name:Lê Quang Huy
// Student ID: 20237344
// Class: 752580
// Project: lab 1
// Date: 25/05/2025
#include <stdio.h>
#include <math.h> 

int findChildArrayWithSumM(float arr[], int n_param, float M, int *found_start, int *found_end) {

    for (int i = 0; i < n_param; i++) {
        float current_sum = 0;
        for (int j = i; j < n_param; j++) { 
            current_sum += arr[j]; //
            if (current_sum == M) {
                *found_start = i;
                *found_end = j;
                return 1; //tim duoc mang con thoa man 
            }
        }
    }
    return 0;
}

int main() {
    int n;
    int i;

    printf("Nhap so phan tu trong mang: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("So phan tu phai lon hon 0.\n");
        return 1;
    }

    float arr[n]; 
    printf("Nhap cac phan tu (so thuc) cho mang:\n");
    for (i = 0; i < n; i++) {
        printf("Nhap phan tu thu %d: ", i + 1);
        scanf("%f", &arr[i]); 
    }

    float M;
    printf("Nhap gia tri M cho truoc: ");
    scanf("%f", &M);

    int sub_start, sub_end;
    if (findChildArrayWithSumM(arr, n, M, &sub_start, &sub_end)) {
        printf("Tim thay mang con co tong bang %f la: ", M); 
        for (i = sub_start; i <= sub_end; i++) {
            printf("%f ", arr[i]); 
        }
        printf("\n");
    } else {
        printf("Khong tim thay mang con nao co tong bang %.2f.\n", M);
    }
    
    return 0;
}