#include <stdio.h>

#define SIZE 20
char matrix[SIZE][SIZE];
int center[2];

void initialize_matrix() {
    int y = 0;
    int x = 0;

    while (y < SIZE) {
        x = 0;
        while (x < SIZE) {
            matrix[y][x] = '-';
            x++;
        }
        y++;
    }
}

void set_objects() {
    matrix[1][5] = 'O';
    matrix[2][1] = 'O';
    matrix[5][2] = 'O';
    matrix[8][7] = 'O';
    matrix[6][14] = 'O';
}

void print_matrix() {
    int i = 0;
    int j = 0;

    while (i < SIZE) {
        j = 0;
        while (j < SIZE) {
            if (matrix[i][j] == 'O')
                printf("\033[33m%c\033[0m", matrix[i][j]);
            else if(matrix[i][j] == 'x')
                printf("\033[31m%c\033[0m", matrix[i][j]);
            else
                printf("%c", matrix[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

void put_corner() {
    int i, j;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if ((i == 0 || j == 0 || i == SIZE - 1 || j == SIZE - 1) && matrix[i][j] != 'O') {
                matrix[i][j] = 1 + '0';
            }
        }
    }
}

int look_around_for(int a, int b, char c) {
    int i = a - 1;
    int j = b - 1;
    while (i <= a + 1) {
        j = b - 1;
        while (j <= b + 1) {
            if (!(i == a && j == b) && matrix[i][j] == c)
                return 1;
            j++;
        }
        i++;
    }
    return 0;
}

void put_objects_around() {
    int i, j;

    for (i = 1; i < SIZE; i++) {
        for (j = 1; j < SIZE; j++) {
            if (matrix[i][j] == '-' && look_around_for(i, j, 'O') == 1) {
                matrix[i][j] = 1 + '0';
            }
        }
    }
}

int check_empty_cell() {
    int i, j;

    for (i = 1; i < SIZE; i++) {
        for (j = 1; j < SIZE; j++) {
            if (matrix[i][j] == '-') {
                return 1;
            }
        }
    }
    return 0;
}

void put_numbers() {
    int k = 2;
    int i, j;

    put_corner();
    put_objects_around();
    while (check_empty_cell() == 1) {
        for (i = 1; i < SIZE; i++) {
            for (j = 1; j < SIZE; j++) {
                if (matrix[i][j] == '-' && look_around_for(i, j, k - 1 + '0') == 1) {
                    matrix[i][j] = k + '0';
                }
            }
        }
        k++;
    }
}

int find_max_number() {
    int i, j;
    int current = 0;

    for (i = 1; i < SIZE; i++) {
        for (j = 1; j < SIZE; j++) {
            if (matrix[i][j] > current && matrix[i][j] != 'O') {
                current = matrix[i][j];
            }
        }
    }
    return current - '0';
}

int look_for_four(int max) {
    int i, j;
    
    for (i = 1; i < SIZE; i++) {
        for (j = 1; j < SIZE; j++) {
            if (matrix[i][j] == max + '0' && matrix[i + 1][j] == max + '0' &&
                matrix[i][j + 1] == max + '0' && matrix[i + 1][j + 1] == max + '0') 
            {
                center[0] = i;
                center[1] = j;
                return 1;
            }
        }
    }
    return 0;
}

void draw_square() {
    int max_number = find_max_number();

    int square_minus_x = max_number - 1;
    int square_plus_x = max_number - 1;
    int square_minus_y = max_number - 1;
    int square_plus_y = max_number - 1;

    if (look_for_four(max_number) == 1) {
        square_plus_x++;
        square_minus_y++;
    }
    
    int i = center[0] - square_plus_y;
    int j = center[1] - square_minus_x;
    while(i <= center[0] + square_minus_y) {
        j = center[1] - square_minus_x;
        while(j <= center[1] + square_plus_x) {
            matrix[i][j] = 'x';
            j++;
        }
        i++;
    }
}

void remove_numbers(){
    int i, j;
    
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if(matrix[i][j] != 'O' && matrix[i][j] != 'x')
                matrix[i][j] = '-';
        }
    }
}

int main() {
    initialize_matrix();
    set_objects();
    print_matrix();
    printf("\n\n\n");
    put_numbers();
    draw_square();
    remove_numbers();
    print_matrix();
}
