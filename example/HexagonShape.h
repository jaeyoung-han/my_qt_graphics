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

		void setCollimatorSize(const v3& coll_size);
		void setParameters(double diameter, double septa, int direction);

        QList<QGraphicsItem*> buildHoles(QGraphicsScene* scene, QPointF origin, qreal scale_factor, int flag);

        int type() { return 1; }

	private:
        QList<QGraphicsItem*> build_horizontal(QGraphicsScene* scene);
        QList<QGraphicsItem*> build_vertical(QGraphicsScene* scene);

	private:
		double diameter;  // inscribed circle
		double septa;
		int direction;

		v3 size;
	};
};

#endif // __HEXAGON_SHAPE_H__
