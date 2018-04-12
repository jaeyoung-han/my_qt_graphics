#ifndef __HEXAGON_SHAPE_H__
#define __HEXAGON_SHAPE_H__

#include <QList>
#include "graphicsview.h"
#include "graphicshexagonitem.h"
#include "data_types.h"
#include "SectionShape.h"

class QGraphicsItemGroup;

namespace LCR {

	class HexagonShape : public SectionShape
	{
	public:
        explicit HexagonShape() : SectionShape() {}

		void setCollimatorSize(const CollimatorEx& size);
		//void setParameters(double diameter, double septa, int direction);
        void setParameters(double diameter[2], double septa[2], int direction);

        QList<QGraphicsItem*> buildHoles(QGraphicsScene* scene, QPointF origin, qreal scale_factor, int flag);

        int type() { return 1; }

    public slots:
        bool checkMousePointInAir(QPointF point);

	private:
        QList<QGraphicsItem*> build_horizontal(QGraphicsScene* scene);
        QList<QGraphicsItem*> build_vertical(QGraphicsScene* scene);

        QPointF getNearestHexagon(QPointF point);
        bool checkPointInAir(QPointF point, QPointF rect_center);

	private:
		//double diameter;  // inscribed circle
        double diameter_x, diameter_y;
        //double septa;
        double septa_x, septa_y;
        int direction;

        CollimatorEx size_;
	};
};

#endif // __HEXAGON_SHAPE_H__
