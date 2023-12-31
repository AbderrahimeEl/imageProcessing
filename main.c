#include"image.h"
#include<string.h>


int main(void){
   int Choice;
printf("\n saisir \n1 to get a image from a text file ");
printf("\n2 to saisir  an  image  ");
printf("\n3 to get a random image ");
scanf("%d",&Choice);

int L = 5, H = 5, R = 1, i, j;
RGB_img image = initialize_values(L, H, R);

char FileName[30];
int kernel[3][3] = {
   {0,1,0},
   {1,1,1},
   {0,1,0},
};
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

printf("\nwhat filter you want to aply to the image  :\n");
printf("enter 1 for blur \n");
Display_values(image);
RGB_img ImgWithFilter = applyfilter(&image, kernel, 3);
Display_values(ImgWithFilter);

return 0;
}
