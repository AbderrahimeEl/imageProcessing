#include"image.h"

int main(void)
{
int L=5,H=5,R=1,i,j;
int **kernel =(int**)malloc(3*sizeof(int*));
    for(i=0;i<3;i++)
    kernel[i] = ( int* )malloc(3 * sizeof(int));
 for(i=0;i<3;i++)
 {
    for(j=0;j<3;j++)
    kernel[i][j]=1;
 }
RGB_img image=initialize_values(L,H,R);
// image= initialize_values(L,H,R);
// initialize_rand(image);
// get_values(image);
initialize_rand(image);
Display_values(image);
RGB_img conv_image = applyfilter(&image,kernel,3);
Display_values(conv_image);
return 0;
}