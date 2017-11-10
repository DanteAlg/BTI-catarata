// Dependencies
#include <stdlib.h>
#include <stdio.h>

// Files
#include "file_methods.h"
#include "image_proccess.h"

// OBS.: heigth e width que são passados pela imagem ppm são os valores do
// tamanho da matriz final.

int main() {
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

  Binarization(*heigth, *width, pixels);
  WritePPM(*heigth, *width, pixels, "eye_binarization.ppm");

  /*
   * Restante:
   * Receber dados da imagem via opções "-i image..."
   * Filtro de sobel
   * Transformada de Hough (Detectar os círculos)
   * Cálculo de magnitudes
  */

  printf("heigth: %d, width: %d\n", *(heigth), *(width));

  return 0;
}
