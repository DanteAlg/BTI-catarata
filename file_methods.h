#ifndef FILE_METHODS_H_
#define FILE_METHODS_H_
  FILE *UploadProccess(int *heigth, int *width);
  void GrayScalePixels(FILE *file, int heigth, int width, int *pixels);
  void WritePPM(int heigth, int width, int *pixels, char file_name[50]);
#endif
