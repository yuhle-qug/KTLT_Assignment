// Name:Lê Quang Huy
// Student ID: 20237344
// Class: 752580
// Project: lab 1
// Date: 25/05/2025
#include <stdio.h>
#include <stdlib.h> 


typedef struct Node {
    int data;           
    struct Node *next;  
} Node;

// tao node moi 
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Loi cap phat bo nho!\n");
        exit(1); 
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// them node moi o dau danh sach
void addToHead(Node** head_ref, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head_ref;
    *head_ref = newNode;
    printf("Da them %d vao dau danh sach.\n", data);
}

// them vao cuoi danh sach 
void addToTail(Node** head_ref, int data) {
    Node* newNode = createNode(data);
    if (*head_ref == NULL) { // Nếu danh sách rỗng
        *head_ref = newNode;
        printf("Da them %d vao cuoi danh sach (danh sach rong).\n", data);
        return;
    }
    Node* temp = *head_ref;
    while (temp->next != NULL) { // Duyệt đến nút cuối cùng
        temp = temp->next;
    }
    temp->next = newNode;
    printf("Da them %d vao cuoi danh sach.\n", data);
}

// them node moi sau node co gia tri cho truoc
void insertAfterValue(Node** head_ref, int prev_value, int new_data) {
    Node* temp = *head_ref;
    while (temp != NULL && temp->data != prev_value) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Khong tim thay nut co gia tri %d de them vao sau.\n", prev_value);
        return;
    }

    Node* newNode = createNode(new_data);
    newNode->next = temp->next;
    temp->next = newNode;
    printf("Da them %d vao sau nut co gia tri %d.\n", new_data, prev_value);
}


// sua gia tri 
int updateNode(Node* head, int old_value, int new_value) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == old_value) {
            temp->data = new_value;
            printf("Da cap nhat nut co gia tri %d thanh %d.\n", old_value, new_value);
            return 1; // Thành công
        }
        temp = temp->next;
    }
    printf("Khong tim thay nut co gia tri %d de cap nhat.\n", old_value);
    return 0; // Không tìm thấy
}

// xoa node o dau danh sach
void deleteFromHead(Node** head_ref) {
    if (*head_ref == NULL) {
        printf("Danh sach rong, khong the xoa.\n");
        return;
    }
    Node* temp = *head_ref;
    *head_ref = (*head_ref)->next;
    printf("Da xoa nut %d o dau danh sach.\n", temp->data);
    free(temp);
}
// Xoa node o cuoi danh sach 
void deleteFromTail(Node** head_ref) {
    if (*head_ref == NULL) {
        printf("Danh sach rong, khong the xoa.\n");
        return;
    }
    if ((*head_ref)->next == NULL) { // Danh sách chỉ có một nút
        printf("Da xoa nut %d o cuoi danh sach (cung la dau).\n", (*head_ref)->data);
        free(*head_ref);
        *head_ref = NULL;
        return;
    }
    Node* temp = *head_ref;
    Node* prev = NULL;
    while (temp->next != NULL) { // Duyệt đến nút cuối cùng
        prev = temp;
        temp = temp->next;
    }
    prev->next = NULL; // Nút kế cuối trỏ tới NULL
    printf("Da xoa nut %d o cuoi danh sach.\n", temp->data);
    free(temp);
}

// Xoa node co gia tri cho truoc
void deleteNodeByValue(Node** head_ref, int key) {
    Node* temp = *head_ref;
    Node* prev = NULL;

    // TH1: nam o dau danh sach
    if (temp != NULL && temp->data == key) {
        *head_ref = temp->next;
        printf("Da xoa nut co gia tri %d (o dau).\n", key);
        free(temp);
        return;
    }

    
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Khong tim thay nut co gia tri %d de xoa.\n", key);
        return;
    }

    prev->next = temp->next;
    printf("Da xoa nut co gia tri %d.\n", key);
    free(temp); 
}


// tim mot node co gia tri cho truoc 
Node* searchNode(Node* head, int key) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == key) {
            return temp; 
        }
        temp = temp->next;
    }
    return NULL; 
}

// In danh sach 
void printList(Node* head) {
    if (head == NULL) {
        printf("Danh sach rong.\n");
        return;
    }
    printf("Danh sach hien tai: ");
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeList(Node** head_ref) {
    Node* current = *head_ref;
    Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *head_ref = NULL; 
}


int main() {
    Node* head = NULL; 
    int choice, data, old_val, new_val, prev_val;
    Node* searchResult = NULL;

    do {
        printf("\n----- MENU QUAN LY DANH SACH -----\n");
        printf("1. Them phan tu vao dau danh sach\n");
        printf("2. Them phan tu vao cuoi danh sach\n");
        printf("3. Them phan tu vao sau mot gia tri\n");
        printf("4. Sua phan tu\n");
        printf("5. Xoa phan tu o dau danh sach\n");
        printf("6. Xoa phan tu o cuoi danh sach\n");
        printf("7. Xoa phan tu theo gia tri\n");
        printf("8. Tim kiem phan tu\n");
        printf("9. In danh sach\n");
        printf("0. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap gia tri can them vao dau: ");
                scanf("%d", &data);
                addToHead(&head, data);
                break;
            case 2:
                printf("Nhap gia tri can them vao cuoi: ");
                scanf("%d", &data);
                addToTail(&head, data);
                break;
            case 3:
                printf("Nhap gia tri cua nut dung truoc: ");
                scanf("%d", &prev_val);
                printf("Nhap gia tri can them: ");
                scanf("%d", &data);
                insertAfterValue(&head, prev_val, data);
                break;
            case 4:
                printf("Nhap gia tri can sua: ");
                scanf("%d", &old_val);
                printf("Nhap gia tri moi: ");
                scanf("%d", &new_val);
                updateNode(head, old_val, new_val);
                break;
            case 5:
                deleteFromHead(&head);
                break;
            case 6:
                deleteFromTail(&head);
                break;
            case 7:
                printf("Nhap gia tri can xoa: ");
                scanf("%d", &data);
                deleteNodeByValue(&head, data);
                break;
            case 8:
                printf("Nhap gia tri can tim: ");
                scanf("%d", &data);
                searchResult = searchNode(head, data);
                if (searchResult != NULL) {
                    printf("Tim thay phan tu co gia tri %d tai dia chi %p.\n", data, (void*)searchResult);
                } else {
                    printf("Khong tim thay phan tu co gia tri %d.\n", data);
                }
                break;
            case 9:
                printList(head);
                break;
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (choice != 0);

    freeList(&head);

    return 0;
}