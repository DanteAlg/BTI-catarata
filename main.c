// Dependencies
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Files
#include "structs.h"
#include "file_methods.h"
#include "image_proccess.h"
#include "image_magnitude.h"

// OBS.: heigth e width que são passados pela imagem ppm são os valores do
// tamanho da matriz final.

// Argumentos em vetor de char quando inicializa o programa
// https://stackoverflow.com/questions/2108192/what-are-the-valid-signatures-for-cs-main-function
int main(int argc, char* argv[]) {
  if (argc != 7) {
    printf("Por favor, passe os parametros -i -f -o\n");
    return -1;
  }

  int h, w;
  int *heigth = &h, *width = &w;
  char file_name[50], file_format[10];
  FILE* file;

  strcpy(file_name, argv[2]);
  strcpy(file_format, argv[4]);

  file = UploadProccess(heigth, width, file_name); // OK

  PixelRGB *pixels =  (PixelRGB*)malloc(sizeof(PixelRGB) * (*heigth) * (*width));

  free(pixels);

  // Processamento da matriz da imagem

  GrayScalePixels(file, *heigth, *width, pixels); // OK
  WritePPM(*heigth, *width, pixels, "eye_grayscale.ppm");

  GaussFilter(*heigth, *width, pixels); // OK
  WritePPM(*heigth, *width, pixels, "eye_gauss_filter.ppm");

  SobelFilter(*heigth, *width, pixels); // OK
  WritePPM(*heigth, *width, pixels, "eye_sobel_filter.ppm");

  Binarization(*heigth, *width, pixels); // OK
  WritePPM(*heigth, *width, pixels, "eye_binarization.ppm");

  // Encontrar circulos e gerar resultados

  FILE* file_res = fopen(argv[6], "w");
  int *hough;

  HoughTransformation(*heigth, *width, pixels, hough);

  printf("heigth: %d, width: %d\n", *(heigth), *(width));

  return 0;
}
