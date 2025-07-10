#include <stdio.h>
//write a function to geereate matrix n*n from 1 to n square using spirale form
void genereateMatrix(int n) {
    //at the first we need to define the matrix
    int matrix[n][n];
    //define the top bottom right and left of the matrix
    int top = 0;
    int bottom = n - 1;
    int right = n - 1;
    int left = 0;
    int num = 1;
    //get a loop for the condition
    //we have 2 condition
    //1-> top <= bottom
    //2-> left <= right
    while(top <= bottom && left <= right) {
        //get the ways to fills the the top rows
        for (int i = left; i <= right; i++) {
            matrix[top][i] = num++;
        }
        top++;
        //fill the right column
          for (int i = top; i <= bottom; i++) {
            matrix[i][right] = num++;
        }
        right--;
        //just gowing to fill the left column
        // fill bottom row (right to left)
        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                matrix[bottom][i] = num++;
            }
            bottom--;
        }

        //just going to work with the bottom rows
        // fill left column (bottom to top)
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                matrix[i][left] = num++;
            }
            left++;
        }
    }
    printf("The spiral matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int n;
    printf("Enter number n: ");
    scanf("%d", &n);
    genereateMatrix(n);
    return 0;
}
