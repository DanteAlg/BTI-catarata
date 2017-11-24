#include <stdio.h>
#include <math.h>

#define Black 0
#define White 255

#include "structs.h"

// Gerar matriz de pixels da imagem em escala de cinza
void GrayScalePixels(FILE *file, int heigth, int width, PixelRGB *pixels, PixelRGB *original) {
  PixelRGB pixelRGB, originalRGB;
  double pixel, grayRGB[3] = { 0.3, 0.59, 0.11 };
  int code, line, col;

  for (line = 0; line < heigth; line++) {
    for (col = 0; col < width; col++) {
      pixel = 0;

      // Escala por combinação linear https://capivararex.wordpress.com/2016/04/17/dip02-conversao-rgb-para-escala-de-cinza/
      // R: 0.3, G: 0.59, B: 0.11
      fscanf(file, "%d", &code);
      pixel += grayRGB[0]*code;

      fscanf(file, "%d", &code);
      pixel += grayRGB[1]*code;

      fscanf(file, "%d", &code);
      pixel += grayRGB[2]*code;

      pixelRGB.r = pixel;
      pixelRGB.g = pixel;
      pixelRGB.b = pixel;

      originalRGB.r = pixel;
      originalRGB.g = pixel;
      originalRGB.b = pixel;

      *(pixels + line * width + col) = pixelRGB;
      *(original + line * width + col) = originalRGB;
    }
  }
}

// Verifica se os dois pontos estão dentro do tamanho da imagem
int imgLimit(int pos, int x, int ref) {
  if (pos + x > 0 && pos + x <= ref)
    return 1;

  return 0;
}

void MatrixToPointer(int heigth, int width, PixelRGB res[heigth][width], PixelRGB *pixels) {
  int line, col;
  PixelRGB pixel;

  for (line = 0; line < heigth; line++) {
    for (col = 0; col < width; col++) {
      pixel = *(pixels + line * width + col);
      pixel.r = res[line][col].r;
      pixel.g = res[line][col].g;
      pixel.b = res[line][col].b;

      *(pixels + line * width + col) = pixel;
    }
  }
}


// Utilizar o filtro de gauss para tirar os ruidos da imagem
void GaussFilter(int heigth, int width, PixelRGB *pixels) {
  int line, col, pixel;
  int k_line, k_col;
  PixelRGB pixelRGB, res[heigth][width];

  // Kernel Gaussiano
  int kernel[5][5] = {
    { 1,  4,  6,  4, 1 },
    { 4, 16, 24, 16, 4 },
    { 6, 24, 36, 24, 6 },
    { 4, 16, 24, 16, 4 },
    { 1,  4,  6,  4, 1 }
  };

  // Soma dos valores do kernel [peso]
  int gauss_weight = 256;
  // variável que percorre o gradiente do kernel na matriz
  int interate = 2;

  for (line = 0; line < heigth; line++) {
    for (col = 0; col < width; col++) {
      pixel = 0;

      for(k_line = -interate; k_line < interate; k_line++ ) {
        for( k_col = -interate; k_col < interate; k_col++ ) {
          if (imgLimit(line, k_line, heigth) == 1 && imgLimit(col, k_col, width) == 1) {
            pixelRGB = *(pixels + (line + k_line)*width + (col + k_col));
            pixel += (pixelRGB.r)*kernel[k_line+interate][k_col+interate];
          }
        }
      }

      res[line][col].r = pixel/gauss_weight;
      res[line][col].g = res[line][col].r;
      res[line][col].b = res[line][col].r;
    }
  }

  MatrixToPointer(heigth, width, res, pixels);

  return;
}

// Aplica a covulação no pixel para o calculo de Sobel
int sobelCovulation(int sobel_v[3][3], int x, int y, int width, PixelRGB *pixels) {
  PixelRGB pixel;
  int l, c, res = 0;

  // Apenas localiza os pixels RGB
  PixelRGB area[3][3] = {
    { *(pixels + (x - 1)*width + y - 1), *(pixels + x*width + y - 1), *(pixels + (x + 1)*width + y - 1) },
    { *(pixels + (x - 1)*width + y), *(pixels + x*width + y), *(pixels + (x + 1)*width + y) },
    { *(pixels + (x - 1)*width + y + 1), *(pixels + x*width + y + 1), *(pixels + (x + 1)*width + y + 1) }
  };

  for (l = 0; l < 3; l++) {
    for (c = 0; c < 3; c++) {
      pixel = area[l][c];

      res += sobel_v[l][c]*pixel.r;
    }
  }

  return res;
}

// Filtro de sobel para realsar as arestas
// https://stackoverflow.com/questions/17815687/image-processing-implementing-sobel-filter
void SobelFilter(int heigth, int width, PixelRGB *pixels) {
  int sobel_x[3][3] = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } },
      sobel_y[3][3] = { {1, 2, 1 }, { 0, 0, 0}, { -1, -2, -1 } };

  int line, col, sc, pixelX, pixelY;
  PixelRGB res[heigth][width];

  for (line = 1; line < (heigth - 2); line++) {
    for (col = 1; col < (width - 2); col++) {
      pixelX = sobelCovulation(sobel_x, line, col, width, pixels);
      pixelY = sobelCovulation(sobel_y, line, col, width, pixels);

      res[line][col].r = ceil(sqrt(pow(pixelX, 2) + pow(pixelY, 2)));
      res[line][col].g = res[line][col].r;
      res[line][col].b = res[line][col].r;
    }
  }

 MatrixToPointer(heigth, width, res, pixels);
}

// Binarização de imagem (dividir pixels em dois grupos e contonar as linhas)
void Binarization(int heigth, int width, PixelRGB *pixels) {
  int line, col, mid = 30;
  PixelRGB pixel;

  for (line = 0; line < heigth; line++) {
    for (col = 0; col < width; col++) {
      pixel = *(pixels + line * width + col);

      if (pixel.r > mid) {
        pixel.r = White;
        pixel.g = White;
        pixel.b = White;
      }
      else {
        pixel.r = Black;
        pixel.g = Black;
        pixel.b = Black;
      }

      *(pixels + line * width + col) = pixel;
    }
  }
}

