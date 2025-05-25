#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// dinh nghia hang so pi neu chua co
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

// so dinh toi da cua mot hinh
#define MAX_VERTICES 50

// cau truc luu toa do diem 2 chieu
typedef struct {
    double x;
    double y;
} Point2D;

// cau truc luu mot hinh da giac
typedef struct {
    Point2D vertices[MAX_VERTICES]; // mang cac dinh
    int num_vertices;               // so dinh
    Point2D center;                 // tam cua hinh
} Shape;

// khai bao cac ham xu ly hinh
// ham doc hinh tu file
int loadShapeFromFile(Shape* shape, const char* filename);
// ham ghi chi tiet hinh ra file
void writeShapeDetailsToFile(FILE* outputFile, const Shape* shape, const char* title);
// ham in thong tin hinh ra man hinh
void printShapeToConsole(const Shape* shape, const char* title);
// ham tinh tam cua hinh
void calculateShapeCenter(Shape* shape);
// ham doi xung qua truc ngang y = y_axis_val
void reflectShapeAcrossXAxis(Shape* shape, double y_axis_val);
// ham doi xung qua truc dung x = x_axis_val
void reflectShapeAcrossYAxis(Shape* shape, double x_axis_val);
// ham doi xung qua mot diem
void reflectShapeThroughPoint(Shape* shape, Point2D pivot_point);
// ham quay hinh quanh mot diem
void rotateShape(Shape* shape, Point2D pivot, double angle_degrees);
// ham phong to/thu nho hinh quanh mot diem
void scaleShape(Shape* shape, Point2D pivot, double scale_x, double scale_y);

// ham chinh chuong trinh
int main(void) {
    Shape myShape, transformedShape;
    myShape.num_vertices = 0;

    const char* inputFile = "shape_input.txt";
    const char* outputTextFile = "shape_output.txt"; // ten file output duy nhat
    FILE* outputFilePtr = NULL; // con tro file cho file output

    printf("--- chuong trinh bien hinh 2d ---\n");
    printf("ket qua chi tiet se duoc ghi vao file: %s\n", outputTextFile);

    // mo file output o che do ghi ("w" - se ghi de neu file da ton tai)
    outputFilePtr = fopen(outputTextFile, "w");
    if (outputFilePtr == NULL) {
        printf("loi: khong the mo file output '%s' de ghi.\n", outputTextFile);
        return 1; // thoat neu khong mo duoc file
    }

    // thu doc hinh tu file, neu khong duoc thi tao hinh mac dinh
    if (!loadShapeFromFile(&myShape, inputFile)) {
        fprintf(outputFilePtr, "khong load duoc hinh tu file '%s'. tao hinh tam giac mac dinh.\n", inputFile);
        printf("khong load duoc hinh tu file '%s'. tao hinh tam giac mac dinh.\n", inputFile);
        myShape.vertices[0] = (Point2D){150.0, 100.0};
        myShape.vertices[1] = (Point2D){250.0, 300.0};
        myShape.vertices[2] = (Point2D){50.0,  250.0};
        myShape.num_vertices = 3;
    }
    calculateShapeCenter(&myShape);

    // in hinh goc ra console va file output
    printShapeToConsole(&myShape, "hinh ban dau (console):");
    writeShapeDetailsToFile(outputFilePtr, &myShape, "hinh ban dau");

    // --- thuc hien cac phep bien hinh khac o day ---
    // doi xung qua truc X (y=0)
    Shape shape_reflected_x = myShape; // tao ban sao de bien hinh
    reflectShapeAcrossXAxis(&shape_reflected_x, 0.0);
    printShapeToConsole(&shape_reflected_x, "Sau khi doi xung qua truc X (y=0):");
    writeShapeDetailsToFile(outputFilePtr, &shape_reflected_x, "hinh sau khi doi xung qua truc X");

    // doi xung qua truc Y (x=0)
    Shape shape_reflected_y = myShape;
    reflectShapeAcrossYAxis(&shape_reflected_y, 0.0);
    printShapeToConsole(&shape_reflected_y, "Sau khi doi xung qua truc Y (x=0):");
    writeShapeDetailsToFile(outputFilePtr, &shape_reflected_y, "hinh sau khi doi xung qua truc Y");

    // doi xung qua tam cua chinh no
    Shape shape_reflected_point = myShape;
    reflectShapeThroughPoint(&shape_reflected_point, myShape.center);
    printShapeToConsole(&shape_reflected_point, "Sau khi doi xung qua tam hinh:");
    writeShapeDetailsToFile(outputFilePtr, &shape_reflected_point, "hinh sau khi doi xung qua tam hinh");

    // quay hinh 90 do quanh tam cua no
    Shape shape_rotated = myShape;
    rotateShape(&shape_rotated, myShape.center, 90.0);
    printShapeToConsole(&shape_rotated, "Sau khi quay 90 do quanh tam hinh:");
    writeShapeDetailsToFile(outputFilePtr, &shape_rotated, "hinh sau khi quay 90 do quanh tam hinh");

    // phong to gap 2 lan quanh tam cua no
    Shape shape_scaled = myShape;
    scaleShape(&shape_scaled, myShape.center, 2.0, 2.0);
    printShapeToConsole(&shape_scaled, "Sau khi phong to x2 quanh tam hinh:");
    writeShapeDetailsToFile(outputFilePtr, &shape_scaled, "hinh sau khi phong to x2 quanh tam hinh");

    // thu nho 0.5 lan quanh goc toa do (0,0)
    Shape shape_scaled_origin = myShape;
    Point2D origin = {0.0, 0.0};
    scaleShape(&shape_scaled_origin, origin, 0.5, 0.5);
    printShapeToConsole(&shape_scaled_origin, "Sau khi thu nho x0.5 quanh goc toa do:");
    writeShapeDetailsToFile(outputFilePtr, &shape_scaled_origin, "hinh sau khi thu nho x0.5 quanh goc toa do");

    fclose(outputFilePtr);
    return 0;
}

// ham doc hinh tu file
int loadShapeFromFile(Shape* shape, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Loi: Khong the mo file input '%s'\n", filename);
        shape->num_vertices = 0;
        return 0; // that bai
    }

    if (fscanf(file, "%d", &shape->num_vertices) != 1 || shape->num_vertices > MAX_VERTICES || shape->num_vertices <= 0) {
        printf("Loi: So dinh khong hop le hoac qua lon trong file '%s'.\n", filename);
        shape->num_vertices = 0;
        fclose(file);
        return 0; // that bai
    }

    for (int i = 0; i < shape->num_vertices; i++) {
        if (fscanf(file, "%lf %lf", &shape->vertices[i].x, &shape->vertices[i].y) != 2) {
            printf("Loi: Dinh dang toa do dinh thu %d khong dung trong file '%s'.\n", i + 1, filename);
            shape->num_vertices = 0; // danh dau la doc loi
            fclose(file);
            return 0; // that bai
        }
    }
    fclose(file);
    printf("Da load hinh tu file '%s' voi %d dinh.\n", filename, shape->num_vertices);
    return 1; // thanh cong
}

// ham ghi chi tiet hinh ra file
void writeShapeDetailsToFile(FILE* outputFile, const Shape* shape, const char* title) {
    fprintf(outputFile, "\n%s\n", title);
    if (shape->num_vertices == 0) {
        fprintf(outputFile, "  (Hinh rong)\n");
        return;
    }
    fprintf(outputFile, "  So dinh: %d\n", shape->num_vertices);
    fprintf(outputFile, "  Tam (tinh toan): (%.2f, %.2f)\n", shape->center.x, shape->center.y);
    fprintf(outputFile, "  Cac dinh:\n");
    for (int i = 0; i < shape->num_vertices; i++) {
        fprintf(outputFile, "    Dinh %d: (%.2f, %.2f)\n", i + 1, shape->vertices[i].x, shape->vertices[i].y);
    }
}

// ham in thong tin hinh ra man hinh
void printShapeToConsole(const Shape* shape, const char* title) {
    printf("\n%s\n", title);
    if (shape->num_vertices == 0) {
        printf("  (Hinh rong)\n");
        return;
    }
    printf("  So dinh: %d\n", shape->num_vertices);
    printf("  Tam (tinh toan): (%.2f, %.2f)\n", shape->center.x, shape->center.y);
    printf("  Cac dinh:\n");
    for (int i = 0; i < shape->num_vertices; i++) {
        printf("    Dinh %d: (%.2f, %.2f)\n", i + 1, shape->vertices[i].x, shape->vertices[i].y);
    }
}

// ham tinh tam cua hinh
void calculateShapeCenter(Shape* shape) {
    if (shape->num_vertices == 0) {
        shape->center = (Point2D){0.0, 0.0};
        return;
    }
    double sum_x = 0, sum_y = 0;
    for (int i = 0; i < shape->num_vertices; i++) {
        sum_x += shape->vertices[i].x;
        sum_y += shape->vertices[i].y;
    }
    shape->center.x = sum_x / shape->num_vertices;
    shape->center.y = sum_y / shape->num_vertices;
}

// ham doi xung qua duong thang y = y_axis_val (truc ngang)
void reflectShapeAcrossXAxis(Shape* shape, double y_axis_val) {
    for (int i = 0; i < shape->num_vertices; i++) {
        shape->vertices[i].y = 2 * y_axis_val - shape->vertices[i].y;
    }
    calculateShapeCenter(shape); // cap nhat lai tam sau bien hinh
}

// ham doi xung qua duong thang x = x_axis_val (truc dung)
void reflectShapeAcrossYAxis(Shape* shape, double x_axis_val) {
    for (int i = 0; i < shape->num_vertices; i++) {
        shape->vertices[i].x = 2 * x_axis_val - shape->vertices[i].x;
    }
    calculateShapeCenter(shape); // cap nhat lai tam sau bien hinh
}

// ham doi xung qua mot diem pivot_point
void reflectShapeThroughPoint(Shape* shape, Point2D pivot_point) {
    for (int i = 0; i < shape->num_vertices; i++) {
        shape->vertices[i].x = 2 * pivot_point.x - shape->vertices[i].x;
        shape->vertices[i].y = 2 * pivot_point.y - shape->vertices[i].y;
    }
    calculateShapeCenter(shape); // cap nhat lai tam sau bien hinh
}

// ham quay hinh quanh diem pivot mot goc angle_degrees
void rotateShape(Shape* shape, Point2D pivot, double angle_degrees) {
    double angle_rad = angle_degrees * (M_PI / 180.0); // chuyen do sang radian
    double cos_a = cos(angle_rad);
    double sin_a = sin(angle_rad);

    for (int i = 0; i < shape->num_vertices; i++) {
        // dich chuyen ve goc toa do (pivot lam goc)
        double translated_x = shape->vertices[i].x - pivot.x;
        double translated_y = shape->vertices[i].y - pivot.y;

        // quay
        double rotated_x = translated_x * cos_a - translated_y * sin_a;
        double rotated_y = translated_x * sin_a + translated_y * cos_a;

        // dich chuyen tro lai vi tri cu
        shape->vertices[i].x = rotated_x + pivot.x;
        shape->vertices[i].y = rotated_y + pivot.y;
    }
    calculateShapeCenter(shape); // cap nhat lai tam sau bien hinh
}

// ham phong to/thu nho hinh quanh diem pivot voi ti le scale_x, scale_y
void scaleShape(Shape* shape, Point2D pivot, double scale_x, double scale_y) {
    if (scale_x <= 0 || scale_y <= 0) {
        printf("Loi: Ti le phong to/thu nho phai duong.\n");
        return;
    }

    for (int i = 0; i < shape->num_vertices; i++) {
        // dich chuyen ve goc toa do (pivot lam goc)
        double translated_x = shape->vertices[i].x - pivot.x;
        double translated_y = shape->vertices[i].y - pivot.y;

        // co gian
        double scaled_x = translated_x * scale_x;
        double scaled_y = translated_y * scale_y;

        // dich chuyen tro lai
        shape->vertices[i].x = scaled_x + pivot.x;
        shape->vertices[i].y = scaled_y + pivot.y;
    }
    calculateShapeCenter(shape); // cap nhat lai tam sau bien hinh
}