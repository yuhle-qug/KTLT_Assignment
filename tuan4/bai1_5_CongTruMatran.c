#include <stdio.h>
#define MAX_SIZE 100 

void matrixPlus(int n, int m, float arr1[][MAX_SIZE], float arr2[][MAX_SIZE], float result[][MAX_SIZE]) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            result[i][j] = arr1[i][j] + arr2[i][j];
        }
    }
    
    printf("Tong hai ma tran la: \n");
    for (i = 0; i < n; i++) {
        printf("[  ");
        for (j = 0; j < m; j++) {
            printf("%f ", result[i][j]);
        }
        printf("]\n");
    }
}
void matrixMinus(int n, int m, float arr1[][MAX_SIZE], float arr2[][MAX_SIZE], float result[][MAX_SIZE]) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            result[i][j] = arr1[i][j] - arr2[i][j];
        }
    }
    
    printf("Hieu hai ma tran la: \n");
    for (i = 0; i < n; i++) {
        printf("[  ");
        for (j = 0; j < m; j++) {
            printf("%f ", result[i][j]);
        }
        printf("]\n");
    }
}
void matrixTimes(int n, int m, float arr1[][MAX_SIZE], float arr2[][MAX_SIZE], float result[][MAX_SIZE]) {
    int i, j; 
    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++){
            
        }
    }
}

int main() {
    int n, m;
    float arr1[MAX_SIZE][MAX_SIZE];
    float arr2[MAX_SIZE][MAX_SIZE];
    float result[MAX_SIZE][MAX_SIZE];
    int i, j;
    
    printf("Nhap kich thuoc cua ma tran: \n");
    printf("Nhap so hang: ");
    scanf("%d", &n);
    while (n <= 0 || n > MAX_SIZE) {
        printf("So hang khong hop le, vui long nhap lai: ");
        scanf("%d", &n);
    }
    
    printf("Nhap so cot: ");    
    scanf("%d", &m);
    while (m <= 0 || m > MAX_SIZE) {
        printf("So cot khong hop le, vui long nhap lai: ");
        scanf("%d", &m);    
    }
    
    printf("Nhap ma tran 1: \n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("Nhap phan tu [%d][%d]: ", i+1, j+1);
            scanf("%f", &arr1[i][j]);
        }
    }
    
    printf("Ma tran 1:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%f ", arr1[i][j]);
        }
        printf("\n");
    }
    
    printf("Nhap ma tran 2: \n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("Nhap phan tu [%d][%d]: ", i+1, j+1);
            scanf("%f", &arr2[i][j]);
        }
    }
    
    printf("Ma tran 2:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%f ", arr2[i][j]);
        }
        printf("\n");
    }
    
    matrixPlus(n, m, arr1, arr2, result);
    
    return 0;
}