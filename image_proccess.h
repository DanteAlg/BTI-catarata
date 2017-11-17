#ifndef IMAGE_PROCCESS_H_
#define IMAGE_PROCCESS_H_
  void GrayScalePixels(FILE *file, int heigth, int width, PixelRGB *pixels);
  void GaussFilter(int heigth, int width, PixelRGB *pixels);
  void SobelFilter(int heigth, int width, PixelRGB *pixels);
  void Binarization(int heigth, int width, PixelRGB *pixels);
#endif
