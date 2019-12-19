#include <stdio.h>
#include <stdlib.h>
#include "image.h"

int main() {
    init(13, 10, 13, 10);
    add_form("A.txt", "_A.txt");
    add_form("B.txt", "_B.txt");
    add_form("C.txt", "_C.txt");

    printf("-------------------\n");
    search_X_form("A_BAD.txt");
    printf("-------------------\n");
    search_Y_form("_A_BAD.txt");
    printf("-------------------\n");
    search_X_form("B_BAD.txt");
    printf("-------------------\n");
    search_Y_form("_B_BAD.txt");
    printf("-------------------\n");
    search_X_form("C_BAD.txt");
    printf("-------------------\n");
    search_Y_form("_C_BAD.txt");

	system("pause");
    return 0;
}
