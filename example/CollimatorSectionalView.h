#ifndef __COLLIMATOR_SECTIONAL_VIEW_H__
#define __COLLIMATOR_SECTIONAL_VIEW_H__

#include "graphicsview.h"
#include "data_types.h"

namespace LCR {

  class CollimatorSectionalView : public MQGAPI::GraphicsView
  {
    Q_OBJECT
  public:
    CollimatorSectionalView(qreal _diameter = 0, qreal _septa = 0, QWidget *parent = Q_NULLPTR);
    virtual ~CollimatorSectionalView();

    void setHole(qreal diameter, qreal septa);

  protected:
    void buildHoles();

  private:
    qreal diameter;
    qreal septa;

    Collimator data;
  };

};

#endif // __COLLIMATOR_SECTIONAL_VIEW_H__
