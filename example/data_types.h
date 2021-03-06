#ifndef __LCR_DATA_TYPES_H__
#define __LCR_DATA_TYPES_H__

namespace LCR {

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
        int shape;
	};
	
	struct CollimatorEx : public Collimator {
		double sec_diameter;
		double sec_thickness;
		double umbra_width;
		double penumbra_width;
		int direction;	// 0: horizontal, 1: vertical
	};

};

#endif // __LCR_DATA_TYPES_H__
