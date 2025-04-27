// Name:Lê Quang Huy
// Student ID: 20237344
// Class: 752580
// Project: lab 1
// Date: 27/04/2025
#include<stdio.h> 
#define MAX_SIZE 100

void matrixTimes(int n, int m, int q, float arr1[][MAX_SIZE],float arr2[][MAX_SIZE],float result[][MAX_SIZE]){
    int i, j, k;
    for ( i = 0; i < n; i++){
        for ( j = 0; j < q; j++){
            result[i][j] = 0;
            for (k = 0; k < m; k++){
                result[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }
    printf("Tich hai ma tran la: \n");
    for (i = 0; i < n; i++) {
        printf("[  ");
        for (j = 0; j < q; j++) {
            printf("%f ", result[i][j]);
        }
        printf("]\n");
    }
}
int main(){
    int n, p, q, m;
    float arr1[MAX_SIZE][MAX_SIZE];
    float arr2[MAX_SIZE][MAX_SIZE];
    float result[MAX_SIZE][MAX_SIZE];
    int i, j;
    
    printf("Nhap kich thuoc cua ma tran: \n");
    printf("Nhap so hang cua ma tran 1: ");
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
    printf("Nhap so hang cua ma tran 2: ");
    scanf("%d", &p);
    while (p <= 0 || p > MAX_SIZE) {
        printf("So hang khong hop le, vui long nhap lai: ");
        scanf("%d", &p);
    }
    
    printf("Nhap so cot: ");    
    scanf("%d", &q);
    while (q <= 0 || q > MAX_SIZE) {
        printf("So cot khong hop le, vui long nhap lai: ");
        scanf("%d", &q);    
    }
    printf("Nhap ma tran 2: \n");
    for (i = 0; i < p; i++) {
        for (j = 0; j < q; j++) {
            printf("Nhap phan tu [%d][%d]: ", i+1, j+1);
            scanf("%f", &arr2[i][j]);
        }
    }
    
    printf("Ma tran 2:\n");
    for (i = 0; i < p; i++) {
        for (j = 0; j < q; j++) {
            printf("%f ", arr2[i][j]);
        }
        printf("\n");
    }
    if( m != p){
        printf("2 ma tran nay khong nhan duoc voi nhau");

    }else{
        matrixTimes(n,m,q, arr1, arr2, result);
    }
}