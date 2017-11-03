#include <stdio.h>

// Gerar matriz de pixels da imagem em escala de cinza
void GrayScalePixels(FILE *file, int heigth, int width, int *pixels) {
  double pixelRGB, grayRGB[3] = { 0.3, 0.59, 0.11 };
  int code, line, col;

  for (line = 0; line < heigth; line++) {
    for (col = 0; col < width; col++) {
      pixelRGB = 0;

      // Escala por combinação linear https://capivararex.wordpress.com/2016/04/17/dip02-conversao-rgb-para-escala-de-cinza/
      // R: 0.3, G: 0.59, B: 0.11
      fscanf(file, "%d", &code);
      pixelRGB += grayRGB[0]*code;

      fscanf(file, "%d", &code);
      pixelRGB += grayRGB[1]*code;

      fscanf(file, "%d", &code);
      pixelRGB += grayRGB[2]*code;

      *(pixels + line * width + col) = (int) pixelRGB;
    }
  }

  return;
}

