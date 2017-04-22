#ifndef __UMBRA_WIDGET_H__
#define __UMBRA_WIDGET_H__

#include "graphicsview.h"
#include "data_types.h"

namespace LCR {

	class UmbraWidget : public QGraphicsView {

	public:
		UmbraWidget();

		void initialize();
		void update(qreal dia_umbra, qreal dia_penumbra);

	protected:
		void resizeEvent(QResizeEvent* event);

	private:
		void update();

	private:
		qreal diameter_umbra;
		qreal diameter_penumbra;

		QGraphicsEllipseItem* umbra_circle;
		QGraphicsEllipseItem* middle_circle;
		QGraphicsEllipseItem* penumbra_circle;
	};

};

#endif // __UMBRA_WIDGET_H__
