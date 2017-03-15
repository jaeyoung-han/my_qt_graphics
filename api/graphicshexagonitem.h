#ifndef __MQGAPI_GRAPHICS_HEXAGON_ITEM_H__
#define __MQGAPI_GRAPHICS_HEXAGON_ITEM_H__

#include <QGraphicsPolygonItem>
#include <QPainter>

namespace MQGAPI {

  class GraphicsHexagonItem : public QGraphicsPolygonItem
  {
  public:
    GraphicsHexagonItem(qreal diameter, qreal angle = 0, QGraphicsItem *parent = Q_NULLPTR);
    virtual ~GraphicsHexagonItem();

  protected:
    void buildVertices(qreal diameter, qreal angle);

  private:
    QPolygonF vertices;
  };
};

#endif // __MQGAPI_GRAPHICS_HEXAGON_ITEM_H__
