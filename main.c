#include"image.h"

int main(void)
{
int L=3,H=3,R=2;
RGB_img image;
image= initialize_values(L,H,R);
// initialize_rand(image);
get_values(image);
Display_values(image);
}