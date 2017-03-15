#ifndef __LCR_DATA_TYPES_H__
#define __LCR_DATA_TYPES_H__

namespace LCR {
  struct v3 {
    double x;
    double y;
    double z;
  };

  struct Collimator {
    double diameter;
    double septa;

    v3 size;
  };
};

#endif // __LCR_DATA_TYPES_H__
