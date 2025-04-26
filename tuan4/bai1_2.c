#include<stdio.h> 

void insertionSort(float arr[], int n){
    int i, j;
    float last;
    for( i = 1; i < n; i++){
        last = arr[i];
        j = i;
        while ( j > 0 && arr[j - 1] > last){
            arr[j] = arr[j -1];
            j = j - 1; 
            arr[j] = last;
        }
    }
}
int binSearch(float arr[], int left, int right, float x){
    if (left > right) return -1; 
    int mid = (left + right) / 2;
    if (arr[mid] == x) return mid; 
    if (arr[mid] < x) return binSearch(arr, mid + 1, right, x); 
    if (arr[mid] > x) return binSearch(arr, left, mid - 1, x);
    return -1;
}
int main(){
    int n,i;
    printf("Nhap kich thuoc cua mang: ");   
    scanf("%d", &n); 
    if (n <=0){
        printf("Kic thuoc cua mang khong hop le\n");
        return 1; 
    }
    float arr[n];
    for(i = 0; i<n; i++){
        printf("Nhap phan tu thu %d: ", i + 1); 
        scanf("%f", &arr[i]); 
    }
    insertionSort(arr, n);
    printf("Mang sau khi sap xep la: \n");  
    for (i = 0; i<n;i++){
        printf("%f, ", arr[i]);
    }
    printf("\nNhap so can tim trong mang: ");
    float x;
    scanf("%f", &x); 
    int pos = binSearch(arr, 0, n - 1, x); 
    if (pos == -1){
        printf("Khong tim thay phan tu %f trong mang\n", x); 
    } else{
        printf("Phan tu %f nam o vi tri thu %d\n", x, pos + 1);
    }
    return 0;
}