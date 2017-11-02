// Dependencies
#include <stdio.h>

// Files
#include "file_methods.h"

int main() {
  int h, w, p;
  int *heigth = &h, *width = &w, *pixels = &p;

  pixels = UploadProccess(pixels, heigth, width);
  WritePPM(*heigth, *width, pixels, "eye_grayscale.ppm");

  printf("heigth: %d, width: %d, pixels: %p \n", *(heigth), *(width), pixels);

  return 0;
}
