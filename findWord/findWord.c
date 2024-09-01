#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 15 

void inputTableWord(char **table, char *word){
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
            scanf(" %c", &table[i][j]);
        }
    }
    scanf("%s", word);
}

void printTable(char **table, int **foundPositions){
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
            if (foundPositions[i][j]){
                printf("%c", table[i][j]);
            }
            else{
                printf("*");
            }
        }
        printf("\n");
    }
}

int isValid(int x, int y){
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

int searchInDirection(char **table, char *word, int x, int y, int dx, int dy, int **foundPositions){
    int len = strlen(word);

    for (int k = 0; k < len; ++k){
        int nx = x + k * dx;
        int ny = y + k * dy;
        if (!isValid(nx, ny) || table[nx][ny] != word[k]){
            return 0;
        }
    }

    for (int k = 0; k < len; ++k){
        int nx = x + k * dx;
        int ny = y + k * dy;
        foundPositions[nx][ny] = 1;
    }
    return 1;
}

int findWord(char **table, char *word, int **foundPositions){
    int directions[8][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}, {0, -1}, {-1, 0}, {-1, -1}, {-1, 1}};

    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
            if (table[i][j] == word[0]){
                for (int d = 0; d < 8; ++d){
                    if (searchInDirection(table, word, i, j, directions[d][0], directions[d][1], foundPositions)){
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int main(){
    char **table = (char **)malloc(SIZE * sizeof(char *));
    int **foundPositions = (int **)malloc(SIZE * sizeof(int *));

    for (int i = 0; i < SIZE; ++i){
        table[i] = (char *)malloc(SIZE * sizeof(char));
        foundPositions[i] = (int *)calloc(SIZE, sizeof(int));
    }

    char word[50];
    inputTableWord(table, word);
    int found = findWord(table, word, foundPositions);
    printTable(table, foundPositions);

    for (int i = 0; i < SIZE; ++i){
        free(table[i]);
        free(foundPositions[i]);
    }

    free(table);
    free(foundPositions);

    return 0;
}
