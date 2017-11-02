#include <stdio.h>
#include <stdlib.h>

// Gerar matriz de pixels da imagem em escala de cinza
void grayScalePixels(FILE *file, int heigth, int width, int *pixels) {
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

     *(pixels + line*width + col) = (int) pixelRGB;

    }
  }

  printf("Pixels: %p\n", pixels);

  return;
}

// Carregar header .ppm
void readPPMHeader(FILE *file, int *heigth, int *width) {
  // PPM header description http://netpbm.sourceforge.net/doc/ppm.html
  // P3
  // # description
  // width heigth
  // max_color
  int max_color;
  char ppmVersion[10], file_description[50];

  fgets(ppmVersion, 9, file);
  fgets(file_description, 49, file);
  fscanf(file, "%d", width);
  fscanf(file, "%d", heigth);
  fscanf(file, "%d", &max_color);
}

// Escreve um arquivo ppm a partir de uma matriz
void WritePPM(int heigth, int width, int *pixels, char file_name[50]) {
  FILE *file = fopen(file_name, "wb");
  int line, col, pixel;

  fprintf(file, "P3\n%d %d\n255\n", width, heigth);

  for (line = 0; line < heigth; ++line) {
    for (col = 0; col < width;  ++col) {
     if (line < 1 && col < 5)
      pixel = *(pixels + line * width + col);
      fwrite(&pixel, sizeof(int), 1, file);
    }
  }

  fclose(file);

  return;
}

// Upload de arquivo e criação da matriz em preto e branco
void* UploadProccess(int *pixels, int *heigth, int *width) {
  char file_name[30] = "images/Catarata.ppm"; //file_format[5]
  FILE *file;

  printf("Escreva o nome do arquivo: ");
  //scanf("%s", file_name);

  // Carrega Arquivo de origem
  file = fopen(file_name, "rb");
  printf("\n");

  // Previnir erro ao não encontrar um arquivo
  while (!file) {
    printf("Arquivo não encontrado, por favor tente novamente: ");
    scanf("%s", file_name);
    file = fopen(file_name, "rb");
    printf("\n");
  }

  readPPMHeader(file, heigth, width);
  pixels = (int*)malloc(sizeof(int) * (*heigth) * (*width));

  grayScalePixels(file, *heigth, *width, pixels);

  return pixels;
}
