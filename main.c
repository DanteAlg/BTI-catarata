// Dependencies
#include <stdio.h>

// Files
#include "file_upload.h"

typedef struct Image {
  FILE *file;
} Image;

int main() {
  Image img;

  img.file = FileUpload();
  // Verificação de dados do arquivo
  // Transformar imagem em escala de cinza
  // Captura de dados da imagem
  // Verficação da doença e porcentagem
  return 0;
}
