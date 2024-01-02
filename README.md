# Image Processing Application

## Overview
This application allows users to perform various image processing operations on images. It utilizes a custom image struct (`RGB_img`) and provides functionalities for applying filters, converting images to grayscale, and handling image files.

## Prerequisites

- Ensure the `image.h` header file is included in the project directory.
- The application relies on the `RGB_img` structure to represent images.

## Usage
1. Run the application.
2. Choose an option:
   - Select `1` to load an image from a text file.
   - Choose `2` to enter image information manually.
   - Pick `3` to generate a random image with user-defined dimensions.
3. After loading an image, choose an operation:
   - Enter `1` to apply a filter (Identity, Gaussian Blur, Sobel Horizontal, Sobel Vertical, Sharpening, Emboss, Box Blur).
   - Choose `2` to convert the image to grayscale.
4. View the original and processed images on the console.
5. Save the processed image by entering a filename when prompted.

## File Structure
- `image.h`: Contains declarations of functions and structures used for image processing.
- `image.c`: Implements image processing functions.
- `main.c`: Houses the main application logic, including user interaction and calling image processing functions.
- `README.md`: This file.
-  `image.txt` : text file for the image compnents

## Functions
- `initialize_values`: Initializes an image structure with user-defined dimensions.
- `initializeMatrixFromFile`: Loads an image from a text file.
- `get_values`: Allows manual input of image information.
- `initialize_rand`: Generates a random image.
- `setKernel`: Sets a filter kernel for image processing.
- `applyfilter`: Applies a filter to the image.
- `convertToGrayscale`: Converts the image to grayscale.
- `Display_values`: Displays image information on the console.
- `ImageToFile`: Saves the image to a file.
- `fileExists`: Checks if a file exists in the directory.
- `freeRGBImage`: Frees memory allocated for the image structure.

## Notes
- Ensure proper file paths are provided when loading/saving images.
- Make sure to handle memory allocation and deallocation properly to avoid memory leaks.
