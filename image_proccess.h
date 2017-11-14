#ifndef IMAGE_PROCCESS_H_
#define IMAGE_PROCCESS_H_
  void GrayScalePixels(FILE *file, int heigth, int width, int *pixels);
  void GaussFilter(int heigth, int width, int *pixels);
  void SobelFilter(int heigth, int width, int *pixels);
  void Binarization(int heigth, int width, int *pixels);
#endif
