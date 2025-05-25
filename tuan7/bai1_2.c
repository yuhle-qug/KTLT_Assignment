// Name:Lê Quang Huy
// Student ID: 20237344
// Class: 752580
// Project: lab 1
// Date: 25/05/2025
#include <stdio.h>
int removeDuplicate(char arr[], int n) {
    if (n == 0 || n == 1) {
        return n; 
    }

    int new_size = 0; 

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < new_size; j++) {
            if (arr[i] == arr[j]) {
                found = 1;
                break;
            }
        }

        if (found == 0) {
            arr[new_size] = arr[i];
            new_size++;
        }
    }
    return new_size; 
}

int main() {
    int n;
    int i;

    printf("Nhap so phan tu trong mang (chu cai hoac so): ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("So phan tu phai lon hon 0.\n");
        return 1; 
    }

    char arr[n]; 

    printf("Nhap cac phan tu ky tu cho mang:\n");
    for (i = 0; i < n; i++) {
        printf("Nhap phan tu thu %d: ", i + 1);
        scanf(" %c", &arr[i]);
    }

    printf("Mang truoc khi xoa phan tu trung: ");
    for (i = 0; i < n; i++) {
        printf("%c ", arr[i]);
    }
    printf("\n");

    int new_n = removeDuplicate(arr, n);

    printf("Mang sau khi xoa cac phan tu trung la: ");
    for (i = 0; i < new_n; i++) {
        printf("%c ", arr[i]);
    }

    return 0;
}