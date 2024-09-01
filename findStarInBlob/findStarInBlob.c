#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int table[MAX][MAX];
int visited[MAX][MAX];
int rows, cols;

int directions[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

void DFS(int row, int col, int *count){
    visited[row][col] = 1;
    (*count)++;

    for (int i = 0; i < 8; i++){
        int newRow = row + directions[i][0], newCol = col + directions[i][1];

        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && table[newRow][newCol] == 1 && !visited[newRow][newCol])
            DFS(newRow, newCol, count);
    }
}

int main()
{
    int blobSizes[MAX * MAX];
    int blobCount = 0;

    scanf("%d %d", &rows, &cols);

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            table[i][j] = 0;
            visited[i][j] = 0;
        }
    }

    int row, col;

    while (scanf("%d %d", &row, &col) && row != -1)
        table[row][col] = 1;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (table[i][j] == 1 && !visited[i][j]){
                int count = 0;
                DFS(i, j, &count);
                blobSizes[blobCount++] = count;
            }
        }
    }

    for (int i = 0; i < blobCount; i++){
        for (int j = i + 1; j < blobCount; j++){
            if (blobSizes[j] < blobSizes[i]){
                int temp = blobSizes[i];
                blobSizes[i] = blobSizes[j];
                blobSizes[j] = temp;
            }
        }
    }

    printf("%d ", blobCount);

    for (int i = 0; i < blobCount; i++)
        printf("%d ", blobSizes[i]);

    return 0;
}