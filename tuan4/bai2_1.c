// Name:Lê Quang Huy
// Student ID: 20237344
// Class: 752580
// Project: lab 1
// Date: 27/04/2025
#include<stdio.h>
#include<conio.h>
 
int main() {
   int size, i;
   int *ptr;
 
   printf("\nNhap kich thuoc mang: ");
   scanf("%d", &size);
   int arr[size];
   ptr = &arr[size - 1];
   printf("Nhap mang\n");
   for (i = 0; i < size; i++) {
       printf("Phan tu thu %d la: ", i + 1);
       scanf("%d", &arr[i]);
   }
   printf("Mang vua nhap la: ");
   for (i = 0; i < size; i++){
        printf("%d ", arr[i]);
   }
 
   printf("\nHien thi cac phan tu mang theo chieu dao nguoc:");
   for (i = size - 1; i >= 0; i--) {
      printf("%d ", *ptr);
      ptr--;
   }
 
   return(0);
}