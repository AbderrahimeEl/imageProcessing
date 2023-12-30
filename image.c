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
                image.img[i][j][k]=1;
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
            printf("(%d-%d-%d)  ", image.img[i][j][0],image.img[i][j][1],image.img[i][j][2]);
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

RGB_img initializeMatrixFromFile(const char *filename) {
    RGB_img image;

    FILE *file = fopen(filename, "r"); // Open the file in read mode
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Read L, H, R values from the file
    fscanf(file, "%d %d %d", &image.L, &image.H, &image.R);

    // Allocate memory for the matrix
    int i, j;
    for (i = 0; i < 3; i++) {
        image.img[i] = (unsigned char **)malloc(image.L * sizeof(unsigned char *));
        if (image.img[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        for (j = 0; j < image.L; j++) {
            image.img[i][j] = (unsigned char *)malloc(image.H * sizeof(unsigned char));
            if (image.img[i][j] == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            // Read pixel values from the file
            for (int k = 0; k < image.H; k++) {
                fscanf(file, "%hhu", &image.img[i][j][k]);
            }
        }
    }

    fclose(file); // Close the file

    return image;
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
            // Extract the selected component (R/G/B) and assign it as the grayscale value
            grayscaleImg[i][j] = originalImage.img[componentIndex][i][j];
        }
    }

    // Display or use the grayscaleImg matrix as needed
    // You can print the grayscale image or perform further operations here

    // Free memory for the grayscale image
    for (i = 0; i < originalImage.L; i++) {
        free(grayscaleImg[i]);
    }
    free(grayscaleImg);
}


// Function to perform convolution on the image and return a new image
RGB_img applyfilter(RGB_img *image,int **kernel ,int KERNEL_SIZE) {
    int i, j, k, l, m;
    int R = image->R, H = image->H, L = image->L;
    unsigned char sum;
    int kernelCenter = KERNEL_SIZE / 2;
    
    // Create a new image to store the result of convolution
    RGB_img resultImage = initialize_values(L, H, R);


    // Apply convolution to each channel (R, G, B)
    for (k = 0; k < 3; k++) {
        for (i = 0; i < R*(H-1); i++) {
            for (j = 0; j < R*(L-1); j++) {
                sum = 0;
                for (l = -kernelCenter; l <= kernelCenter; l++) {
                    for (m = -kernelCenter; m <= kernelCenter; m++) {
                        if (i + l >= 0 && i + l < R*(H-1) && j + m >= 0 && j + m < R*(L-1)) {
                            sum += kernel[kernelCenter + l][kernelCenter + m] * (image->img[k][i + l][j + m]);
                        }
                    }
                }
                resultImage.img[k][i][j] = sum; // Store the result in the new image
            }
        }
    }
printf("\ntest \n");
    return resultImage;
}

