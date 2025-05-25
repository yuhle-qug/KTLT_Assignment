#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>  // cho errno va ERANGE de kiem tra loi strtoll
#include <limits.h> // cho LLONG_MAX, LLONG_MIN

#define MAX_LINE_LENGTH 256 // do dai toi da cua mot dong trong file input
#define MAX_NUM_STR_LENGTH 100 // do dai toi da cua chuoi so

// ham thuc hien phep toan giua hai so lon
// error_flag: 0 = khong loi, 1 = chia cho 0, 2 = toan tu khong hop le, 3 = tran so
long long perform_operation(long long num1, long long num2, char op, int* error_flag) {
    *error_flag = 0;
    switch (op) {
        case '+':
            // kiem tra tran so cong
            if ((num2 > 0 && num1 > LLONG_MAX - num2) || \
                (num2 < 0 && num1 < LLONG_MIN - num2)) {
                *error_flag = 3; // tran so
                return 0;
            }
            return num1 + num2;
        case '-':
            // kiem tra tran so tru
             if ((num2 < 0 && num1 > LLONG_MAX + num2) || \
                 (num2 > 0 && num1 < LLONG_MIN + num2)) {
                *error_flag = 3; // tran so
                return 0;
            }
            return num1 - num2;
        case '*':
            if (num1 == 0 || num2 == 0) return 0;
            // kiem tra tran so nhan (co ban)
            if (llabs(num1) > LLONG_MAX / llabs(num2)) {
                 *error_flag = 3; // tran so
                 return 0;
            }
            return num1 * num2;
        case '/':
            if (num2 == 0) {
                *error_flag = 1; // chia cho 0
                return 0;
            }
            // kiem tra truong hop LLONG_MIN / -1 gay tran so
            if (num1 == LLONG_MIN && num2 == -1) {
                *error_flag = 3; // tran so
                return 0;
            }
            return num1 / num2; // phep chia so nguyen
        default:
            *error_flag = 2; // toan tu khong hop le
            return 0;
    }
}

// ham xu ly file input va ghi ra file output
void process_files(const char* input_filename, const char* output_filename) {
    FILE *inputFile, *outputFile;
    char line[MAX_LINE_LENGTH];
    char num1_str[MAX_NUM_STR_LENGTH];
    char num2_str[MAX_NUM_STR_LENGTH];
    char op_char; // bien luu toan tu
    long long num1, num2, result;
    int error_flag;
    char* endptr1;
    char* endptr2;

    // mo file input
    inputFile = fopen(input_filename, "r");
    if (inputFile == NULL) {
        perror("Loi mo file input");
        printf("Hay chac chan rang file '%s' ton tai va co quyen doc.\n", input_filename);
        return;
    }

    // mo file output
    outputFile = fopen(output_filename, "w");
    if (outputFile == NULL) {
        perror("Loi mo file output");
        printf("Khong the tao hoac ghi vao file '%s'.\n", output_filename);
        fclose(inputFile);
        return;
    }

    printf("Dang xu ly file '%s', ket qua se duoc ghi vao '%s'...\n", input_filename, output_filename);

    // doc tung dong tu file input
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        // loai bo ky tu newline o cuoi dong (neu co)
        line[strcspn(line, "\n")] = 0;
        line[strcspn(line, "\r")] = 0; // cho ca windows newlines

        // phan tich dong: so1 toan_tu so2
        int items_scanned = sscanf(line, "%s %c %s", num1_str, &op_char, num2_str);

        if (items_scanned != 3) {
            fprintf(outputFile, "Dong khong hop le (sai format): %s\n", line);
            fprintf(stderr, "Canh bao: Dong khong hop le trong file input (sai format): %s\n", line);
            continue;
        }

        // chuyen doi chuoi so thanh long long
        errno = 0; // reset errno truoc khi goi strtoll
        num1 = strtoll(num1_str, &endptr1, 10);
        if (errno == ERANGE || *endptr1 != '\0' || endptr1 == num1_str) {
            fprintf(outputFile, "%s = Loi: Dinh dang so thu nhat khong hop le\n", line);
            fprintf(stderr, "Canh bao: Loi dinh dang so thu nhat: %s (Dong: %s)\n", num1_str, line);
            continue;
        }

        errno = 0;
        num2 = strtoll(num2_str, &endptr2, 10);
        if (errno == ERANGE || *endptr2 != '\0' || endptr2 == num2_str) {
            fprintf(outputFile, "%s = Loi: Dinh dang so thu hai khong hop le\n", line);
            fprintf(stderr, "Canh bao: Loi dinh dang so thu hai: %s (Dong: %s)\n", num2_str, line);
            continue;
        }

        // thuc hien phep toan
        result = perform_operation(num1, num2, op_char, &error_flag);

        // ghi ket qua vao file output
        fprintf(outputFile, "%s %c %s = ", num1_str, op_char, num2_str);
        if (error_flag == 0) {
            fprintf(outputFile, "%lld\n", result);
        } else if (error_flag == 1) {
            fprintf(outputFile, "Loi: Chia cho 0\n");
        } else if (error_flag == 2) {
            fprintf(outputFile, "Loi: Toan tu khong hop le '%c'\n", op_char);
        } else if (error_flag == 3) {
            fprintf(outputFile, "Loi: Tran so\n");
        }
    }

    printf("Xu ly hoan tat. Kiem tra file '%s'.\n", output_filename);
    fclose(inputFile);
    fclose(outputFile);
}

// ham chinh chuong trinh
int main() {
    char input_file[FILENAME_MAX]; // ten file input
    char output_file[FILENAME_MAX]; // ten file output

    printf("Chuong trinh tinh toan voi so lon tu file.\n");

    printf("Nhap ten file input (vi du: input.txt): ");
    if (fgets(input_file, sizeof(input_file), stdin) != NULL) {
        input_file[strcspn(input_file, "\n")] = 0; // xoa newline
    } else {
        printf("Loi khi doc ten file input.\n");
        return 1;
    }

    printf("Nhap ten file output (vi du: output.txt): ");
    if (fgets(output_file, sizeof(output_file), stdin) != NULL) {
        output_file[strcspn(output_file, "\n")] = 0; // xoa newline
    } else {
        printf("Loi khi doc ten file output.\n");
        return 1;
    }
    
    if (strlen(input_file) == 0 || strlen(output_file) == 0) {
        printf("Ten file khong duoc de trong.\n");
        return 1;
    }

    // goi ham xu ly file
    process_files(input_file, output_file);

    return 0;
}