#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_NAME_LEN 100
#define MAX_IP_LEN 20
#define MAX_CONTENT_LEN 512


typedef struct {
    char requestName[MAX_NAME_LEN];
    char sourceIP[MAX_IP_LEN];
    char content[MAX_CONTENT_LEN];
    int executionTime; // su dung giay 
} Request;


typedef struct QueueNode {
    Request data;
    struct QueueNode *next;
} QueueNode;


typedef struct {
    QueueNode *front; 
    QueueNode *rear;  
    int count;     
} Queue;

// ham khoi tao hang doi
void initQueue(Queue *q);
// ham kiem tra hang doi co rong khong
int isQueueEmpty(Queue *q);
// ham them mot yeu cau vao hang doi
void enqueue(Queue *q, Request req);
// ham lay mot yeu cau ra khoi hang doi
Request dequeue(Queue *q, int *error_flag); //  0=thanh cong, 1=loi
// ham hien thi thong tin mot yeu cau
void displayRequest(Request req);
// ham hien thi toan bo hang doi
void displayQueue(Queue *q);
// ham nhap thong tin mot yeu cau tu ban phim
void getRequestInput(Request *req);
// ham xu ly mot yeu cau
void processRequest(Request req);
// ham giai phong bo nho cua hang doi
void freeQueue(Queue *q);



// ham khoi tao hang doi
void initQueue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
}

// ham kiem tra hang doi co rong khong
int isQueueEmpty(Queue *q) {
    return (q->count == 0);
    // hoac return (q->front == NULL);
}

// ham them mot yeu cau vao hang doi
void enqueue(Queue *q, Request req) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        printf("Loi: Khong the cap phat bo nho cho nut moi trong hang doi!\n");
        return; 
    }
    newNode->data = req; 
    newNode->next = NULL;

    if (isQueueEmpty(q)) { 
        q->front = newNode;
        q->rear = newNode;
    } else { 
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->count++;
    printf("Da them yeu cau '%s' vao hang doi.\n", req.requestName);
}

// ham lay mot yeu cau ra khoi hang doi
Request dequeue(Queue *q, int *error_flag) {
    Request req_data; 
    *error_flag = 0;  

    if (isQueueEmpty(q)) {
        printf("Loi: Hang doi rong, khong the lay yeu cau!\n");
        *error_flag = 1;
        
        strcpy(req_data.requestName, "NULL"); 
        return req_data;
    }

    QueueNode* temp = q->front;
    req_data = temp->data; 

    q->front = q->front->next; 
    if (q->front == NULL) { 
        q->rear = NULL;
    }
    free(temp);
    q->count--;
    return req_data;
}

// ham hien thi thong tin mot yeu cau
void displayRequest(Request req) {
    printf("  Ten yeu cau: %s\n", req.requestName);
    printf("  Dia chi IP nguon: %s\n", req.sourceIP);
    printf("  Noi dung: %s\n", req.content);
    printf("  Thoi gian thuc hien du kien: %d giay\n", req.executionTime);
}

// ham hien thi toan bo hang doi
void displayQueue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Hang doi hien tai rong.\n");
        return;
    }
    printf("\n--- CAC YEU CAU HIEN TAI TRONG HANG DOI (Tu dau den cuoi) ---\n");
    QueueNode* current = q->front;
    int stt = 1;
    while (current != NULL) {
        printf("Yeu cau %d:\n", stt++);
        displayRequest(current->data);
        printf("------------------------------------------------------\n");
        current = current->next;
    }
    printf("Tong so yeu cau trong hang doi: %d\n", q->count);
}

// ham nhap thong tin mot yeu cau tu ban phim
void getRequestInput(Request *req) {
    printf("Nhap ten yeu cau: ");
    fgets(req->requestName, MAX_NAME_LEN, stdin);
    req->requestName[strcspn(req->requestName, "\n")] = 0; 

    printf("Nhap dia chi IP nguon: ");
    fgets(req->sourceIP, MAX_IP_LEN, stdin);
    req->sourceIP[strcspn(req->sourceIP, "\n")] = 0;

    printf("Nhap noi dung yeu cau: ");
    fgets(req->content, MAX_CONTENT_LEN, stdin);
    req->content[strcspn(req->content, "\n")] = 0;

    printf("Nhap thoi gian thuc hien du kien (giay): ");
    scanf("%d", &req->executionTime);
    while (getchar() != '\n'); 
}

// ham xu ly mot yeu cau
void processRequest(Request req) {
    printf("\nDang xu ly yeu cau...\n");
    displayRequest(req);
    printf("Mo phong thuc hien trong %d giay...\n", req.executionTime);
    sleep(req.executionTime); 
    printf("Yeu cau '%s' da duoc xu ly xong.\n", req.requestName);
}

// ham giai phong bo nho cua hang doi
void freeQueue(Queue *q) {
    int error_flag;
    while (!isQueueEmpty(q)) {
        dequeue(q, &error_flag); 
    }
    printf("Da giai phong toan bo hang doi.\n");
}

int main() {
    Queue serverQueue;
    initQueue(&serverQueue);
    Request currentRequest;
    int choice;
    int error;

    printf("--- CHUONG TRINH MO PHONG HANG DOI SERVER ---\n");

    do {
        printf("\n===== MENU =====\n");
        printf("1. Them yeu cau moi\n");
        printf("2. Xu ly yeu cau tiep theo\n");
        printf("3. Hien thi hang doi hien tai\n");
        printf("4. Xem so luong yeu cau trong hang doi\n");
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
                printf("\n-- Them yeu cau moi --\n");
                getRequestInput(&currentRequest);
                enqueue(&serverQueue, currentRequest);
                break;
            case 2:
                if (!isQueueEmpty(&serverQueue)) {
                    currentRequest = dequeue(&serverQueue, &error);
                    if (!error) {
                        processRequest(currentRequest);
                    }
                } else {
                    printf("Hang doi rong, khong co yeu cau nao de xu ly.\n");
                }
                break;
            case 3:
                displayQueue(&serverQueue);
                break;
            case 4:
                printf("So luong yeu cau hien tai trong hang doi: %d\n", serverQueue.count);
                break;
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (choice != 0);

    freeQueue(&serverQueue); // Giải phóng bộ nhớ trước khi thoát

    return 0;
}
