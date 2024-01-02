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

RGB_img get_values();

RGB_img initializeMatrixFromFile(const char *filename);

void displayImage2(RGB_img image);

RGB_img applyfilter(RGB_img *image,int kernel[3][3] ,int KERNEL_SIZE) ;

void ImageToFile(RGB_img image,char *FileName);

void setKernel(int Kernel[3][3], int Choice);

int fileExists(const char *fileName);

void freeRGBImage(RGB_img *image);

RGB_img convertToGrayscale(RGB_img originalImage);