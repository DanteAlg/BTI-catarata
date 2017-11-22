#ifndef STRUCTS_H_
#define STRUCTS_H_
  typedef struct PixelRGB {
    int r;
    int g;
    int b;
  } PixelRGB;

  typedef struct HoughObj {
    int line;
    int col;
    int value;
    int radius;
  } HoughObj;
#endif

