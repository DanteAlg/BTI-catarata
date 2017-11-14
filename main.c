// Dependencies
#include <stdlib.h>
#include <stdio.h>

// Files
#include "file_methods.h"
#include "image_proccess.h"
#include "image_magnitude.h"

// OBS.: heigth e width que são passados pela imagem ppm são os valores do
// tamanho da matriz final.

// Argumentos em vetor de char quando inicializa o programa
// https://stackoverflow.com/questions/2108192/what-are-the-valid-signatures-for-cs-main-function
int main(int argc, char* argv[]) {
  int h, w;
  int *heigth = &h, *width = &w;
  FILE* file;

  file = UploadProccess(heigth, width);

  int *pixels =  (int*)malloc(sizeof(int) * (*heigth) * (*width));

  free(pixels);

  // Processamento da matriz da imagem

  GrayScalePixels(file, *heigth, *width, pixels);
  WritePPM(*heigth, *width, pixels, "eye_grayscale.ppm");

  GaussFilter(*heigth, *width, pixels);
  WritePPM(*heigth, *width, pixels, "eye_gauss_filter.ppm");

  SobelFilter(*heigth, *width, pixels);
  WritePPM(*heigth, *width, pixels, "eye_sobel_filter.ppm");

  Binarization(*heigth, *width, pixels);
  WritePPM(*heigth, *width, pixels, "eye_binarization.ppm");

  HoughTransformation(*heigth, *width, pixels);

  printf("heigth: %d, width: %d\n", *(heigth), *(width));

  return 0;
}
