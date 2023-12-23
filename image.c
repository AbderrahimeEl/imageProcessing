#include"image.h"
RGB_img initialize_values(int L,int H,int R)
{
    RGB_img image;
    int i,j;
    image.H=H;
    image.L=L;
    image.R=R;
    for(i=0;i<3;i++)
    {
        image.img[i]=(unsigned char**)malloc(R*(H-1)*sizeof(unsigned char*));
        for(j=0;j<R*(H-1);j++)
        {
            image.img[i][j]=(unsigned char*)malloc(R*(L-1)*sizeof(unsigned char));
        }
    }
    return image;
}
void initialize_rand(RGB_img image)
{
    int i,j,k;
    for(i=0;i<3;i++)
    {
        for(j=0;j<image.R*(image.H-1);j++)
        {
            for(k=0;k<image.R*(image.L-1);k++)
            {
                image.img[i][j][k]=rand()%256;
            }
        }
    }
}

void Display_values(RGB_img image)
{
    int i,j,k;
    for(i=0;i<3;i++)
    {
        for(j=0;j<image.R*(image.H-1);j++)
        {
            for(k=0;k<image.R*(image.L-1);k++)
            {
                printf("  %d", image.img[i][j][k]);
            }
            printf("\n");
        }
        printf("\n\n");
    }
}

void get_values(RGB_img image)
{
    int i,j,k;
    printf("\n\n values :\n");
    for(i=0;i<3;i++)
    {
        for(j=0;j<image.R*(image.H-1);j++)
        {
            for(k=0;k<image.R*(image.L-1);k++)
            {
                printf("img[%d][%d][%d] :",i,j,k);
                scanf("%d",&image.img[i][j][k]);
            }
            printf("\n");
        }
        printf("\n\n");
    }
}


