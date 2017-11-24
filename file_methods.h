#ifndef FILE_METHODS_H_
#define FILE_METHODS_H_
  FILE *UploadProccess(int *heigth, int *width, char file_name[50]);
  void WritePPM(int heigth, int width, PixelRGB *pixels, char file_name[50]);
  void MatrizPPM(FILE *file, int heigth, int width, int *pixels);
  void SegmentedWritePPM(int heigth, int width, HoughObj center, PixelRGB *pixels, char file_name[50]);
  void WriteResults(double percent, char file_name[50]);
#endif
