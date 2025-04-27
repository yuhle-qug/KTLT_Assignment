#include <stdio.h>

void cong(int n, const int arr1[], const int arr2[]) {
    int i;
    int result[n]; 
    for (i = 0; i < n; i++) {
        result[i] = arr1[i] + arr2[i];
    }

    printf("Tong cua 2 vecto A va B la: ( ");
    for (i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    printf(")\n");
}
void hieu(int n, const int arr1[], const int arr2[]) {
    int i;
    int result[n]; 
    for (i = 0; i < n; i++) {
        result[i] = arr1[i] - arr2[i];
    }

    printf("Hieu cua 2 vecto A va B la: ( ");
    for (i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    printf(")\n");
}

int main() {
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

    cong(n, arr1, arr2);
    hieu(n, arr1, arr2);

    return 0;
}
