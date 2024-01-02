#include"image.h"
#include<string.h>


int main(void){
   int Choice;

printf("\n saisir \n1 to get a image from a text file ");
printf("\n2 to saisir  an  image  ");
printf("\n3 to get a random image ");
printf("\n\tChoice: ");
scanf("%d", &Choice);

int L = 5, H = 5, R = 1, i, j;
RGB_img image = initialize_values(L, H, R);
RGB_img Newimage;

char FileName[30];
int Kernel[3][3] ;
switch (Choice)
{
case 1:
   printf("\nenter the name of the file with the format .txt :");
   fflush(stdin);
   gets(FileName);
   image = initializeMatrixFromFile(FileName);
   break;

case 2:
   printf("\nenter the image informations :");
   image = get_values();
   break;

case 3:
   printf("\nenter the image informations :");
   printf("\nR:");
    scanf("%d", &R);
    printf("\nL:");
    scanf("%d", &L);
    printf("\nH:");
    scanf("%d", &H);
   image = initialize_values(L, H, R);
   initialize_rand(image);
   break;

default:
   break;
}
printf("\n enter \n1 to to apply a filter to the image  ");
printf("\n2 o extract graystyle image");
printf("\n\tChoice: ");
scanf("%d", &Choice);
if(Choice == 1 || Choice ==2){
if(Choice ==1 )
{

    printf("\nWhat filter do you want to apply to the image?\n");
    printf("Enter 1 for Identity Filter\n");
    printf("Enter 2 for Gaussian Blur\n");
    printf("Enter 3 for Sobel Horizontal\n");
    printf("Enter 4 for Sobel Vertical\n");
    printf("Enter 5 for Sharpening Filter\n");
    printf("Enter 6 for Emboss Filter\n");
    printf("Enter 7 for Box Blur (Average)\n");
    printf("\n\tChoice: ");
    scanf("%d", &Choice);

    setKernel(Kernel, Choice);
    Newimage = applyfilter(&image, Kernel, 3);
}
if(Choice == 2)

Newimage = convertToGrayscale(image);

    
printf("original image  :");

Display_values(image);

printf("\n\n\tnew image : ");

Display_values(Newimage);

printf("\n\tenter the name of the file to save the new image ");
fflush(stdin);
gets(FileName);
ImageToFile(Newimage,FileName);
if(fileExists(FileName))
printf("\nDone image is enregstred in %s",FileName);
else 
printf("\nError");
freeRGBImage(&Newimage);
}
else{
printf("\nError");
freeRGBImage(&image);
}

return 0;
}
