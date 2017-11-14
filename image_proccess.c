#include <stdio.h>
#include <math.h>

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

void matrixToPointer(int heigth, int width, int res[heigth][width], int *pixels) {
  int line, col;

  for (line = 0; line < heigth; line++) {
    for (col = 0; col < width; col++) {
      *(pixels + line * width + col) = res[line][col];
    }
  }
}


// Utilizar o filtro de gauss para tirar os ruidos da imagem
void GaussFilter(int heigth, int width, int *pixels) {
  int line, col, pixelRGB;
  int k_line, k_col;
  int res[heigth][width];

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

      res[line][col] = pixelRGB/gauss_weight;
    }
  }

  matrixToPointer(heigth, width, res, pixels);

  return;
}

// Aplica a covulação no pixel para o calculo de Sobel
int sobelCovulation(int sobel_v[3][3], int x, int y, int width, int *pixels) {
  int l, c, res = 0;

  int area[3][3] = { 
    { *(pixels + (x - 1)*width + y - 1), *(pixels + x*width + y - 1), *(pixels + (x + 1)*width + y - 1) },
    { *(pixels + (x - 1)*width + y), *(pixels + x*width + y), *(pixels + (x + 1)*width + y) },
    { *(pixels + (x - 1)*width + y + 1), *(pixels + x*width + y + 1), *(pixels + (x + 1)*width + y + 1) }
  };

  for (l = 0; l < 3; l++) {
    for (c = 0; c < 3; c++) {
      res += sobel_v[l][c] * area[l][c];
    }
  }

  return res;
}

// Filtro de sobel para realsar as arestas
// https://stackoverflow.com/questions/17815687/image-processing-implementing-sobel-filter
void SobelFilter(int heigth, int width, int *pixels) {
  int sobel_x[3][3] = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } },
      sobel_y[3][3] = { {-1, 2, 1 }, { 0, 0, 0}, { -1, -2, -1 } };

  int line, col, sc, pixelX, pixelY, res[heigth][width];

  for (line = 1; line < (heigth - 2); line++) {
    for (col = 1; col < (width - 2); col++) {
      pixelX = sobelCovulation(sobel_x, line, col, width, pixels);
      pixelY = sobelCovulation(sobel_y, line, col, width, pixels);

      res[line][col] = ceil(sqrt(pow(pixelX, 2) + pow(pixelY, 2)));

      if (res[line][col] > 255)
        res[line][col] = 255;
    }
  }

  matrixToPointer(heigth, width, res, pixels);
}

// Binarização de imagem (dividir pixels em dois grupos e contonar as linhas)
void Binarization(int heigth, int width, int *pixels) {
  int line, col, mid = 127;

  for (line = 0; line < heigth; line++) {
    for (col = 0; col < width; col++) {
      if (*(pixels + line * width + col) > mid) {
        *(pixels + line * width + col) = 255; // Branco
      }
      else {
        *(pixels + line * width + col) = 0; // Preto
      }
    }
  }

  return;
}

