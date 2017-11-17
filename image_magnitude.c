#include <stdio.h>

#include "structs.h"

// Verificar as formas circulares do olho e escrever o arquivo de resultado
// TODO: Aplicar a transformação de Houg, verificar valores e criar o arquivo de resultado
void HoughTransformation(int heigth, int width, int *pixels, FILE *file) {
  int line, col, *b;

  for (line = 0; line < heigth; ++line) {
    for (col = 0; col < width;  ++col) {
      // Remover
      *b = *(pixels + line * width + col);
    }
  }

  fprintf(file, "a) Diagnóstico Geral: \n");
  fprintf(file, "b) Porcentagem de Comprometimento: \n");
}
