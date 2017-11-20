#include <stdio.h>
#include <math.h>

#define PI 3.14159265
#define Black 0

#include "structs.h"

// Verificar as formas circulares do olho e escrever o arquivo de resultado
void HoughTransformation(int heigth, int width, PixelRGB *pixels, FILE *file) {
  int line, col, theta;
  PixelRGB pixel, matrix[heigth][width];

  for (line = 0; line < heigth; ++line) {
    for (col = 0; col < width;  ++col) {
      pixel = *(pixels + line * width + col);

      if (pixel.r == Black) {
        for (theta = -90; theta <= 90; theta++) {
        }
      }
    }
  }

  fprintf(file, "a) Diagnóstico Geral: \n");
  fprintf(file, "b) Porcentagem de Comprometimento: \n");
}
