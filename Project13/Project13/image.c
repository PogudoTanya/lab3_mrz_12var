#include <stdio.h>
#include <stdlib.h>
#include "image.h"


int **W;
int X_width;
int Y_width;
int y_size;
int x_size;

void init(int _width, int _heigth, int _o_x_size, int _o_y_size) {
    x_size = _width * _heigth;
    X_width = _width;
    y_size = _o_y_size * _o_x_size;
    Y_width = _o_x_size;


    W = (int **) malloc(x_size * sizeof(int *));
    for (int i = 0; i < x_size; i++)
        W[i] = (int *) malloc(y_size * sizeof(int));

    for (int i = 0; i < x_size; i++)
        memset(W[i], 0, y_size * sizeof(int));

}

void add_form(char *name, char *form_name) {
	FILE *file;
    fopen_s(&file, name, "r");
    int *X = (int *) malloc(x_size * sizeof(int));
    create_input_vector(file, X, x_size);
    fclose(file);

    fopen_s(&file, form_name, "r");
    int *Y = (int *) malloc(x_size * sizeof(int));
    create_input_vector(file, Y, y_size);
    fclose(file);

    for (int index = 0; index < x_size; index++)
        for (int j = 0; j < y_size; j++)
            W[index][j] += X[index] * Y[j];

    free(X);
    free(Y);
}


void create_input_vector(FILE *file, int *input, int size) {//ÄÅÀÅÒ ÂÅÅÊÒÎÐ ÈÇ ÊÀÐÒÈÍÊÈ
    char ch;
    for (int index = 0; index < size; index++) {
        fscanf_s(file, "%c", &ch);
        if (ch == '.') {
            input[index] = 1;
        } else if (ch == '#') {
            input[index] = -1;
        } else {
            index--;
        }
    }
}

void calculate_res_y(int *res_x, int *res_y) {
    for (int i = 0; i < y_size; i++) {
        for (int j = 0; j < x_size; j++) {
            res_y[i] += res_x[j] * W[j][i];
        }
        if (res_y[i] > 0)
            res_y[i] = 1;
        if (res_y[i] < 0)
            res_y[i] = -1;
    }
}

void calculate_res_x(int *res_x, int *res_y) {
    for (int i = 0; i < x_size; i++) {
        for (int j = 0; j < y_size; j++) {
            res_x[i] += res_y[j] * W[i][j];
        }
        if (res_x[i] > 0)
            res_x[i] = 1;
        if (res_x[i] < 0)
            res_x[i] = -1;
    }

}

int calculateEnergy(int *res_x, int *res_y) {
    int Energy = 0;
    int *temp = (int *) malloc(y_size * sizeof(int));
    for (int i = 0; i < y_size; i++)
        temp[i] = 0;

    for (int i = 0; i < y_size; i++) {
        temp[i] = 0;
        for (int j = 0; j < x_size; j++) {
            temp[i] += W[j][i] * res_y[i];
        }

    }

    for (int i = 0; i < y_size; i++) {
        for (int j = 0; j < x_size; j++) {
            Energy += temp[i] * res_x[j];
        }

    }

    free(temp);
    return Energy;
}


void search_X_form(char *name) {
	FILE *file;
	fopen_s(&file, name, "r");
    int *res_x = (int *) malloc(x_size * sizeof(int));
    int *res_y = (int *) malloc(y_size * sizeof(int));
    for(int i = 0; i<y_size; i++) res_y[i] = 0;
    create_input_vector(file, res_x, x_size);
    fclose(file);

    int Energy_old = -1;
    int iteration = 0;
    int Energy = 0;

    while (Energy != Energy_old) {
        iteration++;
        Energy_old = Energy;

        calculate_res_y(res_x, res_y);
        calculate_res_x(res_x, res_y);

        Energy = calculateEnergy(res_x, res_y);

    }

    printf("iteration: %i\n", iteration);

    print_res(res_y,y_size,Y_width);

    free(res_x);
    free(res_y);
}


void search_Y_form(char *name) {
	FILE *file;
	fopen_s(&file, name, "r");
    int *res_x = (int *) malloc(x_size * sizeof(int));
    int *res_y = (int *) malloc(y_size * sizeof(int));
    for(int i = 0; i<x_size; i++) res_x[i] = 0;
    create_input_vector(file, res_y, y_size);
    fclose(file);

    int iteration = 0;
    int Energy_old = -1;
    int Energy = 0;
    while (Energy != Energy_old) {
        iteration++;
        Energy_old = Energy;

        calculate_res_x(res_x, res_y);
        calculate_res_y(res_x, res_y);

        Energy = calculateEnergy(res_x, res_y);

    }

    printf("iteration: %i\n", iteration);
    print_res(res_x,x_size,X_width);

    free(res_x);
    free(res_y);

}


void print_res(int *array, int size,int width) {
    for (int j = 0; j < size; j++) {
        if (array[j] == 1) {
            printf(".");
        }
        if (array[j] == -1) {
            printf("#");
        }
        if ((j + 1) % (width) == 0)
            printf("\n");
    }
}


