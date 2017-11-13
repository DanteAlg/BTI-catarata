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

// Verifica se os dois pontos estão dentro do tamanho da imagem
int imgLimit(int pos, int x, int ref) {
  if (pos + x > 0 && pos + x <= ref)
    return 1;

  return 0;
}


// Utilizar o filtro de gauss para tirar os ruidos da imagem
void GaussFilter(int heigth, int width, int *pixels) {
  int line, col, pixelRGB;
  int k_line, k_col;

  // Kernel Gaussiano (Oferecido pelo material)
  int kernel[5][5] = {
    { 2,  4,  5,  4, 2 },
    { 4,  9, 12,  9, 4 },
    { 5, 12, 15, 12, 5 },
    { 4,  9, 12,  9, 4 },
    { 2,  4,  5,  4, 2 }
  };

  // Soma dos valores do kernel [peso] (Oferecido pelo material)
  int gauss_weight = 159;

  for (line = 0; line < heigth; line++) {
    for (col = 0; col < width; col++) {
      pixelRGB = 0;

      for(k_line = -2; k_line < 2; k_line++ ) {
        for( k_col = -2; k_col < 2; k_col++ ) {
          if (imgLimit(line, k_line, heigth) == 1 && imgLimit(col, k_col, width) == 1)
            pixelRGB += (*(pixels + (line*width + k_line) + (col + k_col))*kernel[k_line+2][k_col+2]);
        }
      }

      *(pixels + line * width + col) = pixelRGB/gauss_weight;
    }
  }

  return;
}

// Binarização de imagem (dividir pixels em dois grupos e contonar as linhas)
void Binarization(int heigth, int width, int *pixels) {
  int line, col, trashold = 127;

  for (line = 0; line < heigth; line++) {
    for (col = 0; col < width; col++) {
      if (*(pixels + line * width + col) > trashold) {
        *(pixels + line * width + col) = 255;
      }
      else {
        *(pixels + line * width + col) = 0;
      }
    }
  }

  return;
}
