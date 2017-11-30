#ifndef IMAGE_MAGNITUDE_H_
#define IMAGE_MAGNITUDE_H_
  HoughObj *HoughTransformation(int heigth, int width, PixelRGB *pixels, int max_radius);
  double CalculateDiseasePercentual(int heigth, int width, HoughObj *center, PixelRGB *pixels);
#endif
