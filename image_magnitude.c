#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265
#define White 255
#define Black 0

#include "structs.h"
#include "image_proccess.h"

// Raio maximo pra um círculo dentro da imagem
int maxRadius(int heigth, int width) {
  if (heigth > width)
    return heigth/2;

  return width/2;
}

HoughObj *maiorValor(int *hough, int heigth, int width, int min_radius, int max_radius) {
  int line, col, maior, radius, rad;
  HoughObj *center = malloc(sizeof(HoughObj));
  center->value = 0;

  for (radius = min_radius; radius < max_radius; radius+= 10) {
    for (line = 0; line < heigth; line++) {
      for (col = 0; col < width;  col++) {
        rad = *(hough + (line * width * max_radius) + (col * max_radius) + radius);

        if (rad > center->value) {
          center->value = rad;
          center->line = line;
          center->col = col;
          center->radius = radius;
        }
      }
    }
  }

  return center;
}

// Verificar as formas circulares do olho
HoughObj *HoughTransformation(int heigth, int width, PixelRGB *pixels) {
  int line, col, theta, radius, hough_x, hough_y;
  // Para cada pixel verificar se forma um possivel círculo,
  // verificar do raio min ao max
  int max_radius = maxRadius(heigth, width);
  int min_radius = 70;

  // Inicializar o espaço de hough com valores zerados
  int *hough;
  hough = calloc(heigth*width*max_radius, sizeof(int));

  PixelRGB pixel;

  for (line = 0; line < heigth; line++) {
    for (col = 0; col < width;  col++) {
      pixel = *(pixels + line * width + col);

      if (pixel.r == White) {
        // Apenas para os pixels brancos, criamos várias circuferencias entre o raio max e min
        // Para cada theta entre 0 e 360 adquirimos o ponto e armazenamos na matriz
        for (radius = min_radius; radius <= max_radius; radius += 10) {
          for (theta = 0; theta < 360; theta++) {
            hough_x = (int) (line - radius * cos(theta * PI/180));
            hough_y = (int) (col - radius * sin(theta * PI/180));

            if ((hough_x > 0 && hough_x < heigth) && (hough_y > 0 && hough_y < width))
              *(hough + hough_x*width*max_radius + hough_y*max_radius + radius) += 1;
          }
        }
      }
    }
  }

  return maiorValor(hough, heigth, width, min_radius, max_radius);
}

// Relação de um ponto com uma circuferencia http://www.macoratti.net/14/05/c_vpc1.htm
double CalculateDiseasePercentual(int heigth, int width, HoughObj *center, PixelRGB *pixels) {
  int line, col, dx, dy;
  double total = 0, affected = 0;
  int trashold = White*0.5;

  PixelRGB pixel;

  for(line = 0; line < heigth; line++) {
    for(col = 0; col < width; col++) {
      dx = pow(center->line - line, 2);
      dy = pow(center->col - col, 2);

      if (dx + dy <= pow(center->radius, 2)) {
        total++;
        pixel = *(pixels + line*width + col);

        if (pixel.r > trashold) {
          affected++;
        }
      }
    }
  }

  printf("Total: %f, Affected: %f, trashold: %d\n", total, affected, trashold);

  return ((100*affected)/total);
}

