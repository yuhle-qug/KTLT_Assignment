// Name:Lê Quang Huy
// Student ID: 20237344
// Class: 752580
// Project: lab 1
// Date: 25/05/2025
#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int key;            
    struct Node *left;  
    struct Node *right; 
} Node;

// tao mot nut moi voi gia tri key
Node* createNode(int key);
// chen mot nut moi vao cay nhi phan tim kiem
Node* insertNode(Node* root, int key);
// tim kiem mot nut co gia tri key trong cay
Node* searchNode(Node* root, int key);
// tim nut co gia tri nho nhat trong cay con
Node* findMinNode(Node* node); 
// xoa mot nut co gia tri key khoi cay
Node* deleteNode(Node* root, int key);
// dem so nut trong cay
int countNodes(Node* root);
// duyet cay theo thu tu trung tu va in ra cac gia tri
void inorderTraversal(Node* root); 
// giai phong bo nho cua cay
void freeTree(Node* root); 


// tao mot nut moi voi gia tri key
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Loi: Khong the cap phat bo nho!\n");
        exit(1);
    }
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


// chen mot nut moi vao cay nhi phan tim kiem
Node* insertNode(Node* root, int key) {
    
    if (root == NULL) {
        return createNode(key);
    }

   
    if (key < root->key) {
        root->left = insertNode(root->left, key);
    } else if (key > root->key) {
        root->right = insertNode(root->right, key);
    }
    

    return root; 
}


// tim kiem mot nut co gia tri key trong cay
Node* searchNode(Node* root, int key) {
    
    if (root == NULL || root->key == key) {
        return root;
    }

    
    if (key > root->key) {
        return searchNode(root->right, key);
    }

    return searchNode(root->left, key);
}


// tim nut co gia tri nho nhat trong cay con
Node* findMinNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}


// xoa mot nut co gia tri key khoi cay
Node* deleteNode(Node* root, int key) {
    if (root == NULL) {
        return root;
    }
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = findMinNode(root->right);

        
        root->key = temp->key;

        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// dem so nut trong cay
int countNodes(Node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// duyet cay theo thu tu trung tu va in ra cac gia tri
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}


// giai phong bo nho cua cay
void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}


// ham chinh, quan ly menu va cac chuc nang cua chuong trinh
int main() {
    Node* root = NULL; 
    int choice, key;
    Node* searchResult = NULL;

    root = insertNode(root, 50);
    insertNode(root, 30);
    insertNode(root, 20);
    insertNode(root, 40);
    insertNode(root, 70);
    insertNode(root, 60);
    insertNode(root, 80);

    printf("Cay nhi phan tim kiem ban dau (duyet trung tu): ");
    inorderTraversal(root);
    printf("\n");

    do {
        printf("\n===== MENU CAY NHI PHAN TIM KIEM =====\n");
        printf("1. Them mot phan tu\n");
        printf("2. Tim kiem mot phan tu\n");
        printf("3. Xoa mot phan tu\n");
        printf("4. Dem so phan tu cua cay\n");
        printf("5. In cay (duyet trung tu)\n");
        printf("0. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap gia tri can them: ");
                scanf("%d", &key);
                if (searchNode(root, key) == NULL) { 
                    root = insertNode(root, key);
                    printf("Da them %d vao cay.\n", key);
                } else {
                    printf("Khoa %d da ton tai trong cay.\n", key);
                }
                break;
            case 2:
                printf("Nhap gia tri can tim: ");
                scanf("%d", &key);
                searchResult = searchNode(root, key);
                if (searchResult != NULL) {
                    printf("Tim thay phan tu %d trong cay.\n", key);
                } else {
                    printf("Khong tim thay phan tu %d trong cay.\n", key);
                }
                break;
            case 3:
                printf("Nhap gia tri can xoa: ");
                scanf("%d", &key);
                if (searchNode(root, key) != NULL) {
                    root = deleteNode(root, key);
                    printf("Da xoa %d khoi cay (neu ton tai).\n", key);
                } else {
                    printf("Khoa %d khong ton tai de xoa.\n", key);
                }
                break;
            case 4:
                printf("So phan tu hien tai cua cay: %d\n", countNodes(root));
                break;
            case 5:
                printf("Cay hien tai (duyet trung tu): ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (choice != 0);

    freeTree(root); 
    printf("Da giai phong bo nho cay.\n");

    return 0;
}