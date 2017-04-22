#ifndef __COLLIMATOR_SECTIONAL_VIEW_H__
#define __COLLIMATOR_SECTIONAL_VIEW_H__

#include <QList>
#include "graphicsview.h"
#include "graphicshexagonitem.h"
#include "data_types.h"

class QGraphicsItemGroup;

namespace LCR {

  class CollimatorVerticalSectionView : public MQGAPI::GraphicsView
  {
    Q_OBJECT
  public:
	  CollimatorVerticalSectionView(double ins_diameter = 0, double _septa = 0, QWidget *parent = Q_NULLPTR);

  private:
    double diameter;  // inscribed circle
    double septa;

    v3 size;
  };

};

#endif // __COLLIMATOR_SECTIONAL_VIEW_H__
