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
void updateMatrixValueInFile(const char *filename, int rows, int cols, int targetRow, int targetCol, int newValue) {
    FILE *f = fopen(filename, "rb+"); // open for read and write (binary)
    if (f == NULL) {
        printf("Cannot open file!\n");
        return;
    }

    // Calculate offset in bytes
    int index = targetRow * cols + targetCol;
    long offset = index * sizeof(int);

    // Seek to the position
    fseek(f, offset, SEEK_SET);

    // Write the new value at that position
    fwrite(&newValue, sizeof(int), 1, f);

    fclose(f);
}

int main() {
    int rows, columns;

    // Prompt for matrix size
    printf("Enter the number of rows: ");
    scanf("%d", &rows);  // ❌ Removed newline (\n), which causes scanf to wait for Enter

    printf("Enter the number of columns: ");
    scanf("%d", &columns);

    // Dynamic allocation of 2D matrix
    int **matrix = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(columns * sizeof(int));
    }

    // Fill the matrix with incrementing values
    int num = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = num++;
        }
    }

    // Save the matrix to file
    stokerLaMatrice(matrix, rows, columns);

    // Find and store max value from matrix to file (separate file)
    foundMaxOfMatrix(matrix, rows, columns);

    // Optional: update any matrix value in file (example: update [1][1] to 999)
     updateMatrixValueInFile("mat.dat", rows, columns, 1, 1, 999);

    // Free the dynamically allocated memory
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
