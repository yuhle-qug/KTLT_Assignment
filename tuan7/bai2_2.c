// Name:Lê Quang Huy
// Student ID: 20237344
// Class: 752580
// Project: lab 1
// Date: 25/05/2025
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

typedef struct SinhVien {
    char mssv[15];
    char hoTen[50];
    char hocPhan[50];
    float diem;
} ThongTinSinhVien;


typedef struct Node {
    ThongTinSinhVien data;
    struct Node *next;
} Node;

// cac ham can su dung 
Node* taoNut(ThongTinSinhVien sv);
void inThongTinSV(ThongTinSinhVien sv);
void themVaoDau(Node** head_ref, ThongTinSinhVien sv);
void themVaoCuoi(Node** head_ref, ThongTinSinhVien sv);
int themSauMSSV(Node* head, char* mssv_truoc, ThongTinSinhVien sv_moi);
Node* timTheoMSSV(Node* head, char* mssv_can_tim);
int suaTheoMSSV(Node* head, char* mssv_can_sua, ThongTinSinhVien sv_moi);
int xoaTheoMSSV(Node** head_ref, char* mssv_can_xoa);
void inDanhSach(Node* head);
void giaiPhongDanhSach(Node** head_ref);
void nhapThongTinSV(ThongTinSinhVien *sv);

Node* taoNut(ThongTinSinhVien sv) {
    Node* nutMoi = (Node*)malloc(sizeof(Node));
    if (nutMoi == NULL) {
        printf("Loi: Khong the cap phat bo nho!\n");
        return NULL;
    }
    nutMoi->data = sv; // Gán trực tiếp struct
    nutMoi->next = NULL;
    return nutMoi;
}

void inThongTinSV(ThongTinSinhVien sv) {
    printf("  MSSV: %s\n", sv.mssv);
    printf("  Ho ten: %s\n", sv.hoTen);
    printf("  Hoc phan: %s\n", sv.hocPhan);
    printf("  Diem: %.2f\n", sv.diem);
}


void themVaoDau(Node** head_ref, ThongTinSinhVien sv) {
    Node* nutMoi = taoNut(sv);
    if (nutMoi == NULL) return;

    nutMoi->next = *head_ref;
    *head_ref = nutMoi;
    printf("Da them sinh vien MSSV %s vao dau danh sach.\n", sv.mssv);
}


void themVaoCuoi(Node** head_ref, ThongTinSinhVien sv) {
    Node* nutMoi = taoNut(sv);
    if (nutMoi == NULL) return;

    if (*head_ref == NULL) { 
        *head_ref = nutMoi;
        printf("Da them sinh vien MSSV %s vao danh sach (rong).\n", sv.mssv);
        return;
    }
    Node* temp = *head_ref;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = nutMoi;
    printf("Da them sinh vien MSSV %s vao cuoi danh sach.\n", sv.mssv);
}

int themSauMSSV(Node* head, char* mssv_truoc, ThongTinSinhVien sv_moi) {
    Node* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->data.mssv, mssv_truoc) == 0) { 
            Node* nutMoi = taoNut(sv_moi);
            if (nutMoi == NULL) return 0; 
            
            nutMoi->next = temp->next;
            temp->next = nutMoi;
            printf("Da them sinh vien MSSV %s sau sinh vien MSSV %s.\n", sv_moi.mssv, mssv_truoc);
            return 1; 
        }
        temp = temp->next;
    }
    printf("Khong tim thay sinh vien co MSSV %s de them vao sau.\n", mssv_truoc);
    return 0; 
}



Node* timTheoMSSV(Node* head, char* mssv_can_tim) {
    Node* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->data.mssv, mssv_can_tim) == 0) {
            return temp; 
        }
        temp = temp->next;
    }
    return NULL; 
}

// khong sua MSSV
int suaTheoMSSV(Node* head, char* mssv_can_sua, ThongTinSinhVien sv_moi) {
    Node* nutCanSua = timTheoMSSV(head, mssv_can_sua);
    if (nutCanSua != NULL) {
        strcpy(nutCanSua->data.hoTen, sv_moi.hoTen);
        strcpy(nutCanSua->data.hocPhan, sv_moi.hocPhan);
        nutCanSua->data.diem = sv_moi.diem;
        printf("Da cap nhat thong tin cho sinh vien MSSV %s.\n", mssv_can_sua);
        return 1; 
    }
    printf("Khong tim thay sinh vien co MSSV %s de cap nhat.\n", mssv_can_sua);
    return 0; 
}


int xoaTheoMSSV(Node** head_ref, char* mssv_can_xoa) {
    Node* temp = *head_ref;
    Node* prev = NULL;

    if (temp == NULL) {
        printf("Danh sach rong, khong the xoa.\n");
        return 0;
    }

    if (strcmp(temp->data.mssv, mssv_can_xoa) == 0) {
        *head_ref = temp->next;
        printf("Da xoa sinh vien MSSV %s (o dau danh sach).\n", mssv_can_xoa);
        free(temp);
        return 1;
    }

    
    while (temp != NULL && strcmp(temp->data.mssv, mssv_can_xoa) != 0) {
        prev = temp;
        temp = temp->next;
    }

    
    if (temp == NULL) {
        printf("Khong tim thay sinh vien co MSSV %s de xoa.\n", mssv_can_xoa);
        return 0;
    }

    
    prev->next = temp->next;
    printf("Da xoa sinh vien MSSV %s.\n", mssv_can_xoa);
    free(temp); 
    return 1;
}


void inDanhSach(Node* head) {
    if (head == NULL) {
        printf("Danh sach sinh vien rong.\n");
        return;
    }
    printf("\n--- DANH SACH SINH VIEN ---\n");
    Node* temp = head;
    int count = 1;
    while (temp != NULL) {
        printf("STT %d:\n", count++);
        inThongTinSV(temp->data);
        printf("---------------------------\n");
        temp = temp->next;
    }
}


void giaiPhongDanhSach(Node** head_ref) {
    Node* current = *head_ref;
    Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *head_ref = NULL;
}


void nhapThongTinSV(ThongTinSinhVien *sv) {
    printf("Nhap MSSV: ");
    scanf("%14s", sv->mssv); 
    while(getchar() != '\n'); 

    printf("Nhap Ho ten: ");
    fgets(sv->hoTen, sizeof(sv->hoTen), stdin);
    sv->hoTen[strcspn(sv->hoTen, "\n")] = 0; 

    printf("Nhap Hoc phan: ");
    fgets(sv->hocPhan, sizeof(sv->hocPhan), stdin);
    sv->hocPhan[strcspn(sv->hocPhan, "\n")] = 0;

    printf("Nhap Diem: ");
    scanf("%f", &sv->diem);
    while(getchar() != '\n'); 
}


int main() {
    Node* head = NULL;
    ThongTinSinhVien sv_temp;
    char mssv_key[15];
    int choice;
    Node* timThayNode = NULL;

    do {
        printf("\n===== MENU QUAN LY SINH VIEN =====\n");
        printf("1. Them sinh vien vao dau danh sach\n");
        printf("2. Them sinh vien vao cuoi danh sach\n");
        printf("3. Them sinh vien vao sau mot MSSV\n");
        printf("4. Tim kiem sinh vien theo MSSV\n");
        printf("5. Sua thong tin sinh vien (theo MSSV)\n");
        printf("6. Xoa sinh vien (theo MSSV)\n");
        printf("7. In danh sach sinh vien\n");
        printf("0. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        while(getchar() != '\n'); 

        switch (choice) {
            case 1:
                printf("\n-- Them vao dau --\n");
                nhapThongTinSV(&sv_temp);
                themVaoDau(&head, sv_temp);
                break;
            case 2:
                printf("\n-- Them vao cuoi --\n");
                nhapThongTinSV(&sv_temp);
                themVaoCuoi(&head, sv_temp);
                break;
            case 3:
                printf("\n-- Them sau MSSV --\n");
                printf("Nhap MSSV cua sinh vien dung truoc: ");
                scanf("%14s", mssv_key);
                while(getchar() != '\n');
                printf("Nhap thong tin sinh vien moi:\n");
                nhapThongTinSV(&sv_temp);
                themSauMSSV(head, mssv_key, sv_temp);
                break;
            case 4:
                printf("\n-- Tim kiem theo MSSV --\n");
                printf("Nhap MSSV can tim: ");
                scanf("%14s", mssv_key);
                while(getchar() != '\n');
                timThayNode = timTheoMSSV(head, mssv_key);
                if (timThayNode != NULL) {
                    printf("Tim thay sinh vien:\n");
                    inThongTinSV(timThayNode->data);
                } else {
                    printf("Khong tim thay sinh vien co MSSV %s.\n", mssv_key);
                }
                break;
            case 5:
                printf("\n-- Sua thong tin sinh vien --\n");
                printf("Nhap MSSV cua sinh vien can sua: ");
                scanf("%14s", mssv_key);
                while(getchar() != '\n');
                timThayNode = timTheoMSSV(head, mssv_key);
                if (timThayNode != NULL) {
                    printf("Nhap thong tin moi cho sinh vien (MSSV se khong doi):\n");
                    ThongTinSinhVien sv_capnhat;
                    strcpy(sv_capnhat.mssv, mssv_key); 
                    printf("Nhap Ho ten moi: ");
                    fgets(sv_capnhat.hoTen, sizeof(sv_capnhat.hoTen), stdin);
                    sv_capnhat.hoTen[strcspn(sv_capnhat.hoTen, "\n")] = 0;
                    printf("Nhap Hoc phan moi: ");
                    fgets(sv_capnhat.hocPhan, sizeof(sv_capnhat.hocPhan), stdin);
                    sv_capnhat.hocPhan[strcspn(sv_capnhat.hocPhan, "\n")] = 0;
                    printf("Nhap Diem moi: ");
                    scanf("%f", &sv_capnhat.diem);
                    while(getchar() != '\n');
                    suaTheoMSSV(head, mssv_key, sv_capnhat);
                } else {
                     printf("Khong tim thay sinh vien co MSSV %s de sua.\n", mssv_key);
                }
                break;
            case 6:
                printf("\n-- Xoa sinh vien --\n");
                printf("Nhap MSSV cua sinh vien can xoa: ");
                scanf("%14s", mssv_key);
                while(getchar() != '\n');
                xoaTheoMSSV(&head, mssv_key);
                break;
            case 7:
                inDanhSach(head);
                break;
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (choice != 0);

    giaiPhongDanhSach(&head); 
    printf("Da giai phong bo nho.\n");

    return 0;
}