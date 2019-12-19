#ifndef RNN_H_INCLUDED
#define RNN_H_INCLUDED
void init(int _width, int _heigth, int _o_x_size, int _o_y_size);
void add_form(char* name,char* form_name);
void search_X_form(char* name);
void search_Y_form(char* name);
int calculateEnergy(int* res_x, int* res_y);
void create_input_vector(FILE *file, int *input, int size);
void print_res(int *array, int size,int width);
#endif 
