#ifndef IMAGE_PROCCESS_H_
#define IMAGE_PROCCESS_H_
  void GrayScalePixels(FILE *file, int heigth, int width, PixelRGB *pixels, PixelRGB *original, double *median);
  double StandardDeviation(int heigth, int width, PixelRGB *pixels, double *median);
  void GaussFilter(int heigth, int width, PixelRGB *pixels, double deviation);
  void SobelFilter(int heigth, int width, PixelRGB *pixels);
  void Binarization(int heigth, int width, PixelRGB *pixels);
  void MatrixToPointer(int heigth, int width, PixelRGB res[heigth][width], PixelRGB *pixels);
#endif
