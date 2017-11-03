// Dependencies
#include <stdlib.h>
#include <stdio.h>

// Files
#include "file_methods.h"
#include "image_proccess.h"

int main() {
  int h, w;
  int *heigth = &h, *width = &w;
  FILE* file;

  file = UploadProccess(heigth, width);

  int *pixels =  (int*)malloc(sizeof(int) * (*heigth) * (*width));

  free(pixels);

  GrayScalePixels(file, *heigth, *width, pixels);

  WritePPM(*heigth, *width, pixels, "eye_grayscale.pgm");

  printf("heigth: %d, width: %d\n", *(heigth), *(width));

  return 0;
}
