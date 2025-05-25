// Name:Lê Quang Huy
// Student ID: 20237344
// Class: 752580
// Project: lab 1
// Date: 25/05/2025
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h>  

#define MAX_SIZE 100 


typedef struct {
    char items[MAX_SIZE];
    int top;
} CharStack;

// ham khoi tao ngan xep ky tu
void cs_init(CharStack* s) { s->top = -1; }
// ham kiem tra ngan xep ky tu co rong khong
int cs_isEmpty(CharStack* s) { return s->top == -1; }
// ham kiem tra ngan xep ky tu co day khong
int cs_isFull(CharStack* s) { return s->top == MAX_SIZE - 1; }

// ham day mot ky tu vao ngan xep ky tu
void cs_push(CharStack* s, char item) {
    if (cs_isFull(s)) {
        printf("Loi: Ngan xep toan tu day!\n");
        return;
    }
    s->items[++(s->top)] = item;
}

// ham lay mot ky tu ra khoi ngan xep ky tu
char cs_pop(CharStack* s) {
    if (cs_isEmpty(s)) {
        printf("Loi: Ngan xep toan tu rong khi pop!\n");
        return '\0'; 
    }
    return s->items[(s->top)--];
}

// ham tra ve ky tu o dinh ngan xep ky tu
char cs_peek(CharStack* s) {
    if (cs_isEmpty(s)) {
        return '\0';
    }
    return s->items[s->top];
}

typedef struct {
    double items[MAX_SIZE];
    int top;
} DoubleStack;

// ham khoi tao ngan xep so thuc
void ds_init(DoubleStack* s) { s->top = -1; }
// ham kiem tra ngan xep so thuc co rong khong
int ds_isEmpty(DoubleStack* s) { return s->top == -1; }
// ham kiem tra ngan xep so thuc co day khong
int ds_isFull(DoubleStack* s) { return s->top == MAX_SIZE - 1; }

// ham day mot so thuc vao ngan xep so thuc
void ds_push(DoubleStack* s, double item) {
    if (ds_isFull(s)) {
        printf("Loi: Ngan xep toan hang day!\n");
        return;
    }
    s->items[++(s->top)] = item;
}

// ham lay mot so thuc ra khoi ngan xep so thuc
double ds_pop(DoubleStack* s) {
    if (ds_isEmpty(s)) {
        printf("Loi: Ngan xep toan hang rong khi pop!\n");
        return 0.0;
    }
    return s->items[(s->top)--];
}

// --- Hàm trợ giúp ---

// Xác định độ ưu tiên của toán tử
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0; 
}

// ham chuyen doi bieu thuc trung to sang hau to
void infixToPostfix(const char* infix, char* postfix) {
    CharStack op_stack;
    cs_init(&op_stack);
    int k = 0; 

    for (int i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];

        if (isdigit(token)) { 
            postfix[k++] = token;
        } else if (token == '(') {
            cs_push(&op_stack, token);
        } else if (token == ')') {
            while (!cs_isEmpty(&op_stack) && cs_peek(&op_stack) != '(') {
                postfix[k++] = cs_pop(&op_stack);
            }
            if (!cs_isEmpty(&op_stack) && cs_peek(&op_stack) == '(') {
                cs_pop(&op_stack); 
            } else {
                printf("Loi: Bieu thuc infix sai (thieu hoac thua dau ngoac).\n");
                postfix[0] = '\0'; 
                return;
            }
        } else { 
            while (!cs_isEmpty(&op_stack) && cs_peek(&op_stack) != '(' &&
                   precedence(cs_peek(&op_stack)) >= precedence(token)) {
                postfix[k++] = cs_pop(&op_stack);
            }
            cs_push(&op_stack, token);
        }
    }

    while (!cs_isEmpty(&op_stack)) {
        if (cs_peek(&op_stack) == '(') {
             printf("Loi: Bieu thuc infix sai (thieu hoac thua dau ngoac).\n");
             postfix[0] = '\0'; 
             return;
        }
        postfix[k++] = cs_pop(&op_stack);
    }
    postfix[k] = '\0'; 
}

// ham tinh gia tri bieu thuc hau to
double evaluatePostfix(const char* postfix, int* error_flag) {
    DoubleStack val_stack;
    ds_init(&val_stack);
    *error_flag = 0; 

    for (int i = 0; postfix[i] != '\0'; i++) {
        char token = postfix[i];

        if (isdigit(token)) {
            ds_push(&val_stack, (double)(token - '0')); 
        } else if (strchr("+-*/", token)) { 
            if (ds_isEmpty(&val_stack)) { *error_flag = 2; return 0.0; }
            double val2 = ds_pop(&val_stack);
            if (ds_isEmpty(&val_stack)) { *error_flag = 2; return 0.0; }
            double val1 = ds_pop(&val_stack);

            switch (token) {
                case '+': ds_push(&val_stack, val1 + val2); break;
                case '-': ds_push(&val_stack, val1 - val2); break;
                case '*': ds_push(&val_stack, val1 * val2); break;
                case '/':
                    if (val2 == 0) {
                        *error_flag = 1;
                        return 0.0;
                    }
                    ds_push(&val_stack, val1 / val2);
                    break;
            }
        } else {
            *error_flag = 2;
            return 0.0;
        }
    }

    if (val_stack.top != 0) { 
        *error_flag = 2; 
        return 0.0;
    }
    return ds_pop(&val_stack);
}

// ham chinh chuong trinh
int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];
    int error = 0;

    printf("Nhap bieu thuc trung to (voi so 1 chu so, khong co khoang trang, vd: (3+4)*2-1):\n");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    if (postfix[0] == '\0') { 
        printf("Khong the chuyen doi sang postfix.\n");
        return 1;
    }
    printf("Bieu thuc hau to (Postfix): %s\n", postfix);

    double result = evaluatePostfix(postfix, &error);

    if (error == 0) {
        printf("Ket qua: %f\n", result);
    } else if (error == 1) {
        printf("Loi tinh toan: Chia cho 0!\n");
    } else {
        printf("Loi tinh toan: Bieu thuc Postfix khong hop le hoac loi khac.\n");
    }

    return 0;
}