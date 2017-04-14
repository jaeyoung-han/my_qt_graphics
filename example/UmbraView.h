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
	void drawCollimator();

	Collimator data;

	// Draw detection plane (focus plane)
	QGraphicsLineItem* detection_line;
	QGraphicsLineItem* center_line;
	// Draw collimator
	QGraphicsPolygonItem* collimator_polygon;


	// Draw upper hole

	// Draw lower hole

	// Draw umbra lines
	QGraphicsLineItem* umbra_line_l;
	QGraphicsLineItem* umbra_line_r;

	// Draw penumbra lines
	QGraphicsLineItem* peumbra_line_l;
	QGraphicsLineItem* peumbra_line_r;
  };

};

#endif // __UMBRA_VIEW_H__