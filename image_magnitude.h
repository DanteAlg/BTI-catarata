#ifndef IMAGE_MAGNITUDE_H_
#define IMAGE_MAGNITUDE_H_
  HoughObj *HoughTransformation(int heigth, int width, PixelRGB *pixels);
  double CalculateDiseasePercentual(int heigth, int width, HoughObj *center, PixelRGB *pixels);
#endif
