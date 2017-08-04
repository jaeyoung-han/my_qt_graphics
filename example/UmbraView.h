#ifndef __UMBRA_VIEW_H__
#define __UMBRA_VIEW_H__

#include "graphicsview.h"
#include "data_types.h"

namespace LCR {

	class UmbraView : public MQGAPI::GraphicsView
	{
		Q_OBJECT
	public:
		UmbraView(QWidget *parent = Q_NULLPTR);
		virtual ~UmbraView();

		void update();
		void setData(const Collimator& newData);

		const Collimator& getData() const {
			return data;
		}

	private:
		void initialize();
		void initialize2();

		void drawCollimator();

		void drawVerticalUmbra();
		void drawVerticalSection();

		QPolygonF buildPolygon(const QPointF& top_center, qreal top_diameter, const QPointF& bottom_center, qreal bottom_diameter);

		Collimator data;

		// Draw detection plane (focus plane)
		QGraphicsLineItem* detection_line;
		QGraphicsLineItem* center_line;
		// Draw collimator
		QGraphicsPolygonItem* collimator_polygon;


		// Draw upper hole
		QGraphicsLineItem* top_hole;

		// Draw lower hole
		QGraphicsLineItem* bottom_hole;

		// Draw umbra lines
		QGraphicsLineItem* umbra_line_l;
		QGraphicsLineItem* umbra_line_r;

		// Draw penumbra lines
		QGraphicsLineItem* penumbra_line_l;
		QGraphicsLineItem* penumbra_line_r;

		QGraphicsEllipseItem* middle_circle;
		QGraphicsEllipseItem* umbra_circle;
		QGraphicsEllipseItem* penumbra_circle;

		QGraphicsPolygonItem* block1;
		QGraphicsPolygonItem* block2;
		QGraphicsPolygonItem* block3;
		QGraphicsPolygonItem* block4;
	};

};

#endif // __UMBRA_VIEW_H__
