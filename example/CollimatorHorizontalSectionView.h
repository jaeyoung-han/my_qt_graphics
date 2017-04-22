#ifndef __COLLIMATOR_HORIZONTAL_SECTION_VIEW_H__
#define __COLLIMATOR_HORIZONTAL_SECTION_VIEW_H__

#include <QList>
#include "graphicsview.h"
#include "graphicshexagonitem.h"
#include "data_types.h"

class QGraphicsItemGroup;

namespace LCR {

  class CollimatorHorizontalSectionView : public MQGAPI::GraphicsView
  {
    Q_OBJECT
  public:
	  CollimatorHorizontalSectionView(double ins_diameter = 0, double _septa = 0, QWidget *parent = Q_NULLPTR);
    virtual ~CollimatorHorizontalSectionView();

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

#endif // __COLLIMATOR_HORIZONTAL_SECTION_VIEW_H__