#include <stdio.h>
#include <stdlib.h>
#include <cstring>
  
#define INP "input.inp"
#define OUT "output.out"
  
// read data in file input
int readData(int ***G, int *n, int *a, int *b) {
    FILE *fi = fopen(INP, "r");
    if (fi == NULL) {
        printf("file input not found!\n");
        return 0;
    }
    printf("start read file\n");
  
    fscanf(fi, "%d %d %d", n, a, b);
  
    *G = (int **) malloc((*n) * sizeof(int));
    for (int i = 0; i < *n; i++) {
        (*G)[i] = (int *) malloc((*n) * sizeof(int));
        for (int j = 0; j < *n; j++) {
            int x;
            fscanf(fi, "%d", &x);
            (*G)[i][j] = x;
        }
    }
  
    fclose(fi);
    printf("done read file\n");
    return 1;
}
  
// thuat toan dijkstra
int dijkstra(int **G, int n, int a, int b, int P[]) {
  
    /* Do mang tinh tu G[0][0] nen can giam vi tri
     di 1 don vi de tinh toan cho phu hop*/
    a--;
    b--;
  
    printf("start dijkstra\n");
  
    int* Len = (int *) malloc(n * sizeof(int));
    int* S = (int *) malloc(n * sizeof(int));
  
    int sum = 0;            // gia tri vo cung
  
    // tinh gia tri vo cung (sum)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += G[i][j];
        }
    }
  
    // dat vo cung cho tat ca cap canh khong noi voi nhau
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && G[i][j] == 0)
                G[i][j] = sum;
        }
    }
  
    for (int i = 0; i < n; i++) {
        Len[i] = sum;       // khoi tao do dai tu a toi moi dinh la vo cung
        S[i] = 0;           // danh sach cac diem da xet
        P[i] = a;           // dat diem bat dau cua moi diem la a
    }
  
    Len[a] = 0;             // dat do dai tu a -> a la 0
  
    int i;
  
    // tim duong di ngan nhat tu 1 dinh den moi dinh khac thi thay bang vong for:
    //for (int k = 0; k < n; k++)
    while (S[b] == 0) {                 // trong khi diem cuoi chua duoc xet
        for (i = 0; i < n; i++)          // tim 1 vi tri ma khong phai la vo cung
            if (!S[i] && Len[i] < sum)
                break;
  
        // i >=n tuc la duyet het cac dinh ma khong the tim thay dinh b -> thoat
        if (i >= n) {
            printf("done dijkstra\n");
            return 0;
        }
  
        for (int j = 0; j < n; j++) {    // tim diem co vi tri ma do dai la min
            if (!S[j] && Len[i] > Len[j])
                i = j;
        }
  
        S[i] = 1;                       // cho i vao danh sach xet roi
  
        for (int j = 0; j < n; j++) {    // tinh lai do dai cua cac diem chua xet
            if (!S[j] && Len[i] + G[i][j] < Len[j]) {
                Len[j] = Len[i] + G[i][j];      // thay doi len
                P[j] = i;                       // danh dau diem truoc no
            }
        }
    }
    printf("done dijkstra\n");
    return Len[b];
}
  
//  truy vet duong di
void back(int a, int b, int *P, int n, char *path) {
  
    //char *path = (char *) malloc((n * 10) * sizeof(char));
  
    /* Do mang tinh tu G[0][0] nen can giam vi tri
     di 1 don vi de tinh toan cho phu hop*/
    a--;
    b--;
  
    printf("start find path\n");
  
    int i = b;
    int point[n];   // danh sach cac dinh cua duong di
    int count = 0;
  
    /* Do ta dang tinh toan tu dinh 0 nen
     muon hien thi tu dinh 1 thi can dung i + 1 de phu hop */
  
    point[count++] = i + 1;
    while (i != a) {
        i = P[i];
        point[count++] = i + 1;
    }
  
    strcpy(path, "");
    char temp[10];
    for (i = count - 1; i >= 0; i--) {
        sprintf(temp, "%d", point[i]);
        strcat(path, temp);
  
        if (i > 0) {
            sprintf(temp, " --> ");
            strcat(path, temp);
        }
    }
  
    printf("done find path\n");
}
  
void outResult(int len, char* path) {
    FILE *fo = fopen(OUT, "w");
  
    if (len > 0) {
        fprintf(fo, "\nLength of %c to %c is %d\n", path[0],
                path[strlen(path) - 1], len);
    }
  
    fprintf(fo, "path: %s\n", path);
  
    fclose(fo);
}
  
int main() {
    int **G, n, a, b, len;
  
    if (readData(&G, &n, &a, &b) == 0) {
        return 0;
    }
  
    char *path = (char *) malloc((10 * n) * sizeof(char));
    int P[n];
  
    len = dijkstra(G, n, a, b, P);
  
    if (len > 0) {
        back(a, b, P, n, path);
        outResult(len, path);
    } else {
        char *path = (char *) malloc((n * 10) * sizeof(char));
        sprintf(path, "khong co duong di tu %d den %d\n", a, b);
        outResult(len, path);
    }
  
    printf("done - open file output to see result\n");
    return 0;
}
