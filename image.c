#include"image.h"
#include<unistd.h>
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
                image.img[i][j][k]=rand()%255;
            }
        }
    }
}

void Display_values(RGB_img image)
{
    int i,j,k=10;
    for(i=0; i < (image.R)*(image.L-1); i++)
    {
        // printf("\nL%d\tH%d\tR%d\timage.R*(image.H-1)=%d",image.L,image.H,image.R,image.R*(image.H-1));
        printf("\n\n");
        for(j=0;j<(image.R)*(image.L-1);j++)
        {
            printf("(%3d-%3d-%3d)  ", image.img[0][i][j],image.img[1][i][j],image.img[2][i][j]);
            // printf("\t%d\t%d\t%d",i,j,k);
        }
    }
    
}

RGB_img get_values()
{
    int i, j, k, L, H, R;
    RGB_img image;
    printf("\nR:");
    scanf("%d", &R);
    printf("\nL:");
    scanf("%d", &L);
    printf("\nH:");
    scanf("%d", &H);

    image = initialize_values(L, H, R);

    printf("\n\n values :\n");

    for(i=0;i<3;i++)
    {
        for(j=0;j<R*(H-1);j++)
        {
            for(k=0;k<R*(L-1);k++)
            {
                printf("img[%d][%d][%d] :",i,j,k);
                scanf("%d",&image.img[i][j][k]);
            }
            printf("\n");
        }
        printf("\n\n");
    }
}

RGB_img initializeMatrixFromFile(const char *filename) {
    RGB_img image;
    int L,H,R;
    printf("\n%s \n",filename);

    FILE *file = fopen(filename, "r"); // Open the file in read mode
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Read L, H, R values from the file
    fscanf(file, "%d %d %d", &L, &H, &R);
    
    // Allocate memory for the matrix
    image= initialize_values(L,H,R);


    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < R*(H-1); j++) {
            // Read pixel values from the file
            for (int k = 0; k < R*(L-1) ; k++) {
                fscanf(file, "%d", &image.img[i][j][k]);
            }
        }
    }

    fclose(file); // Close the file

    return image;
}

void ImageToFile(RGB_img image,char *FileName)
{
    FILE *File;
    int i,j,k;
    File = fopen(FileName,"w");
    if(File==NULL)
    {
        fprintf(stderr,"error opening file %s\n",FileName);
        exit(EXIT_FAILURE);
    }
    fprintf(File,"\n %d  %d  %d\n",image.L, image.H, image.R);
    for(i=0;i<3;i++)
    {
        for( j = 0; j < image.R * (image.H - 1); j++)
        {
            for(k = 0; k < image.R * (image.L - 1); k++)
            {
                fprintf(File, " %d", image.img[i][j][k]);
            }
            fprintf(File, "%c", '\n');
        }
        fprintf(File, "%c", '\n');
    }
    fclose(File);
}

void extractComponentToGrayscale(RGB_img originalImage, int componentIndex) {

    if (componentIndex < 0 || componentIndex >= 3) {
        printf("Invalid component index\n");
        return;
    }

    int i, j;
    unsigned char **grayscaleImg = (unsigned char **)malloc(originalImage.L * sizeof(unsigned char *));
    if (grayscaleImg == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < originalImage.L; i++) {
        grayscaleImg[i] = (unsigned char *)malloc(originalImage.H * sizeof(unsigned char));
        if (grayscaleImg[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        for (j = 0; j < originalImage.H; j++) {
            grayscaleImg[i][j] = originalImage.img[componentIndex][i][j];
        }
    }

    for (i = 0; i < originalImage.L; i++) {
        free(grayscaleImg[i]);
    }
    free(grayscaleImg);
}

RGB_img applyfilter(RGB_img *image,int kernel[3][3] ,int KERNEL_SIZE) {
    int i, j, k, l, m, n;
    int R = image->R, H = image->H, L = image->L;
    int length,hight;
    unsigned char sum;
    int kernelCenter = KERNEL_SIZE / 2;

    RGB_img resultImage = initialize_values(L, H, R);

length=R*(H-1);
hight=R*(L-1);

for (k = 0; k < 3; k++){
    for (i = 0; i < length; i++) 
    {
        for (j = 0; j < hight; j++) 
        { 
            resultImage.img[k][i][j] = 0;
            for (m = -kernelCenter; m <= kernelCenter; m++) 
            {
                for (n = -kernelCenter; n <= kernelCenter; n++) {
                    if (i-m>=0 && i- m <length && j-n >= 0 && j- n < hight &&
                    m+kernelCenter>= 0 && m + kernelCenter < KERNEL_SIZE && n + kernelCenter >= 0 && n + kernelCenter <KERNEL_SIZE) 
                    {
                       resultImage.img[k][i][j] += image->img[k][i-m][j-n]*kernel[m+kernelCenter][n+kernelCenter];
                    }
                }
            }
        }
    }
}


    return resultImage;
}

void setKernel(int Kernel[3][3], int Choice) {
    switch (Choice) {
        case 1:
            printf("Applying Identity Filter\n");
            // Identity Filter
            Kernel[0][0] = 0;
            Kernel[0][1] = 0;
            Kernel[0][2] = 0;
            Kernel[1][0] = 0;
            Kernel[1][1] = 1;
            Kernel[1][2] = 0;
            Kernel[2][0] = 0;
            Kernel[2][1] = 0;
            Kernel[2][2] = 0;
            break;

        case 2:
            printf("Applying Gaussian Blur\n");
            // Gaussian Blur
            Kernel[0][0] = 1;
            Kernel[0][1] = 2;
            Kernel[0][2] = 1;
            Kernel[1][0] = 2;
            Kernel[1][1] = 4;
            Kernel[1][2] = 2;
            Kernel[2][0] = 1;
            Kernel[2][1] = 2;
            Kernel[2][2] = 1;
            break;

        case 3:
            printf("Applying Sobel Horizontal\n");
            // Sobel Horizontal
            Kernel[0][0] = -1;
            Kernel[0][1] = -2;
            Kernel[0][2] = -1;
            Kernel[1][0] = 0;
            Kernel[1][1] = 0;
            Kernel[1][2] = 0;
            Kernel[2][0] = 1;
            Kernel[2][1] = 2;
            Kernel[2][2] = 1;
            break;

        case 4:
            printf("Applying Sobel Vertical\n");
            // Sobel Vertical
            Kernel[0][0] = -1;
            Kernel[0][1] = 0;
            Kernel[0][2] = 1;
            Kernel[1][0] = -2;
            Kernel[1][1] = 0;
            Kernel[1][2] = 2;
            Kernel[2][0] = -1;
            Kernel[2][1] = 0;
            Kernel[2][2] = 1;
            break;

        case 5:
            printf("Applying Sharpening Filter\n");
            // Sharpening Filter
            Kernel[0][0] = -1;
            Kernel[0][1] = -1;
            Kernel[0][2] = -1;
            Kernel[1][0] = -1;
            Kernel[1][1] = 9;
            Kernel[1][2] = -1;
            Kernel[2][0] = -1;
            Kernel[2][1] = -1;
            Kernel[2][2] = -1;
            break;

        case 6:
            printf("Applying Emboss Filter\n");
            // Emboss Filter
            Kernel[0][0] = -2;
            Kernel[0][1] = -1;
            Kernel[0][2] = 0;
            Kernel[1][0] = -1;
            Kernel[1][1] = 1;
            Kernel[1][2] = 1;
            Kernel[2][0] = 0;
            Kernel[2][1] = 1;
            Kernel[2][2] = 2;
            break;

        case 7:
            printf("Applying Box Blur (Average)\n");
            // Box Blur (Average)
            Kernel[0][0] = 1;
            Kernel[0][1] = 1;
            Kernel[0][2] = 1;
            Kernel[1][0] = 1;
            Kernel[1][1] = 1;
            Kernel[1][2] = 1;
            Kernel[2][0] = 1;
            Kernel[2][1] = 1;
            Kernel[2][2] = 1;
            break;

        default:
            printf("Invalid choice\n");
            break;
    }
}

void freeRGBImage(RGB_img *image) {
    if (image != NULL) {
        for (int i = 0; i < 3; ++i) {
            if (image->img[i] != NULL) {
                for (int j = 0; j < image->R*(image->H-1); ++j) {
                    if (image->img[i][j] != NULL) {
                        free(image->img[i][j]);
                        image->img[i][j] = NULL;
                    }
                }
                free(image->img[i]);
                image->img[i] = NULL;
            }
        }
        // No need to free 'image' itself as it's not dynamically allocated
    }
}

int fileExists(const char *fileName) {
    if (access(fileName, F_OK) == 0) {
        return 1; // File exists
    } else {
        return 0; // File doesn't exist
    }
}


RGB_img convertToGrayscale(RGB_img originalImage) {
    
    RGB_img grayscaleImage = initialize_values(originalImage.L, originalImage.H, originalImage.R);

    for (int i = 0; i < originalImage.R*  (originalImage.H - 1); ++i) {
        for (int j = 0; j < originalImage.R*  (originalImage.L - 1); ++j) {
            unsigned char r = originalImage.img[0][i][j];
            unsigned char g = originalImage.img[1][i][j];
            unsigned char b = originalImage.img[2][i][j];
            unsigned char grayscale = (unsigned char)(0.21 * r + 0.72 * g + 0.07 * b);

            grayscaleImage.img[0][i][j] = grayscale;
            grayscaleImage.img[1][i][j] = grayscale;
            grayscaleImage.img[2][i][j] = grayscale;
        }
    }

    return grayscaleImage;
}
