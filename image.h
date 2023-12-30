#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// la structure RGB_img

typedef struct  {
    int L,H,R;
    unsigned char **img[3]; 
}RGB_img ;

// initialisation de l'immage 
RGB_img initialize_values(int L,int H,int R);
void initialize_rand(RGB_img image);
void Display_values(RGB_img image);
void get_values(RGB_img image);
RGB_img initializeMatrixFromFile(const char *filename);
void displayImage2(RGB_img image);
RGB_img applyfilter(RGB_img *image,int **kernel ,int KERNEL_SIZE) ;

