#include <stdio.h>

// Function to generate and print a matrix
void generateMatrix(int n) {
    int matrix[n][n];
    int num = n;

    printf("[\n");
    for (int i = 0; i < n; i++) {
        printf("  [ ");
        for (int j = 0; j < n; j++) {
            matrix[i][j] = num++;
            printf("%d ", matrix[i][j]);
        }
        printf("]\n");
    }
    printf("]\n");
}

int main() {
    printf("Try programiz.pro\n");
    generateMatrix(3);
    return 0;
}
