// Name:Lê Quang Huy
// Student ID: 20237344
// Class: 752580
// Project: lab 1
// Date: 25/05/2025
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_SIZE 1024
#define MAX_INPUT_SIZE 256

typedef struct StackNode {
    char* text_state;       
    struct StackNode* next;
} StackNode;

StackNode* undo_stack = NULL;
StackNode* redo_stack = NULL;
char current_text[MAX_TEXT_SIZE];

// ham tao mot nut cho ngan xep
StackNode* createStackNode(const char* text) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        perror("Khong the cap phat bo nho cho StackNode");
        exit(EXIT_FAILURE);
    }
    newNode->text_state = (char*)malloc(strlen(text) + 1);
    if (!newNode->text_state) {
        perror("Khong the cap phat bo nho cho text_state trong StackNode");
        free(newNode);
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->text_state, text);
    newNode->next = NULL;
    return newNode;
}

// ham kiem tra ngan xep co rong khong
int isStackEmpty(StackNode* top) {
    return top == NULL;
}

// ham day mot trang thai vao ngan xep
void push(StackNode** top_ref, const char* text) {
    StackNode* newNode = createStackNode(text);
    newNode->next = *top_ref;
    *top_ref = newNode;
}

// ham lay mot trang thai ra khoi ngan xep
char* pop(StackNode** top_ref) {
    if (isStackEmpty(*top_ref)) {
        return NULL;
    }
    StackNode* tempNode = *top_ref;
    char* popped_text = tempNode->text_state; 
    
    *top_ref = tempNode->next;
    free(tempNode); 
    
    return popped_text;
}

// ham xoa toan bo ngan xep va giai phong bo nho
void clearStack(StackNode** top_ref) {
    while (!isStackEmpty(*top_ref)) {
        char* text_to_free = pop(top_ref);
        if (text_to_free) {
            free(text_to_free);
        }
    }
}

// ham tao ban sao chuoi ky tu
char* duplicate_string(const char* src) {
    if (src == NULL) return NULL;
    char* dest = (char*)malloc(strlen(src) + 1);
    if (dest == NULL) {
        perror("Khong the cap phat bo nho cho duplicate_string");
        exit(EXIT_FAILURE);
    }
    strcpy(dest, src);
    return dest;
}

// ham them van ban moi vao van ban hien tai va cap nhat undo/redo
void typeText(const char* text_to_add) {
    push(&undo_stack, current_text);

    if (strlen(current_text) + strlen(text_to_add) < MAX_TEXT_SIZE) {
        strcat(current_text, text_to_add);
    } else {
        printf("Loi: Van ban qua dai, khong the them.\n");
        char* last_state = pop(&undo_stack);
        if (last_state) free(last_state);
        return;
    }

    clearStack(&redo_stack);

    printf("Da them: \"%s\"\n", text_to_add);
}

// ham thuc hien thao tac undo
void performUndo() {
    if (isStackEmpty(undo_stack)) {
        printf("Khong co gi de undo.\n");
        return;
    }

    push(&redo_stack, current_text);
    char* previous_state = pop(&undo_stack);
    if (previous_state) {
        strcpy(current_text, previous_state);
        free(previous_state); 
        printf("Da undo.\n");
    }
}

// ham thuc hien thao tac redo
void performRedo() {
    if (isStackEmpty(redo_stack)) {
        printf("Khong co gi de redo.\n");
        return;
    }

    push(&undo_stack, current_text);

    char* future_state = pop(&redo_stack);
    if (future_state) {
        strcpy(current_text, future_state);
        free(future_state); 
        printf("Da redo.\n");
    }
}

// ham chinh chuong trinh
int main() {
    current_text[0] = '\0'; 
    char input_buffer[MAX_INPUT_SIZE];
    int choice;

    printf("--- Chuong trinh Soan Thao Van Ban Don Gian (voi Undo/Redo) ---\n");

    while (1) {
        printf("\nVan ban hien tai: \"%s\"\n", current_text);
        printf("----------------------------------------\n");
        printf("Chon hanh dong:\n");
        printf("1. Them van ban\n");
        printf("2. Undo\n");
        printf("3. Redo\n");
        printf("0. Thoat\n");
        printf("Lua chon cua ban: ");

        if (scanf("%d", &choice) != 1) {
            printf("Vui long nhap mot so.\n");
            while (getchar() != '\n'); 
            continue;
        }
        while (getchar() != '\n'); 

        switch (choice) {
            case 1:
                printf("Nhap van ban muon them: ");
                if (fgets(input_buffer, MAX_INPUT_SIZE, stdin) != NULL) {
                    input_buffer[strcspn(input_buffer, "\n")] = 0;
                    typeText(input_buffer);
                }
                break;
            case 2:
                performUndo();
                break;
            case 3:
                performRedo();
                break;
            case 0:
                printf("Thoat chuong trinh.\n");
                clearStack(&undo_stack);
                clearStack(&redo_stack);
                return 0;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    }

    return 0;
}