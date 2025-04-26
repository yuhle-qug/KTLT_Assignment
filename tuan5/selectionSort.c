#include<stdio.h> 
void selectionSort(float arr[], int n){
    int i; 
    int j; 
    int inx;
    int tmp;
    for ( i = 0; i<n-1; i++){
        inx = i;
        for(j = i+1; j <n; j++){
            if(arr[j] < arr[inx]){
                inx = j;
            }
        }
        tmp = arr[i];
        arr[i]= arr[inx];
        arr[inx]= tmp;
    }
    printf("\nMang sau khi sap xep la: ");
    for(i = 0; i<n; i++){
        printf("%f ", arr[i]);
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
    selectionSort(arr, n);
    return 0;

}