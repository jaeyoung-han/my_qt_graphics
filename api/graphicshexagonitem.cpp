#include <QtMath>
#include "graphicshexagonitem.h"

using namespace MQGAPI;

GraphicsHexagonItem::GraphicsHexagonItem(qreal diameter, qreal angle, QGraphicsItem *parent)
  : QGraphicsPolygonItem(parent)
{
  buildVertices(diameter, angle);
}

void GraphicsHexagonItem::buildVertices(qreal diameter, qreal angle)
{
  Q_ASSERT(diameter > 0);

  qreal radius = diameter * 0.5;
  qreal unit_angle = M_PI / 3;

  vertices.clear();
  for (size_t i = 0; i < 6; ++i) {
    QPointF p(radius * qCos(i * unit_angle + angle), radius * qSin(i * unit_angle + angle));
    vertices.push_back(p);
  }
  setPolygon(vertices);
}
