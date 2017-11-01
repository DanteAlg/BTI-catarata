// Dependencies
#include <stdio.h>

// Files
#include "file_upload.h"

typedef struct Image {
  int *heigth;
  int *width;
  int **pixels;
} Image;

int main() {
  int heigth, width;
  Image img = { &heigth, &width };

  UploadProccess(img.pixels, img.heigth, img.width);

  printf("heigth: %d, width: %d \n", *(img.heigth), *(img.width));
  // Transformar imagem em escala de cinza
  // Captura de dados da imagem
  // Verficação da doença e porcentagem
  return 0;
}
