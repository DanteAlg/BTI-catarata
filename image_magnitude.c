#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265
#define White 255

#include "structs.h"
#include "image_proccess.h"

// Raio maximo pra um círculo dentro da imagem
int maxRadius(int heigth, int width) {
  if (heigth > width)
    return heigth/2;

  return width/2;
}

// Verificar as formas circulares do olho e escrever o arquivo de resultado
void HoughTransformation(int heigth, int width, PixelRGB *pixels, int *hough) {
  int line, col, theta, radius, hough_x, hough_y;
  // Para cada pixel verificar se forma um possivel círculo,
  // verificar do raio min ao max
  int max_radius = maxRadius(heigth, width);
  int min_radius = 120;

  // Inicializar o espaço de hough com valores zerados
  hough = realloc(hough, sizeof(int)*heigth*width*max_radius);

  PixelRGB pixel;

  printf("Rodando segmentação da imagem... ");
  printf("Aguarde...\n");

  for (line = 0; line < heigth; ++line) {
    for (col = 0; col < width;  ++col) {
      pixel = *(pixels + line * width + col);

      if (pixel.r == White) {
        // Apenas para os pixels brancos, criamos várias circuferencias entre o raio max e min
        // Para cada theta entre 0 e 360 adquirimos o ponto e armazenamos na matriz
        for (radius = min_radius; radius <= max_radius; radius++) {
          for (theta = 0; theta < 360; theta++) {
            hough_x = line - radius * cos(theta * PI/180);
            hough_y = col - radius * sin(theta * PI/180);

            if ((hough_x > 0 && hough_x < heigth) && (hough_y > 0 && hough_y < width))
              *(hough + hough_x*heigth + hough_y*width + radius) += 1;
          }
        }
      }
    }
  }
}

