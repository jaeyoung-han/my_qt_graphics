#ifndef __LCR_DATA_TYPES_H__
#define __LCR_DATA_TYPES_H__

#include <QSettings>

namespace LCR {

    struct v2 {
        double x;
        double y;
        v2() : x(0), y(0) {}
        v2(double _x, double _y) : x(_x), y(_y) {}
    };

	struct v3 {
		double x;
		double y;
		double z;
	};

    struct Hole {
        double z;
        double diameter_long;
        double diameter_tran;
        double septa_long;
        double septa_tran;

        Hole() {
            z = 0;
            diameter_long = 2.0;
            diameter_tran = 2.0;
            septa_long = 0.2;
            septa_tran = 0.2;
        }
    };

    static inline double getX(double y, const v2& p1, const v2& p2)
    {
        return (p1.x - p2.x) / (p1.y - p2.y) * (y - p2.y) + p2.x;
    }

    static inline double getY(double x, const v2& p1, const v2& p2)
    {
        return (p1.y - p2.y) / (p1.x - p2.x) * (x - p2.x) + p2.y;
    }

	class Collimator {
    public:
        Collimator() {
            size.x = 10;
            size.y = 10;
            size.z = 100;

            hole_ex.z = size.z;
            hole_en.z = 0;
            hole_sec.z = 0;

            focus_coll_long = 460;
            focus_coll_tran = 460;
            focus_hole_long = 460;
            focus_hole_tran = 460;

            //diameter[0] = 2.0;
            //diameter[1] = 2.4;
            //septa[0] = 0.3;
            //septa[1] = 0.375;
            //section_height = 0;
            shape = 0;

            //focus_coll[0] = 500;
            //focus_coll[1] = 500;
            //focus_hole[0] = 500;
            //focus_hole[1] = 500;
        }

		v3 size;

        Hole hole_ex;
        Hole hole_en;
        Hole hole_sec;

        double focus_coll_long;
        double focus_coll_tran;
        double focus_hole_long;
        double focus_hole_tran;
        
		//double diameter[2];
		//double septa[2];
		//double section_height;
        int shape;
  //      double focus_coll[2];
  //      double focus_hole[2];

        void update() {
            hole_en.diameter_long = getLongitudinalDiameter(hole_en.z);
            hole_en.diameter_tran = getTransverseDiameter(hole_en.z);
            hole_en.septa_long = getLongitudinalDistance(hole_en.z) - hole_en.diameter_long;
            hole_en.septa_tran = getTransverseDistance(hole_en.z) - hole_en.diameter_tran;

            hole_sec.diameter_long = getLongitudinalDiameter(hole_sec.z);
            hole_sec.diameter_tran = getTransverseDiameter(hole_sec.z);
            hole_sec.septa_long = getLongitudinalDistance(hole_sec.z) - hole_sec.diameter_long;
            hole_sec.septa_tran = getTransverseDistance(hole_sec.z) - hole_sec.diameter_tran;
        }

        double getLongitudinalDiameter(double z) {
            return (focus_hole_long - z) / (focus_hole_long - size.z) * hole_ex.diameter_long;
        }

        double getTransverseDiameter(double z) {
            return (focus_hole_tran - z) / (focus_hole_tran - size.z) * hole_ex.diameter_tran;
        }

        double getLongitudinalDistance(double z) {
            return (focus_coll_long - z) / (focus_coll_long - size.z) * (hole_ex.diameter_long + hole_ex.septa_long);
        }

        double getTransverseDistance(double z) {
            return (focus_coll_tran - z) / (focus_coll_tran - size.z) * (hole_ex.diameter_tran + hole_ex.septa_tran);
        }

        void loadSettings(QSettings& settings) {
            size.x = settings.value("COLLIMATOR_LENGTH", 30).toDouble();
            size.y = settings.value("COLLIMATOR_WIDTH", 30).toDouble();
            size.z = settings.value("COLLIMATOR_HEIGHT", 100).toDouble();

            settings.beginGroup("Exit");
            {
                hole_ex.z = settings.value("HEIGHT", size.z).toDouble();
                hole_ex.diameter_long = settings.value("DIAMETER_LONGITUDINAL", 2.0).toDouble();
                hole_ex.diameter_tran = settings.value("DIAMETER_TRANSVERSE", 2.5).toDouble();
                hole_ex.septa_long = settings.value("SEPTA_LONGITUDINAL", 2.0).toDouble();
                hole_ex.septa_tran = settings.value("SEPTA_TRANSVERSE", 2.5).toDouble();
            }
            settings.endGroup();

            focus_coll_long = settings.value("COLLIMATOR_FOCUS_LONGITUDINAL", 460).toDouble();
            focus_coll_tran = settings.value("COLLIMATOR_FOCUS_TRANSVERSE", 460).toDouble();
            focus_hole_long = settings.value("HOLE_FOCUS_LONGITUDINAL", 460).toDouble();
            focus_hole_tran = settings.value("HOLE_FOCUS_TRANSVERSE", 460).toDouble();

            shape = settings.value("HOLE_SHAPE", 0).toInt();

            update();
        }
        void saveSettings(QSettings& settings) {
            update();

            settings.setValue("COLLIMATOR_LENGTH", size.x);
            settings.setValue("COLLIMATOR_WIDTH", size.y);
            settings.setValue("COLLIMATOR_HEIGHT", size.z);

            settings.beginGroup("Exit");
            {
                settings.setValue("HEIGHT", hole_ex.z);
                settings.setValue("DIAMETER_LONGITUDINAL", hole_ex.diameter_long);
                settings.setValue("DIAMETER_TRANSVERSE", hole_ex.diameter_tran);
                settings.setValue("SEPTA_LONGITUDINAL", hole_ex.septa_long);
                settings.setValue("SEPTA_TRANSVERSE", hole_ex.septa_tran);
            }
            settings.endGroup();

            settings.setValue("COLLIMATOR_FOCUS_LONGITUDINAL",focus_coll_long); 
            settings.setValue("COLLIMATOR_FOCUS_TRANSVERSE", focus_coll_tran); 
            settings.setValue("HOLE_FOCUS_LONGITUDINAL", focus_hole_long); 
            settings.setValue("HOLE_FOCUS_TRANSVERSE", focus_hole_tran); 

            settings.setValue("HOLE_SHAPE", shape);
        }
        //v2 getDiameter(double height) {
        //    v2 result;
        //    result.x = diameter[0] / (focus_hole[0] - size.z) * (focus_hole[0] - height);
        //    result.y = diameter[0] / (focus_hole[1] - size.z) * (focus_hole[1] - height);
        //    return result;
        //}
        //v2 getDistance(double height) {
        //    v2 result;
        //    result.x = (diameter[0] + septa[0]) / (focus_coll[0] - size.z) * (focus_coll[0] - height);
        //    result.y = (diameter[0] + septa[0]) / (focus_coll[1] - size.z) * (focus_coll[1] - height);
        //    return result;
        //}
    };
	
	class CollimatorEx : public Collimator {
    public:
        CollimatorEx() : Collimator() {
            direction = 0;
            //sec_diameter[0] = 0;
            //sec_diameter[1] = 0;
            //sec_thickness[0] = 0;
            //sec_thickness[1] = 0;
            umbra_width = 0;
            penumbra_width = 0;
        }
		//double sec_diameter[2];
		//double sec_thickness[2];
		double umbra_width;
		double penumbra_width;
		int direction;	// 0: horizontal, 1: vertical

        void loadSettings(QSettings& settings) {
            direction = settings.value("DIRECTION", 0).toInt();
            Collimator::loadSettings(settings);
        }
        void saveSettings(QSettings& settings) {
            settings.setValue("DIRECTION", direction);
            Collimator::saveSettings(settings);
        }

        void updateUmbra(double detect_position) {
            v2 tl(hole_ex.diameter_long * -0.5, hole_ex.z);
            v2 tr(hole_ex.diameter_long *  0.5, hole_ex.z);
            v2 bl(hole_en.diameter_long * -0.5, hole_en.z);
            v2 br(hole_en.diameter_long *  0.5, hole_en.z);

            // Umbra
            double x = getX(focus_hole_long, tl, bl);
            v2 ul(x, detect_position);
            x = getX(detect_position, tr, br);
            v2 ur(x, detect_position);

            x = getX(detect_position, tl, br);
            v2 pl(x, detect_position);
            x = getX(detect_position, tr, bl);
            v2 pr(x, detect_position);

            umbra_width = ur.x - ul.x;
            penumbra_width = pr.x - pl.x;
        }
	};

};

#endif // __LCR_DATA_TYPES_H__
