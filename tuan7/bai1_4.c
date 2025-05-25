// Name:Lê Quang Huy
// Student ID: 20237344
// Class: 752580
// Project: lab 1
// Date: 25/05/2025
#include<stdio.h>

// Hàm max giữ nguyên, rất tốt
float max(float a, float b){
    if (a > b){
        return a;  
    }else{
        return b;
    }
}

void findMax(float arr[], int n, int *found_start, int *found_end){
    int i; 
    float maxSum = 0; 
    float currentSum = 0;
    int current_start_index = 0; 

    *found_start = -1;
    *found_end = -1;   

    for (i = 0; i < n; i++){
        if (arr[i] > 0){
            if (currentSum == 0) { 
                current_start_index = i;
            }
            currentSum += arr[i]; 
        } else { 
            if (currentSum > maxSum) {
                maxSum = currentSum;
                *found_start = current_start_index;
                *found_end = i - 1; 
            }
            currentSum = 0; 
        }
    }

    if (currentSum > maxSum) {
        maxSum = currentSum;
        *found_start = current_start_index;
        *found_end = n - 1;
    }
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
    printf("Nhap cac phan tu (so thuc) cho mang:\n");
    for (i = 0; i < n; i++) {
        printf("Nhap phan tu thu %d: ", i + 1);
        scanf("%f", &arr[i]); 
    }

    int sub_start, sub_end;
    findMax(arr, n, &sub_start, &sub_end);

    if (sub_start != -1 && sub_end != -1) { 
        printf("Day con toan duong co tong lon nhat la: ");
        for(i = sub_start; i <= sub_end; i++){
            printf("%f ", arr[i]); 
        }
        printf("\n");
    } else {
        printf("Khong tim thay day con toan duong nao trong mang.\n");
    }
    
    return 0;
}