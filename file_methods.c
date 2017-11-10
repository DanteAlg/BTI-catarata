#include <stdio.h>

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

// Escreve um arquivo ppm a partir de uma matriz
void WritePPM(int heigth, int width, int *pixels, char file_name[50]) {
  FILE *file = fopen(file_name, "wb");
  int line, col;

  fprintf(file, "P3\n%d %d\n255\n", width, heigth);

  for (line = 0; line < heigth; ++line) {
    for (col = 0; col < width;  ++col) {
      fprintf(file, "%d\n", *(pixels + line * width + col));
      fprintf(file, "%d\n", *(pixels + line * width + col));
      fprintf(file, "%d\n", *(pixels + line * width + col));
    }
  }

  fclose(file);

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
FILE* UploadProccess(int *heigth, int *width) {
  char file_name[30] = "images/Catarata2.ppm"; //file_format[5]
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

  return file;
}

