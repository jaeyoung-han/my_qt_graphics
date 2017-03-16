#ifndef __COLLIMATOR_SECTIONAL_VIEW_H__
#define __COLLIMATOR_SECTIONAL_VIEW_H__

#include <QList>
#include "graphicsview.h"
#include "graphicshexagonitem.h"
#include "data_types.h"

class QGraphicsItemGroup;

namespace LCR {

  class CollimatorSectionalView : public MQGAPI::GraphicsView
  {
    Q_OBJECT
  public:
    CollimatorSectionalView(double ins_diameter = 0, double _septa = 0, QWidget *parent = Q_NULLPTR);
    virtual ~CollimatorSectionalView();

    void setCollimatorSize(const v3& coll_size);
    void setParameters(double diameter, double septa);

    void buildHoles();
    void updateBase();
    void updateHoles();

  private:
    QGraphicsRectItem* base_item;
    QGraphicsItemGroup* hex_group;
    QList<QGraphicsItem*> hex_list;


    double diameter;  // inscribed circle
    double septa;

    v3 size;
  };

};

#endif // __COLLIMATOR_SECTIONAL_VIEW_H__
