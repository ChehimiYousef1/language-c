#include <stdio.h>
#include <stdlib.h>

void stokerLaMatrice(int **matrice2D, int rows, int columns) {
    FILE *f = fopen("mat.dat", "wb"); // open in write binary mode
    if (f == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    // Write dimensions
    fwrite(&rows, sizeof(int), 1, f);
    fwrite(&columns, sizeof(int), 1, f);

    // Write matrix data row by row
    for (int i = 0; i < rows; i++) {
        fwrite(matrice2D[i], sizeof(int), columns, f);
    }

    fclose(f);
}

//found the max and store it on the file
//and to get the position
void foundMaxOfMatrix(int **matrice2d, int rows, int columns) {
    FILE *f = fopen("mat.dat", "wb");
    if (f == NULL) {
        printf("Cannot open file!\n");
        return;
    }

    int max = matrice2d[0][0];
    int maxRow = 0, maxCol = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (matrice2d[i][j] > max) {
                max = matrice2d[i][j];
                maxRow = i;
                maxCol = j;
            }
        }
    }

    // Store position and max value
    fwrite(&maxRow, sizeof(int), 1, f);
    fwrite(&maxCol, sizeof(int), 1, f);
    fwrite(&max, sizeof(int), 1, f);

    fclose(f);
}
int main() {
    int rows,colunms;
    printf("Enter the number of rows you want it : ");
    scanf("%d \n",&rows);
    printf("Enter the number of colunms you want it : ");
    scanf("%d \n",&colunms);
    //releated to define the matrix
    //dynamic allocation of the matrix
    int ** matrix = malloc(rows*(sizeof(int*)));
    for(int i = 0;i < rows;i++){
        matrix[i] = malloc(colunms * sizeof(int*));
    }
    //get adding the value of the matrix
    int num = 1;
    for(int i = 0;i < rows;i++){
        for(int j = 0;j < colunms;j++){
            matrix[i][j] = num++;
        }
    }
