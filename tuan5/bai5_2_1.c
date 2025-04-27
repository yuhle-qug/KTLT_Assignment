// Name:Lê Quang Huy
// Student ID: 20237344
// Class: 752580
// Project: lab 1
// Date: 27/04/2025
#include <stdio.h>

typedef struct {
    float thuc;
    float ao;
} SoPhuc;

SoPhuc congSoPhuc(SoPhuc a, SoPhuc b) {
    SoPhuc tong;
    tong.thuc = a.thuc + b.thuc;
    tong.ao = a.ao + b.ao;
    return tong;
}

void hienThiSoPhuc(SoPhuc sp) {
    printf("%.2f + %.2fi\n", sp.thuc, sp.ao);
}

typedef struct {
    int n;      
    float data[100];
} Vecto;

Vecto congVecto(Vecto a, Vecto b) {
    Vecto tong;
    tong.n = a.n;
    for (int i = 0; i < a.n; i++) {
        tong.data[i] = a.data[i] + b.data[i];
    }
    return tong;
}

void hienThiVecto(Vecto v) {
    printf("(");
    for (int i = 0; i < v.n; i++) {
        printf("%.2f", v.data[i]);
        if (i != v.n - 1) printf(", ");
    }
    printf(")\n");
}
typedef struct {
    int hang;
    int cot;
    float data[100][100];
} MaTran;

MaTran congMaTran(MaTran a, MaTran b) {
    MaTran tong;
    tong.hang = a.hang;
    tong.cot = a.cot;
    for (int i = 0; i < a.hang; i++) {
        for (int j = 0; j < a.cot; j++) {
            tong.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return tong;
}

void hienThiMaTran(MaTran m) {
    for (int i = 0; i < m.hang; i++) {
        for (int j = 0; j < m.cot; j++) {
            printf("%.2f ", m.data[i][j]);
        }
        printf("\n");
    }
}

int main() {
    printf("TEST SO PHUC\n");
    SoPhuc sp1, sp2, tongSP;
    printf("Nhap so phuc thu nhat (phan thuc va phan ao): ");
    scanf("%f%f", &sp1.thuc, &sp1.ao);
    printf("Nhap so phuc thu hai (phan thuc va phan ao): ");
    scanf("%f%f", &sp2.thuc, &sp2.ao);
    tongSP = congSoPhuc(sp1, sp2);
    printf("Tong so phuc: ");
    hienThiSoPhuc(tongSP);

    printf("\nTEST VECTO\n");
    Vecto v1, v2, tongV;
    int i;
    printf("Nhap so chieu cua vecto: ");
    scanf("%d", &v1.n);
    v2.n = v1.n; // Hai vecto cùng số chiều

    printf("Nhap vecto thu nhat:\n");
    for (i = 0; i < v1.n; i++) {
        printf("Phan tu thu %d: ", i + 1);
        scanf("%f", &v1.data[i]);
    }

    printf("Nhap vecto thu hai:\n");
    for (i = 0; i < v2.n; i++) {
        printf("Phan tu thu %d: ", i + 1);
        scanf("%f", &v2.data[i]);
    }

    tongV = congVecto(v1, v2);
    printf("Tong vecto: ");
    hienThiVecto(tongV);

    printf("\n TEST MA TRAN \n");
    MaTran m1, m2, tongM;
    printf("Nhap kich thuoc ma tran (so hang va so cot): ");
    scanf("%d%d", &m1.hang, &m1.cot);
    m2.hang = m1.hang;
    m2.cot = m1.cot;

    printf("Nhap ma tran thu nhat:\n");
    for (i = 0; i < m1.hang; i++) {
        for (int j = 0; j < m1.cot; j++) {
            printf("Phan tu [%d][%d]: ", i, j);
            scanf("%f", &m1.data[i][j]);
        }
    }

    printf("Nhap ma tran thu hai:\n");
    for (i = 0; i < m2.hang; i++) {
        for (int j = 0; j < m2.cot; j++) {
            printf("Phan tu [%d][%d]: ", i, j);
            scanf("%f", &m2.data[i][j]);
        }
    }

    tongM = congMaTran(m1, m2);
    printf("Tong ma tran:\n");
    hienThiMaTran(tongM);

    return 0;
}