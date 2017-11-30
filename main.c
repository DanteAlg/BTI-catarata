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

  PixelRGB *pixels = (PixelRGB*)malloc(sizeof(PixelRGB) * (*heigth) * (*width));
  PixelRGB *original = (PixelRGB*)malloc(sizeof(PixelRGB) * (*heigth) * (*width));

  // Processamento da matriz da imagem

  GrayScalePixels(file, *heigth, *width, pixels, original); // OK
  WritePPM(*heigth, *width, pixels, "eye_grayscale.ppm");

  int count;

  // Quanto mais borrado a imagem melhor fica depois do sobel
  // Estou passando gauss várias vezes por não ter tido tempo de fazer o código
  // que descobre um desvio padrão que faça um gauss mais prático.
  for (count = 0; count < 10; count++)
    GaussFilter(*heigth, *width, pixels); // OK
  WritePPM(*heigth, *width, pixels, "eye_gauss_filter.ppm");

  SobelFilter(*heigth, *width, pixels); // OK
  WritePPM(*heigth, *width, pixels, "eye_sobel_filter.ppm");

  Binarization(*heigth, *width, pixels); // OK
  WritePPM(*heigth, *width, pixels, "eye_binarization.ppm");

  // Encontrar circulos e gerar resultados

  HoughObj *center = HoughTransformation(*heigth, *width, pixels);

  SegmentedWritePPM(*heigth, *width, *center, original, "eye_segmented.ppm");

  double disease_perc = CalculateDiseasePercentual(*heigth, *width, center, original);

  WriteResults(disease_perc, argv[6]);

  // Debugger messages
  printf("Pupila - X: %d Y: %d RAIO: %d\n", center->line, center->col, center->radius);
  printf("Image - heigth: %d, width: %d, pontos com catarata %0.2f%%\n", *(heigth), *(width), disease_perc);

  return 0;
}
