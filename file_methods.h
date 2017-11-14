#ifndef FILE_METHODS_H_
#define FILE_METHODS_H_
  FILE *UploadProccess(int *heigth, int *width, char file_name[50]);
  void WritePPM(int heigth, int width, int *pixels, char file_name[50]);
  void MatrizPPM(FILE *file, int heigth, int width, int *pixels);
#endif
