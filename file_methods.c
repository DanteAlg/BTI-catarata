#include <stdio.h>

#include "structs.h"
#include <math.h>

#define PI 3.14159265

// [DEBUG] Gera uma matriz a partir de um arquivo ppm
void MatrizPPM(FILE *file, int heigth, int width, int *pixels) {
  int code, line, col;

  for (line = 0; line < heigth; line++) {
    for (col = 0; col < width; col++) {
      fscanf(file, "%d", &code);
      *(pixels + line * width + col) = code;

      fscanf(file, "%d", &code);
      *(pixels + line * width + col) = code;

      fscanf(file, "%d", &code);
      *(pixels + line * width + col) = code;
    }
  }
}

void WriteResults(double percent, char file_name[50]) {
  FILE* file = fopen(file_name, "w");
  double trashold = 50;

  if (percent > trashold) {
    fprintf(file, "a) Diagnóstico Geral: %s\n", "Com catarata");
  }
  else {
    fprintf(file, "a) Diagnóstico Geral: %s\n", "Sem catarata");
  }

  fprintf(file, "b) Porcentagem de comprometimento: %0.2f%%\n", percent);

  fclose(file);
}

// Escreve um arquivo ppm a partir de uma matriz
void WritePPM(int heigth, int width, PixelRGB *pixels, char file_name[50]) {
  FILE *file = fopen(file_name, "wb");
  PixelRGB pixel;
  int line, col;

  fprintf(file, "P3\n%d %d\n255\n", width, heigth);

  for (line = 0; line < heigth; ++line) {
    for (col = 0; col < width;  ++col) {
      pixel = *(pixels + line * width + col);

      fprintf(file, "%d\n", pixel.r);
      fprintf(file, "%d\n", pixel.g);
      fprintf(file, "%d\n", pixel.b);
    }
  }

  fclose(file);

  return;
}

// Relação de um ponto com uma circuferencia http://www.macoratti.net/14/05/c_vpc1.htm
// Transforma tudo fora da circuferencia em preto
void cropTrash(HoughObj center, int heigth, int width, PixelRGB *pixels) {
  int line, col, dx, dy;
  PixelRGB pixel;

  for (line = 0; line < heigth; ++line) {
    for (col = 0; col < width;  ++col) {
      dx = pow(center.line - line, 2);
      dy = pow(center.col - col, 2);

      if (dx + dy > pow(center.radius, 2)) {
        pixel = *(pixels + line*width + col);
        pixel.r = 0;
        pixel.g = 0;
        pixel.b = 0;
        *(pixels + line*width + col) = pixel;
      }
    }
  }
}

void SegmentedWritePPM(int heigth, int width, HoughObj center, PixelRGB *pixels, char file_name[50]) {
  int theta, x, y, line, col;
  PixelRGB pixel;

  cropTrash(center, heigth, width, pixels);

  WritePPM(heigth, width, pixels, file_name);
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

// Upload de arquivo e criação da matriz em preto e branco
FILE* UploadProccess(int *heigth, int *width, char file_name[50]) {
  FILE *file;

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

  return file;
}

