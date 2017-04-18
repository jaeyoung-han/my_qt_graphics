#ifndef __LCR_DATA_TYPES_H__
#define __LCR_DATA_TYPES_H__

namespace LCR {
  enum CONVERGENCE {
    Converging = 0,
    Diverging = 1,
  };

  struct v3 {
    double x;
    double y;
    double z;
  };

  struct Collimator {
    v3 size;
    double focus_distance;
    double diameter[2];
    double septa[2];
    double section_height;
    double focus_width;
  };
};

#endif // __LCR_DATA_TYPES_H__
